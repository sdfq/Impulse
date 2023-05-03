#include "stdafx.h"

FiberManager g_mainFiberManager;
FiberManager g_authFiberManager;
FiberManager g_scriptHookFiberManager;

void FiberManager::Init(String name) {
	if (m_initialized) return;
	ConvertThreadToFiber(nullptr);
	m_name = name;
	m_mainFiber = GetCurrentFiber();
	m_initialized = true;
	//LOG_DEBUG("[Threads] %s initialized", m_name);
}

void FiberManager::AddFiber(String name, void(*function)()) {
	UINT64* args = new UINT64[2]{ (UINT64)function, (UINT64)m_mainFiber };
	LPVOID fiber = CreateFiber(NULL, [](LPVOID lpFiberParameter) {
		UINT64* arguments = (UINT64*)lpFiberParameter;
		try {
			while (true) {
				((void(*)(void)) arguments[0])();
				SwitchToFiber((LPVOID)arguments[1]);
			}
		} catch (...) {
			delete[] arguments;
		}
	}, args);

	Fiber newFiber = { fiber, nullptr, timeGetTime(), name };
	m_fibers.push_back(newFiber);

	for (auto& fiber = m_fibers.begin(); fiber != m_fibers.end(); ++fiber) {
		auto& nextFiber = fiber + 1;
		if (nextFiber != m_fibers.end()) fiber->m_nextFiber = &*nextFiber;
		else fiber->m_nextFiber = &m_fibers.front();
	}
	m_currentFiber = &m_fibers.front();
	LOG_DEBUG("[Threads] Created %s fiber", newFiber.m_name.c_str());
}

bool FiberTickBlankCondition(Fiber f) { return true; };

void FiberManager::Tick(bool(*cond)(Fiber f)) {
	if (!m_currentFiber || !m_initialized) return;
	for (Fiber& f : m_fibers) {
		if (f.m_disabled) continue;
		if (cond(f)) {
			if (timeGetTime() >= f.m_wakeTime) {
				SwitchToFiber(f.m_fiber);
			}
		}
	}
	m_currentFiber = m_currentFiber->m_nextFiber;
}

void FiberManager::Sleep(unsigned long waitTime) {
	auto& fiber = find_if(m_fibers.begin(), FiberManager::m_fibers.end(), [](const Fiber& fiber) -> bool { return fiber.m_fiber == GetCurrentFiber(); });
	if (fiber != FiberManager::m_fibers.end()) {
		fiber->m_wakeTime = timeGetTime() + waitTime;
		SwitchToFiber(m_mainFiber);
	}
}

void FiberManager::GoToMainFiber() {
	SwitchToFiber(m_mainFiber);
}

void FiberManager::Delete(String name) {
	for (Fiber& fiber : m_fibers) {
		if (!strcmp(fiber.m_name.c_str(), name)) {
			fiber.m_disabled = true;
			LOG_DEBUG("[Threads] Deleted %s fiber", fiber.m_name.c_str());
			break;
		}
	}
}

void FiberManager::Cleanup() {
	if (!m_cleaned) {
		for (Fiber& fiber : m_fibers) {
			DeleteFiber(fiber.m_fiber);
			LOG_DEBUG("[Threads] Deleted %s fiber", fiber.m_name.c_str());
		}
		//LOG_DEBUG("[Threads] %s deleted", m_name);
		m_cleaned = true;
	}
}

FiberManager* GetFiberManager() {
	return &g_mainFiberManager;
}

FiberManager* GetAuthFiberManager() {
	return &g_authFiberManager;
}

FiberManager* GetScriptHookFiberManager() {
	return &g_scriptHookFiberManager;
}

void WAIT(unsigned long waitTime) {
	GetFiberManager()->Sleep(waitTime);
}

void WAITAUTH(unsigned long waitTime) {
	GetAuthFiberManager()->Sleep(waitTime);
}