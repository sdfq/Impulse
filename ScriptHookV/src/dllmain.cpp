// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);
typedef void(*PresentCallback)(void*);

enum eGameVersion : int
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,

	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,

	VER_1_0_372_2_STEAM,
	VER_1_0_372_2_NOSTEAM,

	VER_1_0_393_2_STEAM,
	VER_1_0_393_2_NOSTEAM,

	VER_1_0_393_4_STEAM,
	VER_1_0_393_4_NOSTEAM,

	VER_1_0_463_1_STEAM,
	VER_1_0_463_1_NOSTEAM,

	VER_1_0_505_2_STEAM,
	VER_1_0_505_2_NOSTEAM,

	VER_1_0_573_1_STEAM,
	VER_1_0_573_1_NOSTEAM,

	VER_1_0_617_1_STEAM,
	VER_1_0_617_1_NOSTEAM,

	VER_1_0_678_1_STEAM,
	VER_1_0_678_1_NOSTEAM,

	VER_1_0_757_2_STEAM,
	VER_1_0_757_2_NOSTEAM,

	VER_1_0_757_4_STEAM,
	VER_1_0_757_4_NOSTEAM,

	VER_1_0_791_2_STEAM,
	VER_1_0_791_2_NOSTEAM,

	VER_1_0_877_1_STEAM,
	VER_1_0_877_1_NOSTEAM,

	VER_1_0_944_2_STEAM,
	VER_1_0_944_2_NOSTEAM,

	VER_1_0_1011_1_STEAM,
	VER_1_0_1011_1_NOSTEAM,

	VER_1_0_1032_1_STEAM,
	VER_1_0_1032_1_NOSTEAM,

	VER_1_0_1103_2_STEAM,
	VER_1_0_1103_2_NOSTEAM,

	VER_1_0_1180_2_STEAM,
	VER_1_0_1180_2_NOSTEAM,

	VER_1_0_1290_1_STEAM,
	VER_1_0_1290_1_NOSTEAM,

	VER_1_0_1365_1_STEAM,
	VER_1_0_1365_1_NOSTEAM,

	VER_1_0_1493_0_STEAM,
	VER_1_0_1493_0_NOSTEAM,

	VER_1_0_1493_1_STEAM,
	VER_1_0_1493_1_NOSTEAM,

	VER_SIZE,
	VER_UNK = -1
};

void __declspec(dllexport) scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)()) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "scriptRegister"); // penis_enlargement_pills
	((void(*)(HMODULE, void(*)()))function)(module, LP_SCRIPT_MAIN);
}

void __declspec(dllexport) scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)()) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "scriptRegisterAdditionalThread"); // penis_enlargement_pills
	((void(*)(HMODULE, void(*)()))function)(module, LP_SCRIPT_MAIN);
}

void __declspec(dllexport) scriptUnregister(HMODULE module) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "scriptUnregister"); // penis_enlargement_pills
	((void(*)(HMODULE))function)(module);
}

void __declspec(dllexport) scriptUnregister(void(*LP_SCRIPT_MAIN)()) { // deprecated
}

void __declspec(dllexport) nativeInit(UINT64 hash) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "nativeInit"); // penis_enlargement_pills
	((void(*)(UINT64))function)(hash);
}

void __declspec(dllexport) nativePush64(UINT64 val) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "nativePush64"); // penis_enlargement_pills
	((void(*)(UINT64))function)(val);
}

__declspec(dllexport) uint64_t* nativeCall() {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "nativeCall"); // penis_enlargement_pills
	return ((uint64_t*(*)())function)();
}

__declspec(dllexport) uint64_t* getGlobalPtr(int index) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "getGlobalPtr"); // penis_enlargement_pills
	return ((uint64_t*(*)(int))function)(index);
}

int __declspec(dllexport) createTexture(const char* fileName) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "createTexture"); // penis_enlargement_pills
	return ((int(*)(const char*))function)(fileName);
}

void __declspec(dllexport) drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "drawTexture"); // penis_enlargement_pills
	((void(*)(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a))function)(id, index, level, time, sizeX, sizeY, centerX, centerY, posX, posY, rotation, screenHeightScaleFactor, r, g, b, a);
}

void __declspec(dllexport) scriptWait(unsigned long waitTime) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "scriptWait"); // penis_enlargement_pills
	((void(*)(unsigned long))function)(waitTime);
}

void __declspec(dllexport) keyboardHandlerRegister(KeyboardHandler func) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "keyboardHandlerRegister"); // penis_enlargement_pills
	((void(*)(KeyboardHandler))function)(func);
}

void __declspec(dllexport) keyboardHandlerUnregister(KeyboardHandler func) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "keyboardHandlerUnregister"); // penis_enlargement_pills
	((void(*)(KeyboardHandler))function)(func);
}

eGameVersion __declspec(dllexport) getGameVersion() {
	static uint64_t function;
	if(!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "getGameVersion"); // penis_enlargement_pills

	return ((eGameVersion(*)())function)();
}

__declspec(dllexport) BYTE *getScriptHandleBaseAddress(int handle) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "getScriptHandleBaseAddress"); // penis_enlargement_pills
	return ((BYTE*(*)(int))function)(handle);
}

void __declspec(dllexport) presentCallbackRegister(PresentCallback cb) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "presentCallbackRegister"); // penis_enlargement_pills
	((void(*)(PresentCallback))function)(cb);
}

void __declspec(dllexport) presentCallbackUnregister(PresentCallback cb) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "presentCallbackUnregister"); // penis_enlargement_pills
	((void(*)(PresentCallback))function)(cb);
}

int __declspec(dllexport) worldGetAllVehicles(int *arr, int arrSize) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "worldGetAllVehicles"); // penis_enlargement_pills
	return ((int(*)(int*, int))function)(arr, arrSize);
}

int __declspec(dllexport) worldGetAllPeds(int *arr, int arrSize) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "worldGetAllPeds"); // penis_enlargement_pills
	return ((int(*)(int*, int))function)(arr, arrSize);
}

int __declspec(dllexport) worldGetAllObjects(int *arr, int arrSize) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "worldGetAllObjects"); // penis_enlargement_pills
	return ((int(*)(int*, int))function)(arr, arrSize);
}

int __declspec(dllexport) worldGetAllPickups(int *arr, int arrSize) {
	static uint64_t function;
	if (!function)
		function = (uint64_t)GetProcAddress((HMODULE)0xf9d38c98, "worldGetAllPickups"); // penis_enlargement_pills
	return ((int(*)(int*, int))function)(arr, arrSize);
}


DWORD WINAPI MainThread(LPVOID lp) {
	while (true) {
		Sleep(1000);
	}

	return 1;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}