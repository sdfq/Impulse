#pragma once

#define STRINGIZE(x) #x
#define PROFILER_START(x) Test x(__FILE__, STRINGIZE(x));
#define PROFILER() Test x(__FILE__, __FUNCTION__);
#define PROFILER_END(x) x.end();

const double NANOTOMILLI = 1.0 / 1000000.0;

class ProfileEntry {
private:
	bool m_started;
	String m_fileName;
	String m_functionName;
	__int64 m_cyclesBegin;
	__int64 m_cyclesTotal;
	__int64 m_cyclesLatest;

	chrono::steady_clock::time_point m_timeBegin;
	uint64_t m_timeTotal;

	double m_timeAverageList[600];
	int m_timeAverageIndex;
	double m_timeAverageSum;
	double m_timeLatest;
	uint64_t m_calls;
public:
	ProfileEntry() : m_started(false), m_fileName(""), m_functionName(""), m_cyclesBegin(0), m_cyclesLatest(0), m_cyclesTotal(0), m_calls(0), m_timeAverageIndex(0), m_timeAverageSum(0), m_timeLatest(0), m_timeAverageList{ 0 } {}
	ProfileEntry(String fileName, String functionName) : m_started(false), m_fileName(fileName), m_functionName(functionName), m_cyclesBegin(0), m_cyclesLatest(0), m_cyclesTotal(0), m_calls(0), m_timeAverageIndex(0), m_timeAverageSum(0), m_timeLatest(0), m_timeAverageList{ 0 } {}

	void start() {
		if (m_started) {
			//LOG_ERROR("[Profile] call PROFILER_END(%s) before calling PROFILER_START(%s)", m_functionName, m_functionName);
			return;
		}
		m_calls++;
		m_cyclesBegin = __rdtsc();
		m_timeBegin = chrono::high_resolution_clock::now();
		m_started = true;
	}

	void end() {
		if (!m_started) {
			//LOG_ERROR("[Profile] call PROFILER_START(%s) before calling PROFILER_END(%s)", m_functionName, m_functionName);
			return;
		}
		m_cyclesLatest = __rdtsc() - m_cyclesBegin;
		m_cyclesTotal += m_cyclesLatest;

		m_timeLatest = double(chrono::duration_cast<std::chrono::nanoseconds>(chrono::high_resolution_clock::now() - m_timeBegin).count()) * NANOTOMILLI;
		calculateAverage(m_timeLatest);
		//m_timeTotal += m_timeLatest;
		m_started = false;

	}

	void calculateAverage(double newtick) {
		m_timeAverageSum -= m_timeAverageList[m_timeAverageIndex];
		m_timeAverageSum += newtick;
		m_timeAverageList[m_timeAverageIndex] = newtick;
		if (++m_timeAverageIndex == 600) m_timeAverageIndex = 0;
	}

	String getFileName() { return m_fileName; }
	String getFunctionName() { return m_functionName; }

	__int64 getCalls() { return m_calls; }
	__int64 getCycles() { return m_cyclesLatest; }
	double getLatest() { return m_timeLatest; }
	double getAverage() { return (m_timeAverageSum / 600.0); }
};

class Profiler {
private:
	map<String, ProfileEntry> m_entries;
public:
	ProfileEntry * getEntry(String fileName, String functionName) {
		if (m_entries.find(functionName) != m_entries.end()) return &m_entries[functionName];
		m_entries.insert({ functionName, ProfileEntry(fileName, functionName) });
		return &m_entries[functionName];
	}

	void Push(String fileName, String functionName) {
		getEntry(fileName, functionName)->start();
	}

	void Pop(String fileName, String functionName) {
		ProfileEntry* entry = getEntry(fileName, functionName);
		entry->end();
		//LOG_PRINT("%s %f %f", entry->getFunctionName(), entry->getLatest(), entry->getAverage());
	}

	vector<ProfileEntry> GetEntries() {
		vector<ProfileEntry> toRet;
		for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
			toRet.push_back(it->second);
		}
		return toRet;
	}

};

Profiler* GetProfiler();

class Test {
public:
	String m_fileName;
	String m_functionName;
	bool m_hasEnded;
	Test(String fileName, String functionName) : m_fileName(fileName), m_functionName(functionName), m_hasEnded(false) { GetProfiler()->Push(m_fileName, functionName); }
	~Test() {
		end();
	}

	void end() {
		if (!m_hasEnded) GetProfiler()->Pop(m_fileName, m_functionName);
		m_hasEnded = true;
	}
};