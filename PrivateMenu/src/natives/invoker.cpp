#include "stdafx.h"

#define IGNORE_SPAM

namespace detailSpoofer
{
	extern "C" void* _spoofer_stub();

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first,
				Second second,
				Third third,
				Fourth fourth,
				Pack... pack
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*,
				Pack...
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr,
				pack...
				);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first = First{},
				Second second = Second{},
				Third third = Third{},
				Fourth fourth = Fourth{}
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};
}


template <typename Ret, typename... Args>
static inline auto spoof_call(
	const void* trampoline,
	Ret(*fn)(Args...),
	Args... args
) -> Ret
{
	struct shell_params
	{
		const void* trampoline;
		void* function;
		void* rbx;
	};

	shell_params p{ trampoline, reinterpret_cast<void*>(fn) };
	using mapper = detailSpoofer::argument_remapper<sizeof...(Args), void>;
	return mapper::template do_call<Ret, Args...>((const void*)&detailSpoofer::_spoofer_stub, &p, args...);
}

pGetStatInt OriginalGetStatInt;
vector<uint64_t> Invoker::m_failedInvokes;

void nativeCallContext::setVectorResults() {
	for (uint32_t i = 0; i < m_dataCount; i++) {
		m_script_vectors[i]->x = m_vector_results[i].x;
		m_script_vectors[i]->y = m_vector_results[i].y;
		m_script_vectors[i]->z = m_vector_results[i].z;
	}
	m_dataCount = 0;
}


void Invoker::call(uint64_t hash, NativeContext* cxt) {
	static bool firstNativeCall = true;
	static void* trampolineAddress = 0;
	NativeHandler handler = Natives::getNativeHandlerCache(hash);

	if (handler == nullptr)
	{
		LOG_DEBUG("Could not locate handler for 0x%llx", hash);
	}

	if (firstNativeCall) {
		if (!Hooking::PatternCallback<void>({ "PFSM" /*Penis fairy's masterwork*/, true, 0x0, "FF 23" }, [](void* address) { 
			trampolineAddress = address; // Look for a possible trampoline (jmp rbx / jmp qword ptr [rbx]) in GTA's memory, the return address
			// spoofer needs it in order to make the stub work accordingly.
			firstNativeCall = false; // First occurrence of FF 23 is confirmed RWX in 1.46 (build 1604.1)
		})) {
#ifdef HARD_DEV
			LOG_DEBUG("Native invoker trampoline not found!");
#endif		// We're not going anywhere without that addy sir.
		}
		
	}
#ifdef HARD_DEV
	if (handler == nullptr) {
		LOG_DEBUG("Could not locate handler for 0x%llx", hash);
		*(int*)cxt->getResultPtr() = 0;
	}
#endif

	if (handler) {
		spoof_call(trampolineAddress, handler, static_cast<nativeCallContext*>(cxt)); // Spoofing the return address to a spot in GTA5.exe.
	}
}

//void Invoker::call(uint64_t hash, NativeContext* cxt) {
//	NativeHandler handler = Natives::getNativeHandlerCache(hash);
//	if (handler) {
//		__try {
//			handler(cxt);
//		}
//		__except (true) {
//#ifdef IGNORE_SPAM
//			if (find(m_failedInvokes.begin(), m_failedInvokes.end(), hash) == m_failedInvokes.end())
//				LOG_DEVERROR("[Natives] Failed invoking 0x%p at %p", hash, handler);
//			else m_failedInvokes.push_back(hash);
//#else
//			LOG_ERROR("[Natives] Failed invoking 0x%p at %p", hash, handler);
//#endif
//		}
//	}
//}