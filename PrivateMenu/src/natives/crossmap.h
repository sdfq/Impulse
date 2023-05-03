#pragma once

typedef std::unordered_map<uint64_t, uint64_t> crossmap;

typedef struct
{
	uint64_t m_x;
	uint64_t m_y;
} crossmapEntry;

class Crossmap
{
public:
	static bool Initialize();
	static uint64_t map(uint64_t original_native);
	static uint64_t m_crossmapData[];

private:
	static crossmap m_crossmap;
	static std::vector<uint64_t> m_failedMaps;
};