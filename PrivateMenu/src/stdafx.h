#pragma once

#pragma warning(disable: 4091)
#pragma warning(disable: 4838)
#pragma warning(disable: 4311)
#pragma warning(disable: 4302)
#pragma warning(disable: 4191)
#pragma warning(disable: 4018)
#pragma warning(disable: 4305)
#pragma warning(disable: 4800)
#pragma warning(disable: 4804)
#pragma warning(disable: 4305)
#pragma warning(disable: 4551)
#pragma warning(disable: 4390)
#pragma warning(disable: 4715)

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#define HARD_DEVs // for shit we don't want compiled unless dev is defined
#define TESTER_ONLYs // for when we only want testers using it

#define CRASH_DBGs // enables detailed startup log

/*Windows includes*/
#include <windows.h>
#include <windowsx.h>

#include <string>
#include <xstring>

#include <tlhelp32.h>

#include <sstream>
#include <fstream>
#include <filesystem>
#include <iostream>

#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <chrono>

#include <memory>
#include <Psapi.h>

#include <timeapi.h>
#pragma comment(lib, "winmm.lib")

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

/*Json*/
#include "util/json.h"
using namespace nlohmann;

/*Minhook*/
#include "minhook.h"

template <typename T, size_t N>
constexpr size_t NUMOF(T(&)[N]) { return N; }

/*Util*/
#include "util/types.h"
#include "util/status.h"
#include "util/utils.h"
#include "util/config.h"
#include "util/log.h"
#include "util/profiler.h"
#include "util/threadPool.h"
#include "util/script.h"
#include "util/fiberManager.h"
#include "util/fiberPool.h"
#include "util/systemData.h"
#include "util/translationString.h"
#include "util/pugiconfig.hpp"
#include "util/pugixml.hpp"

/*Auth*/
#include "authorization/cryptopp/md5.h"
#include "authorization/cryptopp/cryptlib.h"
#include "authorization/cryptopp/hex.h"
#include "authorization/cryptopp/osrng.h"
#include "authorization/cryptopp/base64.h"
#include "authorization/cryptopp/filters.h"
#include "authorization/cryptopp/des.h"
#include "authorization/cryptopp/modes.h"
#include "authorization/cryptopp/secblock.h"
#include "authorization/cryptopp/crc.h"
#include "authorization/winhttpclient.h"
#include "authorization/network.h"
#include "authorization/encryption.h"
#include "authorization/serverEvent.h"
#include "authorization/authorization.h"

/*Memory*/
#include "util/memory/pattern.h"
#include "util/memory/patternBatch.h"
#include "util/memory/memory.h"
#include "util/memory/VPBypass.h"

/*Natives*/
#include "natives/crossmap.h"
#include "natives/invoker.h"
#include "natives/natives.h"

/*Pools*/
#include "backend/pools/poolManager.h"
#include "backend/pools/entityPool.h"
#include "backend/pools/objectPool.h"
#include "backend/pools/pedPool.h"
#include "backend/pools/vehiclePool.h"

/*ReClass*/
#include "util/memory/reclass.h"

/*Backend*/
#include "backend/patterns.h"
#include "backend/backendHooking.h"
#include "backend/backendMain.h"
#include "backend/backendNatives.h"
#include "backend/backendSecurity.h"
#include "backend/backendAnticheat.h"
#include "backend/backendProtection.h"
#include "backend/backendModelSwap.h"
#include "backend/backendExplosions.h"

/*Renderer*/
#include "menu/renderer.h"

/*Input*/
#include "util/input/keyboard.h"
#include "util/input/mouse.h"
#include "util/input/controller.h"
#include "util/input/input.h"
#include "menu/util/vehicles.h"
#include "menu/util/menuInput.h"
#include "menu/util/hotkeyManager.h"
#include "menu/util/contextMenu.h"
#include "menu/util/scaleform.h"
#include "menu/util/VFX.h"
#include "menu/util/scriptHookV.h"

/*Menu Util*/
#include "menu/util/playerManager.h"
#include "menu/util/entityControl.h"
#include "menu/util/oceanManager.h"
#include "menu/util/fingerOfGod.h"
#include "menu/util/netEvent.h"
#include "menu/util/animatedYtd.h"
#include "menu/util/transaction.h"
#include "menu/util/session.h"
#include "menu/util/socialclub.h"
#include "menu/util/inventoryTypes.h"
#include "menu/util/inventory.h"

/*Option*/
#include "menu/options/option.h"
#include "menu/options/keyOption.h"
#include "menu/options/colorOption.h"
#include "menu/options/breakOption.h"
#include "menu/options/buttonOption.h"
#include "menu/options/toggleOption.h"
#include "menu/options/numberOption.h"
#include "menu/options/scrollOption.h"
#include "menu/options/vehicleOption.h"
#include "menu/options/submenuOption.h"

/*Submenu*/
#include "menu/submenu.h"
#include "menu/submenuHandler.h"

/*UI*/
#include "UI/component.h"
#include "UI/window.h"
#include "UI/frame.h"
#include "UI/screenPanel.h"
#include "UI/components/input/textInputComponent.h"
#include "UI/components/profilerComponent.h"
#include "UI/components/playerInfoComponent.h"
#include "UI/components/systemdataComponent.h"
#include "UI/components/textBoxComponent.h"
#include "UI/components/vehicleComponent.h"
#include "UI/components/loggerComponent.h"
#include "UI/windowManager.h"

/*Menu*/
#include "menu/globals.h"
#include "menu/menu.h"
#include "menu/util/menuFunctions.h"
