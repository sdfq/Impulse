#pragma once

class Hooking {
public:
	struct Hook {
		LPVOID m_hash;
		String m_name;
	};

	struct HookedScriptNative {
		String m_name;
		Script::ScriptTableItem* m_script;
		uint64_t m_origFunc;
		uint64_t m_nativeHash;
		int m_nativePos;
	};

	template<typename T>
	struct CallbackData {
		T* m_address;
		String m_name;
	};

	/*Hook*/
	template <typename T>
	static bool HookFunctionQueued(LPVOID hash, LPVOID hookFunction, T** trampoline, String name, bool addToLastLine = true) {
		if (*reinterpret_cast<LPVOID*>(trampoline) != NULL) return true;
		MH_STATUS createHookStatus = MH_UNKNOWN;

		if (hash) {
			Backend::SetHooking(true);
			createHookStatus = MH_CreateHook(hash, hookFunction, reinterpret_cast<LPVOID*>(trampoline));
			if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED))) {
				if ((createHookStatus = MH_QueueEnableHook(hash)) == MH_OK) {
					Backend::SetHooking(false);
					if (addToLastLine)LOG_ADD(" -> queued");
					else LOG_DEBUG("[Hooking] Queued %s", name);

					m_hooks.push_back({ hash, name });
					return true;
				}
			}
		}
		Backend::SetHooking(false);
		if (addToLastLine) {
			LOG_ADDC(ConsoleForeground::RED, " -> queue failed");
			#ifdef HARD_DEV
			LOG_ADDC(ConsoleForeground::RED, " (%s)", MH_StatusToString(createHookStatus));
			#endif

		} else LOG_WARN("[Hooking] Failed to queue %s (%i)", name, createHookStatus);

		return false;
	}

	static void ApplyQueue() {
		MH_ApplyQueued();
		LOG_DEBUG("[Hooking] Executed queue");
	}


	/*Hook*/
	template <typename T>
	static bool HookFunction(LPVOID hash, LPVOID hookFunction, T** trampoline, String name, bool addToLastLine = true) {
		if (*reinterpret_cast<LPVOID*>(trampoline) != NULL) return true;
		MH_STATUS createHookStatus = MH_UNKNOWN;

		if (hash) {
			Backend::SetHooking(true);
			createHookStatus = MH_CreateHook(hash, hookFunction, reinterpret_cast<LPVOID*>(trampoline));
			if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED))) {
				if ((createHookStatus = MH_EnableHook(hash)) == MH_OK) {
					Backend::SetHooking(false);
					if (addToLastLine)LOG_ADD(" -> hooked");
					else LOG_DEBUG("[Hooking] Hooked %s", name);

					m_hooks.push_back({ hash, name });
					return true;
				}
			}
		}
		Backend::SetHooking(false);
		if (addToLastLine) {
			LOG_ADDC(ConsoleForeground::RED, " -> hook failed");
			#ifdef HARD_DEV
			LOG_ADDC(ConsoleForeground::RED, " (%s)", MH_StatusToString(createHookStatus));
			#endif

		} else LOG_WARN("[Hooking] Failed to hook %s (%i)", name, createHookStatus);

		return false;
	}

	template <typename T, typename C>
	static bool HookFunction(Hooking::CallbackData<C>& data, LPVOID hookFunction, T** trampoline, bool addToLastLine = true) {
		return HookFunction(data.m_address, hookFunction, trampoline, data.m_name, addToLastLine);
	}

	static void Unhook(String name) {
		for (auto& hook : m_hooks) {
			if (strcmp(hook.m_name, name) == 0) {
				if (MH_DisableHook(hook.m_hash) != MH_OK)LOG_ERROR("[Hooking] Failed to unhook: %s", hook.m_name);
				else LOG_DEBUG("[Hooking] Unhooked %s", hook.m_name);
			}
		}
	}

	/*Hook natives in scripts*/
	static bool HookScriptNative(Script::ScriptTableItem* script, UINT64 nativeHash, LPVOID function, String name);
	static bool UnhookScriptNative(HookedScriptNative hookedNative);

	static bool Initialize();
	static void Cleanup();

	static bool ScriptTableCallback(String scriptName, String name, void(*funcptr)(Script::ScriptTableItem* script));

	template<typename T>
	static bool PatternCallback(PStruct pattern, void(*funcptr)(T* address)) {
		T* address = SetAddressTypeForUse<char>(Pattern::Scan(pattern.m_name.c_str(), pattern.m_pattern), pattern.m_offset);
		switch (IsValidAddress<T>(address, pattern.m_name, pattern.m_important, pattern.m_offset)) {
		case STATUS_SUCCESS: funcptr(address); return true; break;
		case STATUS_WARNING: if (!pattern.m_important) { return true; }
		case STATUS_FATAL: LOG_ERROR("[Pattern] %s pattern callback failed", pattern.m_name); Backend::Cleanup(); break;
		}
		return false;
	}

	template<typename T>
	static bool PatternCallback(PStruct pattern, bool(*funcptr)(T* address)) {
		T* address = SetAddressTypeForUse<char>(Pattern::Scan(pattern.m_name.c_str(), pattern.m_pattern), pattern.m_offset);
		switch (IsValidAddress<T>(address, pattern.m_name, pattern.m_important, pattern.m_offset)) {
		case STATUS_SUCCESS: if (funcptr(address))return true; else if (pattern.m_important) { LOG_ERROR("[Pattern] %s pattern callback failed", pattern.m_name); Backend::Cleanup(); } break;
		case STATUS_WARNING: if (!pattern.m_important) { return true; }
		case STATUS_FATAL:  LOG_ERROR("[Pattern] %s pattern callback failed", pattern.m_name); Backend::Cleanup(); return false; break;
		}
		return false;
	}

	//I couldn't use function above because then it doesn't know what to use anymore, so do it the ugly way
	template<typename T>
	static bool PatternCallback1(PStruct pattern, std::function<void(T *)> funcptr) {
		T* address = SetAddressTypeForUse<char>(Pattern::Scan(pattern.m_name.c_str(), pattern.m_pattern), pattern.m_offset);
		switch (IsValidAddress<T>(address, pattern.m_name, pattern.m_important, pattern.m_offset)) {
		case STATUS_SUCCESS: funcptr(address); return true;
		case STATUS_WARNING: if (!pattern.m_important) { return true; }
		case STATUS_FATAL:  LOG_ERROR("[Pattern] %s pattern callback failed", pattern.m_name); Backend::Cleanup(); return false; break;
		}
		return false;
	}
   
	template<typename T>
	static bool ServerPatternCallback(String name, function<void(CallbackData<T> data)> funcptr) {
		PStruct* pStruct = GetAuth()->GetSignature(name);
		if (pStruct == nullptr) return false;

		CallbackData<T> blank = { SetAddressTypeForUse<T>(Pattern::Scan(pStruct->m_name.c_str(), pStruct->m_pattern), pStruct->m_offset) , name };

		switch (IsValidAddress<T>(blank.m_address, blank.m_name, pStruct->m_important, pStruct->m_offset)) {
		case STATUS_SUCCESS: pStruct->clear(); funcptr(blank);  return true; break;
		case STATUS_WARNING: if (!pStruct->m_important) { pStruct->clear();  return true; }
		case STATUS_FATAL: LOG_ERROR("[Pattern] %s pattern callback failed", pStruct->m_name); pStruct->clear(); Backend::Cleanup(); break;
		}
		return false;
	}

	template<typename T>
	static bool ServerPatternCallbackBool(String name, function<bool(CallbackData<T> data)> funcptr) {
		PStruct* pStruct = GetAuth()->GetSignature(name);
		if (pStruct == nullptr) return false;

		CallbackData<T> blank = { SetAddressTypeForUse<T>(Pattern::Scan(pStruct->m_name.c_str(), pStruct->m_pattern), pStruct->m_offset) ,name };

		switch (IsValidAddress<T>(blank.m_address, blank.m_name, pStruct->m_important, pStruct->m_offset)) {
		case STATUS_SUCCESS: if (funcptr(blank)) { pStruct->clear(); return true; } else if (pStruct->m_important) { LOG_ERROR("[Pattern] %s pattern callback failed", pStruct->m_name); pStruct->clear(); Backend::Cleanup(); }  break;
		case STATUS_WARNING: if (!pStruct->m_important) { pStruct->clear(); return true; }
		case STATUS_FATAL: LOG_ERROR("[Pattern] %s pattern callback failed", pStruct->m_name); Backend::Cleanup(); pStruct->clear(); return false;
		}
		return false;
	}

	static void* ReplaceInstructionAddress(void* wherePtr, void* toPtr, const int opSize = 3, const int opLength = 7) {
		const auto delta = static_cast<DWORD>(reinterpret_cast<DWORD64>(toPtr) - reinterpret_cast<DWORD64>(wherePtr) - opLength);
		const auto original = reinterpret_cast<void *>(reinterpret_cast<DWORD64>(wherePtr) + *reinterpret_cast<int *>(reinterpret_cast<DWORD64>(wherePtr) + opSize) + opLength);

		DWORD op;
		VirtualProtect(wherePtr, 7, PAGE_READWRITE, &op);
		*reinterpret_cast<DWORD *>(reinterpret_cast<DWORD64>(wherePtr) + opSize) = delta;
		VirtualProtect(wherePtr, 7, op, &op);

		return original;
	}

private:
	static vector<Hook> m_hooks;
	static vector<HookedScriptNative> m_hookedScriptNatives;

};