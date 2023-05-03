#pragma once
#include <functional>

struct SessionInfoTask {
	uint32_t m_rockstarId;
	std::function<void(uint32_t, bool, const char *, int)> m_callback;
};

struct InfoTaskData {
	uint32_t rockstarId;
	char pad0[0x4];
	uint8_t unk1;
	char pad1[0x7];
	uint8_t unk2;
	char pad2[0x7];
};

class Session
{
public:
	static void GetSessionInfoByRockstarId(uint32_t handle, std::function<void(uint32_t, bool, const char *, int)> callback);
	typedef bool(__fastcall *readSessionInfoResponseType)(__int64);
	typedef char(__fastcall *sendSessionInfoByGamerHandleTaskType)(uint32_t, InfoTaskData *, int, __int64, __int64, __int64, int*);
	static readSessionInfoResponseType __readSessionInfoResponse;
	static sendSessionInfoByGamerHandleTaskType sendSessionInfoByGamerHandleTask;
	static bool __fastcall _readSessionInfoResponse(__int64 a1);
	static std::vector<SessionInfoTask> sessionInfoTasks;

	typedef bool(__fastcall *readSessionInfoType)(__int64 a1, int a2, DWORD *handlePtr, unsigned int a4);
	typedef bool(__fastcall *joinSelectedPlayerType)(__int64 menuPtr, bool a2);
	typedef QWORD *(__fastcall *playerMenuListConstructorType)(__int64 a1, __int64 a2, __int64 a3);

	static readSessionInfoType __readSessionInfo; // original
	static joinSelectedPlayerType joinSelectedPlayer;
	static playerMenuListConstructorType __playerMenuListConstructor;

	static bool _readSessionInfo(__int64 a1, int a2, DWORD *handlePtr, unsigned int a4);
	static QWORD *_playerMenuListConstructor(__int64 a1, __int64 a2, __int64 a3);

	static int handleToFake;
	static __int64 menuPointer;
	static CHostStruct* hostStruct;

public:

	static void Initialize();
	static void Tick();
	static void JoinByRockstarId(int handle);

};