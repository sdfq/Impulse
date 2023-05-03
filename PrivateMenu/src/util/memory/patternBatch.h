#pragma once

class PatternBatch {
private:
	struct BatchedPattern {
		PStruct m_pattern;
		vector<PatternByte> m_bytes;
		bool(*m_callback)(DWORD64 address);
		bool m_found;
		DWORD64 m_addr;
	};

	String m_name;
	vector<BatchedPattern> m_buffer;

public:
	PatternBatch(String name) : m_name(name) {
		LOG_DEBUG("[Pattern] registered %s batch", m_name);
	}
	void Submit(PStruct pattern, bool(*callback)(DWORD64 address));
	void Submit(string serverPattern, bool(*callback)(DWORD64 address));
	void Flush();
	String GetName() { return m_name; }
};