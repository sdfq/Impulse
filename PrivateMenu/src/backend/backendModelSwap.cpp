#include "stdafx.h"
#include "backendModelSwap.h"
#include "backendProtection.h"

vector<modelSwap_t> ModelSwapping::modelSwaps;
uint64_t ModelSwapping::pModelMap;
uint16_t ModelSwapping::uiKey;

uint64_t ModelSwapping::FindHashInModelMap(Hash hash) {
	uint64_t i = 0;

	for (i = *reinterpret_cast<uint64_t*>(pModelMap + 8 * (hash % uiKey)); ; i = *reinterpret_cast<uint64_t*>(i + 8)) {
		if (!i) break;
		if (*reinterpret_cast<Hash*>(i) == hash) {
			return i;
		}
	}

	return 0;
}

uint16_t ModelSwapping::GetModelDataFromHash(Hash hash) {
	return *reinterpret_cast<uint16_t*>(FindHashInModelMap(hash) + 4);
}

void ModelSwapping::ModelSwap(String originalModel, String newModel) {
	if (originalModel == newModel) {
		return;
		// someone will do it anyway
	}
	if (modelSwaps.size() > 0) {
		for (modelSwap_t m : modelSwaps) {
			if (m.originalModel == originalModel)
				return;
			// tbh i don't want people with chains of shit complaining about crashes
		}
	}
	Hash originalHash = MISC::GetHashKey(originalModel);
	Hash newHash = MISC::GetHashKey(newModel);
	modelSwaps.push_back({ originalModel, newModel, originalHash, newHash, GetModelDataFromHash(originalHash) });
	*reinterpret_cast<uint16_t*>(FindHashInModelMap(originalHash) + 4) = GetModelDataFromHash(newHash); // swapping model data
}

void ModelSwapping::RemoveSwap(String originalModel) {
	modelSwap_t target;
	vector<modelSwap_t> buffer;
	bool found = false;
	for (int i = 0; i < modelSwaps.size(); i++) {
		if (modelSwaps.at(i).originalModel != originalModel) 
			buffer.push_back(modelSwaps.at(i));
		else {
			target = modelSwaps.at(i);
			found = true;
		}
	}
	if (found) {
		modelSwaps = buffer;
		*reinterpret_cast<uint16_t*>(FindHashInModelMap(target.originalHash) + 4) = target.originalData; // swapping model data back
	}
}

bool ModelSwapping::PreGame() {
	if (!Hooking::ServerPatternCallback<char>("MAP", [](Hooking::CallbackData<char> data) {
		pModelMap = *reinterpret_cast<decltype(pModelMap)*>(data.m_address + *(int32_t*)(data.m_address + 3) + 7);
	})) return false;

	if (!Hooking::ServerPatternCallback<char>("KEY", [](Hooking::CallbackData<char> data) {
		uiKey = *reinterpret_cast<decltype(uiKey)*>(data.m_address + *(int32_t*)(data.m_address + 3) + 7);
	})) return false;
	return true;
}