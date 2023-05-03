#pragma once

struct Fiber {
	LPVOID m_fiber;
	Fiber* m_nextFiber;
	unsigned long m_wakeTime;
	string m_name;
	bool m_disabled;
};

bool FiberTickBlankCondition(Fiber f);

class FiberManager {
public:
	void Init(String name);
	void Tick(bool(*cond)(Fiber f) = FiberTickBlankCondition);
	void AddFiber(String name, void(*function)());
	void Sleep(unsigned long waitTime);
	void GoToMainFiber();
	void Cleanup();
	void Delete(String name);
	vector<Fiber> GetFibers() { return m_fibers; }

	String GetCurrentFiberName() { return m_currentFiber->m_name.c_str(); }

private:
	vector<Fiber> m_fibers;

	LPVOID m_mainFiber;
	Fiber* m_currentFiber;

	String m_name;
	bool m_initialized;
	bool m_cleaned;
};

FiberManager* GetFiberManager();
FiberManager* GetAuthFiberManager();
FiberManager* GetScriptHookFiberManager();

void WAIT(unsigned long waitTime);
void WAITAUTH(unsigned long waitTime);