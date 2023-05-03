#include "stdafx.h"

namespace ReClass {
	CWorld* GetWorld() { return *(CWorld**)Backend::GetWorldPtr(); }
	CNetworkPlayerManager* GetNetworkPlayerManager() { return *(CNetworkPlayerManager**)Backend::GetNetworkPlayerManagerPtr(); }
}