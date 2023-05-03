#include "stdafx.h"

NativeContext ScriptHookV::Context;
vector<ModuleDetection> ScriptHookV::LoadedModuleMemory;
uint64_t ScriptHookV::Hash;

void ScriptHookV::scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)()) {
	static char name[256];

	if (GetModuleFileNameA(module, name, 256)) {
		if (strstr(name, "Menyoo")) {
			uint64_t base = (uint64_t)module;
			uint64_t address = (base + 0x2CDC06);
			static BYTE nops[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

			DWORD oldProtect;
			Ext_VirtualProtect((void*)address, sizeof(nops), PAGE_EXECUTE_READWRITE, &oldProtect);
			memcpy((void*)address, &nops, sizeof(nops));
			Ext_VirtualProtect((void*)address, sizeof(nops), oldProtect, &oldProtect);
		}
	}

	MODULEINFO mi = {};
	GetModuleInformation(GetCurrentProcess(), module, &mi, sizeof(MODULEINFO));
	LOG_DEVPRINT("Adding shv module with base 0x%llx and size 0x%llx", (uint64_t)mi.lpBaseOfDll, (uint64_t)mi.SizeOfImage);
	LoadedModuleMemory.emplace_back((uint64_t)mi.lpBaseOfDll, (uint64_t)mi.SizeOfImage, name, module);

	GetScriptHookFiberManager()->AddFiber(va("0x%llx:0x%llx", (uint64_t)module, (uint64_t)LP_SCRIPT_MAIN), LP_SCRIPT_MAIN);
}

void ScriptHookV::scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)()) {
	GetScriptHookFiberManager()->AddFiber(va("0x%llx:0x%llx", (uint64_t)module, (uint64_t)LP_SCRIPT_MAIN), LP_SCRIPT_MAIN);
}

void ScriptHookV::scriptUnregister(HMODULE module) {
	auto fibers = GetScriptHookFiberManager()->GetFibers();
	for (auto&e : fibers) {
		if (strstr(e.m_name.c_str(), va("0x%llx", (uint64_t)module))) {
			GetScriptHookFiberManager()->Delete(e.m_name.c_str());
		}
	}
}

/*void ScriptHookV::scriptUnregister(void(*LP_SCRIPT_MAIN)()) { // deprecated
	LOG_DEBUG("[SHV] Unregistering thread with handle 0x%llx", LP_SCRIPT_MAIN);
	auto fibers = GetScriptHookFiberManager()->GetFibers();
	for (auto&e : fibers) {
		if (strstr(e.m_name, va("0x%llx", LP_SCRIPT_MAIN))) {
			GetScriptHookFiberManager()->Delete(e.m_name);
			break;
		}
	}
}*/

void ScriptHookV::nativeInit(uint64_t hash) {
	Context.reset();

	if (hash == 0x43A66C31C68491C0)
		hash = 0x50FAC3A3E030A6E1;

	if (hash == 0x239528EACDC3E7DE)
		hash = 0x3882114BDE571AD4;

	Hash = hash;
}

void ScriptHookV::nativePush64(uint64_t val) {
	Context.push(val);
}

uint64_t* ScriptHookV::nativeCall() {
	static uint64_t nativeBypasses[18] = {
		0x39FF19C64EF7DA5B,
		0x340E61DE7F471565,
		0xE0A7D1E497FFCD6F,
		0x2975C866E6713290,
		0xA1B043EE79A916FB,
		0x18D0456E86604654,
		0x2E397FD2ECD37C87,
		0xA4A79DD2D9600654,
		0x407C7F91DDB46C16,
		0xD24D37CC275948CC,
		0xA66C71C98D5F2CFB,
		0xFF1BED81BFDC0FE0,
		0x11879CDD803D30F4,
		0x57FFF03E423A4C0B,
		0x00A1CADD00108836,
		0x4B33C4243DE0C432,
		0x4851997F37FE9B3C,
		0xB3271D7AB655B441
	};

	bool found = false;

	for (int i = 0; i < 18; i++) {
		if (Hash == nativeBypasses[i]) {
			found = true;
			break;
		}
	}

	/*if (Hash == 0xa1cadd00108836) {
		LOG_DEBUG("SET_PLAYER_MODEL(%i, 0x%X);", Context.getArgument<int>(0), Context.getArgument<unsigned int>(1));
	}*/

	if (Hash == 0x509D5878EB39E842 || Hash == 0x9A294B2138ABB884 || Hash == 0x7DD959874C1FD534)
		Context.setArgument(4, true);

	if (Hash == 0x509D5878EB39E842) {
		Context.setArgument(5, true);
		Context.setArgument(6, false);
	}

	if (Hash == 0xAF35D0D2583051B0)
		Context.setArgument(6, false);

	if (Hash == 0xD49F9B0955C367DE) {
		Context.setArgument(6, true);
		Context.setArgument(7, false);
	}

	/*control check*/

	if (Hash == 0xD49F9B0955C367DE || Hash == 0xAF35D0D2583051B0 || Hash == 0x9A294B2138ABB884 || Hash == 0x509D5878EB39E842) {
		if (!STREAMING::HasModelLoaded(Context.getArgument<int>(0))) {
			STREAMING::RequestModel(Context.getArgument<int>(0));
		}
	}

	/*control check*/

	if (!found) {
		Invoker::call(Hash, &Context);
		Context.setVectorResults();
	}

	if (Hash == 0xAF35D0D2583051B0) {
		if (Context.getResultPtr() != nullptr) {
			Vehicle veh = *reinterpret_cast<Vehicle*>(reinterpret_cast<uint64_t*>(Context.getResultPtr()));
			DECORATOR::DecorSetInt(veh, "MPBitset", 0);
		}
	}

	if (Hash == 0x39FF19C64EF7DA5B || Hash == 0xE0A7D1E497FFCD6F || Hash == 0x340E61DE7F471565) {
		// set wanted level?
	}

	if (Hash == 0xA1B043EE79A916FB || Hash == 0xA4A79DD2D9600654 || Hash == 0x18D0456E86604654 || Hash == 0x407C7F91DDB46C16) {
		Context.setResult(0, 0);
	}

	if (Hash == 0x3C06B5C839B38F7B || Hash == 0xDDDF64C91BFCF0AA || Hash == 0xE6CC9F3BA0FB9EF1 || Hash == 0x1077788E268557C2 || Hash == 0xF25D331DC2627BBC || Hash == 0xD83C2B94E7508980 || Hash == 0xCA97246103B63917 || Hash == 0x10FAB35428CCC9D7 || Hash == 0x9DE624D2FC4B603F) {
		Context.setResult(0, false);
	}

	if (Hash == 0xD24D37CC275948CC) {
		Context.setResult(0, Utils::GetHashKey(Context.getArgument<char*>(0)));
	}

	return reinterpret_cast<uint64_t*>(Context.getResultPtr());
}

uint64_t* ScriptHookV::getGlobalPtr(int index) {
	if (index == 0x140815) index = (Globals::IMIQUEUE_BASE + Globals::IMIQUEUE_OFFSET);
	return (uint64_t*)&Backend::GetGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF];
}

int ScriptHookV::createTexture(const char* fileName) {
	//LOG_DEBUG("[SHV] Ignoring call to createTexture");
	return 0;
}

void ScriptHookV::drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a) {
	//LOG_DEBUG("[SHV] Ignoring call to drawTexture");
}

void ScriptHookV::scriptWait(unsigned long waitTime) {
	GetScriptHookFiberManager()->Sleep(waitTime);
}

void ScriptHookV::keyboardHandlerRegister(KeyboardHandler function) {
	Input::g_keyboardFunctions.insert(function);
}

void ScriptHookV::keyboardHandlerUnregister(KeyboardHandler function) {
	Input::g_keyboardFunctions.erase(function);
}

int ScriptHookV::getGameVersion() {
	static const bool isSteam = GetConfig()->DoesFileExist("steam_api64.dll");
	return isSteam ? VER_1_0_1493_1_STEAM : VER_1_0_1493_1_NOSTEAM;
}

BYTE* ScriptHookV::getScriptHandleBaseAddress(int handle) {
#ifdef HARD_DEV
	LOG_DEBUG("getScriptHandleBaseAddress called with handle 0x%X", handle);
#endif
	auto address = PoolManager::GetEntityAddress(handle);
	if (!address) return nullptr;
	return (BYTE*)address;
}

void ScriptHookV::presentCallbackUnregister(PresentCallback cb) {

}

void ScriptHookV::presentCallbackRegister(PresentCallback cb) {

}

int ScriptHookV::worldGetAllVehicles(int *arr, int arrSize) {
	PoolManager::Update();
	auto vehicles = VehiclePool::GetVehicles();
	int size = vehicles.size();

	int iterateSize = size < arrSize ? size : arrSize;

	for (int i = 0; i < iterateSize; i++) {
		arr[i] = vehicles[i];
	}

	return iterateSize;
}

int ScriptHookV::worldGetAllPeds(int *arr, int arrSize) {
	PoolManager::Update();
	auto peds = PedPool::GetPeds();
	int size = peds.size();

	int iterateSize = size < arrSize ? size : arrSize;

	for (int i = 0; i < iterateSize; i++) {
		arr[i] = peds[i];
	}

	return iterateSize;
}

int ScriptHookV::worldGetAllObjects(int *arr, int arrSize) {
	auto objects = ObjectPool::GetObjects();
	int size = objects.size();

	int iterateSize = size < arrSize ? size : arrSize;

	for (int i = 0; i < iterateSize; i++) {
		arr[i] = objects[i];
	}

	return iterateSize;
}

int ScriptHookV::worldGetAllPickups(int *arr, int arrSize) {
	return 0;
}
