#pragma once

DWORD FindProcessId(const WCHAR* pName);
BOOL Ext_VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
BOOL ClearCodeInjectionAllocatedMemory();
