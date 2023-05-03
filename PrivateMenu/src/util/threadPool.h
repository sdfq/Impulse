#pragma once

class Thread {
private:
	String m_name;
	HANDLE m_thread;
	bool m_isRunning;

public:
	Thread() : m_name(""), m_thread(0), m_isRunning(true) {}
	Thread(String name) : m_name(name), m_thread(0), m_isRunning(true) {}
	void setHandle(HANDLE handle) { m_thread = handle; }
	HANDLE getHandle() { return m_thread; };
	void shutdown() { m_isRunning = false; };
	void destroy() { TerminateThread(m_thread, 0); };
	bool isRunning() { return m_isRunning; }
	String getName() { return m_name; }
};

class ThreadPool {
public:
	void Initialize(int threads);
	void Cleanup();
	void Remove(String name, bool destroy = false);
	void DoJob(std::function <void(void)> func);
	bool IsInitialized() { return m_initialized; }
	Thread* RegisterThread(String name, void(*func)());
	vector<Thread*> GetThreads() { return m_threads; };

private:
	vector<Thread*> m_threads;
	vector <thread> m_jobThreads;

	bool m_shutdown = false;
	bool m_initialized = false;

	mutex m_lock;
	condition_variable m_conditionVariable;
	queue <std::function <void(void)>> m_jobs;

	void ThreadEntry(int index);
};

ThreadPool* GetThreadPool();