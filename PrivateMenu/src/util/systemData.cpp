#include "stdafx.h"

SystemData g_systemdata;

bool SystemData::Initialize()
{
	/*Main Data*/
	if (!Hooking::ServerPatternCallback<char>("SDMD", [&](Hooking::CallbackData<char> data) {
		m_operatingSystem =		(char*)(GetAddressFromInstruction(data.m_address, 0x56));
		m_CPUSpeed =			(char*)(GetAddressFromInstruction(data.m_address, 0x6F));
		m_CPUBrand =			(char*)(GetAddressFromInstruction(data.m_address, 0x7D));
		m_directXVersion =		(char*)(GetAddressFromInstruction(data.m_address, 0x8F));
		m_VRam =				(char*)(GetAddressFromInstruction(data.m_address, 0xA4));
		m_GPU =					(char*)(GetAddressFromInstruction(data.m_address, 0xAB));
		m_motherBoard =			(char*)(GetAddressFromInstruction(data.m_address, 0xD2));
		m_gameLanguage =		(char*)(GetAddressFromInstruction(data.m_address, 0xED));
	})) return false;

	/*Title Data*/
	if (!Hooking::ServerPatternCallback<char>("SDT", [&](Hooking::CallbackData<char> data) {
		m_gameName =			(char*)(GetAddressFromInstruction(data.m_address, 0x1A8));
	})) return false;

	/*Version Data*/
	if (!Hooking::ServerPatternCallback<char>("SDV", [&](Hooking::CallbackData<char> data) {
		m_gameBuild =			(char*)(GetAddressFromInstruction(data.m_address, 0x61));
		m_gameOnlineVersion =	(char*)(GetAddressFromInstruction(data.m_address, 0x109));
	})) return false;

	/*Exe Data*/
	if (!Hooking::ServerPatternCallback<char>("SDEN", [&](Hooking::CallbackData<char> data) {
		m_gameLauncherName =	(char*)(GetAddressFromInstruction(data.m_address, 0xC7));
		m_gameExecutableName =	(char*)(GetAddressFromInstruction(data.m_address, 0XEE));
	})) return false;

	/*Social Club Data*/
	if (!Hooking::ServerPatternCallback<char>("SDSC", [&](Hooking::CallbackData<char> data) {
		m_socialClubVersion =	(char*)(GetAddressFromInstruction(data.m_address, 0x11));
		m_socialClubEmail =		(char*)(GetAddressFromInstruction(data.m_address, 0x17));
	})) return false;

	return true;
}

SystemData* GetSystemdata() { return &g_systemdata; }