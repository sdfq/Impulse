#pragma once
#include "stdafx.h"

typedef struct {
	string originalModel;
	string newModel;
	Hash originalHash;
	Hash newHash;
	uint16_t originalData;
} modelSwap_t;

class ModelSwapping : Protection {
public:
	static uint64_t pModelMap;
	static uint16_t uiKey;
	static vector<modelSwap_t> modelSwaps;
	static uint64_t FindHashInModelMap(Hash hash);
	static uint16_t GetModelDataFromHash(Hash hash);
	static void ModelSwap(String originalModel, String newModel);
	static void RemoveSwap(String originalModel);
	static bool PreGame();
};