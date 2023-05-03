#include "stdafx.h"

OceanManager g_oceanManager;

bool OceanManager::Init() {
	if (!Hooking::ServerPatternCallback<char>("OQ", [&](Hooking::CallbackData<char> data) {
		m_waterQuads.m_oceanQuads = (QuadInfo*)GetAddressFromInstruction(data.m_address);
	})) return false;

	if (!Hooking::ServerPatternCallback<char>("WI", [&](Hooking::CallbackData<char> data) {
		m_waveIntensity = (float*)GetAddressFromInstruction(data.m_address, 1);
	})) return false;
	
	if (!Hooking::ServerPatternCallback<char>("WT", [&](Hooking::CallbackData<char> data) {
		g_oceanManager.m_WaterTune = reinterpret_cast<sWaterTune*>(data.m_address);
	})) return false;
	return true;
}

void OceanManager::NoOcean(bool toggle) {
	for (int i = 0; i < m_waterQuads.m_oceanQuads->m_quadCount; i++) {
		uint64_t QuadStruct = m_waterQuads.m_oceanQuads->m_quadPool + (i * 0x1C);
		float Height = *(float*)(QuadStruct + 0x14);
		if (toggle && Height == 0.0f) *(float*)(QuadStruct + 0x14) = -10000.0f;
		else if (!toggle && Height == -10000.0f) *(float*)(QuadStruct + 0x14) = 0.0f;
	}
}

void OceanManager::ClearWater(bool toggle) {
	for (int i = 0; i < m_waterQuads.m_oceanQuads->m_quadCount; i++) {
		uint64_t QuadStruct = m_waterQuads.m_oceanQuads->m_quadPool + (i * 0x1C);
		if (toggle) *(int*)(QuadStruct + 0x8) = 0x01010101;
		else *(int*)(QuadStruct + 0x8) = 0x1A1A1A1A;
	}
}

void OceanManager::SetWaveIntensity(float intensity) {
	*m_waveIntensity = intensity;
}

bool OceanManager::Initialize() { return GetOceanManager()->Init(); }

OceanManager* GetOceanManager() { return &g_oceanManager; }