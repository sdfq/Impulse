#pragma once

char* va(String fmt, ...);
char* vaBuff(char* buffer, size_t bufferSize, String fmt, ...);
string toLower(string data);
vector<string> split(string s, string splitter);

struct ImageSection {
	uint32_t hash;
	uint64_t pointer;
	uint64_t size;
};
struct HandleInfo {
	DWORD ownerPid;
	DWORD targetPid;
	HANDLE handle;
	HandleInfo(DWORD _ownerPid, DWORD _targetPid, HANDLE _handle) {
		ownerPid = _ownerPid;
		targetPid = _targetPid;
		handle = _handle;
	}
};
typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;
typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
	DWORD UniqueProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT HandleValue;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;
typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;
typedef enum _OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectTypesInformation,
	ObjectHandleFlagInformation,
	ObjectSessionInformation,
	MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;
typedef struct _OBJECT_NAME_INFORMATION
{
	UNICODE_STRING ObjectName;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;
typedef struct _OBJECT_BASIC_INFORMATION
{
	ULONG Attributes;
	ACCESS_MASK GrantedAccess;
	ULONG HandleCount;
	ULONG PointerCount;
	ULONG PagedPoolCharge;
	ULONG NonPagedPoolCharge;
	ULONG Reserved[3];
	ULONG NameInfoSize;
	ULONG TypeInfoSize;
	ULONG SecurityDescriptorSize;
	LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;
typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccessMask;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	ULONG PoolType;
	ULONG DefaultPagedPoolCharge;
	ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

namespace Utils {
	long long GetFileSize(const char* filename);
	string GetModuleMemoryIntegrityHash(HMODULE hModule, vector<char> originalPE);
	vector<ImageSection> EnumMemorySections(HMODULE hModule, vector<char> originalPE);
	vector<HandleInfo> GetSystemHandles();
	void DoTimedFunction(int* timer, int timeMS, function<void()> function);
	bool IsProcessRunning(LPCTSTR szProcessName);
	DWORD GetProcessIDByName(wstring name);
	void PaintFader(Color* rgbs, Color origin);
	Hash GetJenkinsHashFromString(char* str);

	Hash GetHashKey(String str);
	int PlayerIDFromName(char* name);
	int PlayerIDFromRID(string rid);

	float Lerp(float toEase, float easeFrom, float percent);
	void Ease(float& toEase, float& easeFrom, float multiplier);
	int Clamp(int val, int min, int max);
	float Clamp(float val, float min, float max);
	void Clamp(int *val, int min, int max);
	bool Clamp(float *val, float min, float max);

	template<typename T>
	bool Within(T val, T min, T max) {
		return val <= max && val >= min;
	}

	bool DoesItExistInBlacklist(int idToCheck, String name = "", bool isallplayers = false);
	float degToRad(float degs);
	Vector3 RotateToDirection(Vector3*rot);
	void GetCameraDirection(float *dirX, float *dirY, float *dirZ, Vector3 rotation = Vector3());
	Vector3 get_coords_infront_of_coords(Vector3 pos, Vector3 rot, float dist);
	Vector3 Rotate(Vector3 vec, float angle);
	std::string RandomString(size_t length);

	void ApplyForceToEntity(Entity entity, float x, float y, float z, float offX = 0, float offY = 0, float offZ = 0);
	int GetFreeSeat(int vehicle);

	Color HSVToRGB(float h, float s, float v);

	String BuildBase64Handle(int handle);
	string FixedBuildBase64Handle(const int handle);
	std::string xorStr(std::string data, char *key);
}

namespace Stats {
	void SetStatI(String stat, int value, bool save);
	void SetStatB(String stat, bool value, bool save);
	void SetStatF(String stat, float value, bool save);
	int GetStatI(String stat);
	bool GetStatB(String stat);
	float GetStatF(String stat);
}

class Raycast {
public:
	Entity hitEntity;
	bool hit;
	Vector3 endCoords;
	Vector3 surfaceNormal;
	bool didHitEntity;

	Raycast(int handle);
};

Raycast CastInfront(float length, Vector3 camCoord, int flag);
Vector3 FrontCoords(float length, Vector3 camCoord);