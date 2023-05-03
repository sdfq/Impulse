#include "stdafx.h"

char Config::m_appdata[260];
char Config::m_documents[260];
char Config::m_log[260];
char Config::m_ytd[260];
char Config::m_VFX[260];
char Config::m_data[260];
char Config::m_login[260];
char Config::m_config[260];
char Config::m_themes[260];
char Config::m_plugins[260];
char Config::m_outfits[260];
char Config::m_handling[260];
char Config::m_vehicles[260];
char Config::m_ytdConfig[260];
char Config::m_ytdHeader[260];
char Config::m_languages[260];
char Config::m_recoveries[260];
char Config::m_teleports[260];
char Config::m_blacklist[260];
char Config::m_profiles[260];
char Config::m_namesave[260];
char Config::m_playerlogs[260];
char Config::m_chatdumps[260];
char Config::m_ridspoof[260];
char Config::m_messaging[260];
char Config::m_mapmods[260];

Config g_config;

Config* GetConfig() { return &g_config; }