#include "stdafx.h"

static ThreadPool g_pool;

void ThreadPool::Initialize(int threads) {
	if (m_initialized) return;
	m_initialized = true;
	m_jobThreads.reserve(threads);
	for (int i = 0; i < threads; ++i)
		m_jobThreads.emplace_back(std::bind(&ThreadPool::ThreadEntry, this, i));
	LOG_DEBUG("[Threads] Thread pool created");
}

void ThreadPool::Cleanup() {
	{
		std::unique_lock <std::mutex> l(m_lock);

		m_shutdown = true;
		m_conditionVariable.notify_all();
	}
	for (auto& c_thread : m_threads) {
		c_thread->shutdown();
		//delete c_thread;
	}
	for (auto& c_thread : m_jobThreads)
		c_thread.join();
	LOG_DEBUG("[Threads] Thread pool terminated");
}

void ThreadPool::DoJob(std::function <void(void)> func) {
	if (!m_initialized) {
		LOG_ERROR("[Threads] Thread pool has not been initialized");
		return;
	}
	std::unique_lock <std::mutex> l(m_lock);
	m_jobs.emplace(std::move(func));
	m_conditionVariable.notify_one();
}

void ThreadPool::ThreadEntry(int index) {
	function <void(void)> job;
	while (1) {
		{
			std::unique_lock <mutex> lock(m_lock);
			while (!m_shutdown && m_jobs.empty()) m_conditionVariable.wait(lock);
			if (m_jobs.empty())return;
			job = std::move(m_jobs.front());
			m_jobs.pop();
		}
		job();
	}
}

void ThreadPool::Remove(String name, bool destroy) {
	/*auto vit = find(m_threads.begin(), m_threads.end(), name);
	if (vit != m_threads.end()) {
		auto item = (*vit);
		if (destroy) {
			item->destroy();
		}

		item->shutdown();
	}*/
}

Thread* ThreadPool::RegisterThread(String name, void(*func)()) {
	Thread* c_thread = new Thread(name);
	UINT64* args = new UINT64[3]{ 0, (UINT64)c_thread, (UINT64)func };

	c_thread->setHandle(CreateThread(0, 0, [](LPVOID lpFiberParameter) -> DWORD {
		UINT64* arguments = (UINT64*)lpFiberParameter;
		try {
			while ((*(Thread*)arguments[1]).isRunning()) {
				((void(*)(void)) arguments[2])();
			}
		} catch (...) {
			delete[] arguments;
		}
		return 1;
	}, args, 0, 0));

	if (Security::NtSetInformationThread) {
		Security::NtSetInformationThread(c_thread->getHandle(), 17, 0, 0);
	}

	m_threads.push_back(c_thread);
	LOG_DEBUG("[Threads] %s registered", name);
	return c_thread;
}

ThreadPool* GetThreadPool() {
	return &g_pool;
}