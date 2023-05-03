#pragma once

class SystemData
{
public:
	String m_gameName;
	String m_operatingSystem;
	String m_CPUSpeed;
	String m_CPUBrand;
	String m_directXVersion;
	String m_VRam;
	String m_GPU;
	String m_motherBoard;
	String m_gameLanguage;
	String m_gameBuild;
	String m_gameOnlineVersion;
	String m_gameLauncherName;
	String m_gameExecutableName;
	String m_socialClubVersion;
	String m_socialClubEmail;

	bool Initialize();
};

SystemData* GetSystemdata();