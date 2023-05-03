#include "stdafx.h"

DWORD WINAPI MainThread(LPVOID hModule) {
	Backend::Start((HMODULE)hModule);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			Backend::SetModule(hModule);
			copy((BYTE*)hModule, (BYTE*)(hModule + 0x1000), back_inserter(Backend::m_modulePE));
			Backend::GetModuleInfo();

			DisableThreadLibraryCalls(hModule);
			Memory::UnlinkModuleFromPEB(hModule);
			Memory::UnlinkModuleFromPEB(GetModuleHandleA("dinput8.dll"));
			Memory::FakePeHeader(hModule);

			CreateThread(0, 0, MainThread, hModule, 0, 0);
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return true;
}