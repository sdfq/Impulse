#include "stdafx.h"

vector<Hooking::Hook>				Hooking::m_hooks;
vector<Hooking::HookedScriptNative>	Hooking::m_hookedScriptNatives;

/*Initialize Minhook*/
bool Hooking::Initialize(){
	if (MH_Initialize() != MH_OK) LOG_ERROR("MH failed to initialize");
	else {
		LOG_DEBUG("[Hooking] MH initialized");
		return true;
	}
	return false;
}

bool Hooking::ScriptTableCallback(String scriptName, String name, void(*funcptr)(Script::ScriptTableItem* script))
{
	Script::ScriptTableItem* script = Backend::GetScriptTable()->FindScript(scriptName);
	if (IsValidAddress(script, name, false)== STATUS_SUCCESS) funcptr(script);
	else {
		LOG_ERROR("[Scripts] %s scriptTable callback failed", name);
		Backend::Cleanup();
		return false;
	}
	return true;
}

/*Hook natives in scripts*/
bool Hooking::HookScriptNative(Script::ScriptTableItem* script, UINT64 nativeHash, LPVOID function, String name) {
	if (script->header != nullptr) {
		const auto nativeOffset = reinterpret_cast<UINT64>(Natives::getNativeHandlerCache(nativeHash));
		if (nativeOffset != NULL) {
			for (auto i = 0; i < script->header->nativeCount; i++) {
				if (script->header->nativeOffset[i] == nativeOffset) {
					HookedScriptNative thisHook = { name, script, (uint64_t)nativeHash, (uint64_t)script->header->nativeOffset[i] , i };
					m_hookedScriptNatives.push_back(thisHook);
					script->header->nativeOffset[i] = (UINT64)function;
					LOG_DEBUG("[Hooking] Hooked %s", name);
					return true;
				}
			}
		}
	}
	LOG_WARN("[Hooking] Failed to hook %s", name);
	return false;
}

/*Unhook natives in scripts*/
bool Hooking::UnhookScriptNative(HookedScriptNative hookedNative)
{
	if (hookedNative.m_script->header != nullptr) {
		if (hookedNative.m_script->header->nativeOffset[hookedNative.m_nativePos] != 0) {
			if (hookedNative.m_origFunc != 0) {
				hookedNative.m_script->header->nativeOffset[hookedNative.m_nativePos] = hookedNative.m_origFunc;
				return true;
			}
		}
	}
	return false;
}

void Hooking::Cleanup()
{
	for(HookedScriptNative& hsn : m_hookedScriptNatives){
		if (!UnhookScriptNative(hsn))LOG_ERROR("Failed to unhook: %s", hsn.m_nativeHash);
		else LOG_DEBUG("[Hooking] Unhooked %s", hsn.m_name);
	}
	for(Hook& hook : m_hooks){
		if (MH_QueueDisableHook(hook.m_hash) != MH_OK)LOG_ERROR("[Hooking] Failed to unhook: %s", hook.m_name);
		else LOG_DEBUG("[Hooking] Unhooked %s", hook.m_name);
	}
	MH_ApplyQueued();

	/*Uninitialize MinHook*/
	if (MH_Uninitialize() != MH_OK) LOG_ERROR("[Hooking] Disabling MH failed");
	else LOG_DEBUG("[Hooking] Disabled MH");
}