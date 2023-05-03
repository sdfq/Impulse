#include "stdafx.h"
#pragma pack(push,8)
#include <tlhelp32.h>
#pragma pack(pop)
#pragma comment(lib, "Kernel32.lib")

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004
#define SystemHandleInformation 16


char vaBuffer[0x1000];
char* va(String fmt, ...) {
	memset(vaBuffer, 0, 0x1000);
	va_list ap;
	va_start(ap, fmt);
	vsprintf_s(vaBuffer, fmt, ap);
	va_end(ap);
	return vaBuffer;
}

char* vaBuff(char* buffer, size_t bufferSize, String fmt, ...) {
	memset(buffer, 0, bufferSize);
	va_list ap;
	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);
	return buffer;
}

string toLower(string data) {
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

vector<string> split(string s, string splitter) {
	size_t pos;
	vector<string> out;
	while ((pos = s.find(splitter)) != string::npos) {
		string token = s.substr(0, pos);
		out.push_back(token);
		s.erase(0, pos + splitter.length());
	}
	return out;
}
namespace Utils {
	long long GetFileSize(const char* filename) {
		FILE *p_file = NULL;
		p_file = fopen(filename, "rb");
		fseek(p_file, 0, SEEK_END);
		long long size = ftell(p_file);
		fclose(p_file);
		return size;
	}

	string GetModuleMemoryIntegrityHash(HMODULE hModule, vector<char> originalPE) {
		vector<ImageSection> sectionList;
		sectionList = EnumMemorySections(hModule, originalPE);

		string hash = "";

		for (int i = 0; i < sectionList.size(); i++) {
			ImageSection is = sectionList[i];
			if (is.hash == HashAlgorithm::CRC32(".text\x0\x0")) {
				char* ptr = (char*)is.pointer;
				hash = HashAlgorithm::SHA1(ptr, is.size - 1);
				break;
			}
		}

		return hash;
	}

	vector<ImageSection> EnumMemorySections(HMODULE hModule, vector<char> originalPE) {
		vector<ImageSection> output;

		PIMAGE_DOS_HEADER pDOSHeader = NULL;
		PIMAGE_NT_HEADERS pNTHeader = NULL;

		if (originalPE.empty()) {
			pDOSHeader = static_cast<PIMAGE_DOS_HEADER>((PVOID)hModule);
			pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>((PBYTE)hModule + pDOSHeader->e_lfanew);
		} else {
			pDOSHeader = static_cast<PIMAGE_DOS_HEADER>((PVOID)originalPE.data());
			pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>((PBYTE)originalPE.data() + pDOSHeader->e_lfanew);
		}

		IMAGE_SECTION_HEADER *pSectionHeader = reinterpret_cast<IMAGE_SECTION_HEADER*>(pNTHeader + 1);
		for (int i = 0; i < pNTHeader->FileHeader.NumberOfSections; i++) {
			char* section = reinterpret_cast<char*>(pSectionHeader->Name);
			uint64_t start = reinterpret_cast<uint64_t>(hModule) + pSectionHeader->VirtualAddress;

			ImageSection current = { HashAlgorithm::CRC32(string(section)), start, pSectionHeader->Misc.VirtualSize };
			output.push_back(current);
			pSectionHeader += 1;
		}

		return output;
	}

	vector<HandleInfo> GetSystemHandles() {
		vector<HandleInfo> res;
		ULONG size = 0;
		PSYSTEM_HANDLE_INFORMATION handleInfo = nullptr;
		POBJECT_TYPE_INFORMATION objectInfo = (POBJECT_TYPE_INFORMATION)VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		NTSTATUS status = -1;

		DWORD myPid = GetCurrentProcessId();

		/*Get all system handles*/
		while (!NT_SUCCESS(status)) {
			status = Security::NtQuerySystemInformation(SystemHandleInformation, handleInfo, size, &size);
			if (status == STATUS_INFO_LENGTH_MISMATCH) {
				if (handleInfo != nullptr) VirtualFree(handleInfo, 0, MEM_RELEASE);
				handleInfo = (PSYSTEM_HANDLE_INFORMATION)VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
			}
		}
		/*Filters & finds the process handles info*/
		for (ULONG i = 0; i < handleInfo->NumberOfHandles; i++) {
			const PSYSTEM_HANDLE_TABLE_ENTRY_INFO currentHandleInfo = &handleInfo->Handles[i];

			if (currentHandleInfo->UniqueProcessId == myPid)
				continue;

			HANDLE currentHandle = reinterpret_cast<HANDLE>(currentHandleInfo->HandleValue);
			HANDLE duplicatedHandle;
			HANDLE procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, currentHandleInfo->UniqueProcessId);
			if (!DuplicateHandle(procHandle, currentHandle, GetCurrentProcess(), &duplicatedHandle, 0, 0, DUPLICATE_SAME_ACCESS)) {
				CloseHandle(procHandle);
				continue;
			}

			ULONG size;
			if (NT_SUCCESS(Security::NtQueryObject(duplicatedHandle, ObjectTypeInformation, objectInfo, 0x1000, &size))) {
				if (wcsncmp(objectInfo->TypeName.Buffer, L"Process", objectInfo->TypeName.Length + 1) == 0) {
					if (GetProcessId(duplicatedHandle) == myPid) {
						res.push_back(HandleInfo(currentHandleInfo->UniqueProcessId, myPid, currentHandle));
					}
				}
			}

			CloseHandle(duplicatedHandle);
			CloseHandle(procHandle);
		}

		VirtualFree(handleInfo, 0, MEM_RELEASE);
		return res;
	}

	bool IsProcessRunning(LPCTSTR szProcessName) {
		HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (SnapShot == INVALID_HANDLE_VALUE)
			return false;

		PROCESSENTRY32W procEntry = { 0 };
		procEntry.dwSize = sizeof(PROCESSENTRY32W);

		if (!Process32First(SnapShot, &procEntry)) {
			return false;
		}

		do {
			if (wstring(procEntry.szExeFile) == szProcessName)
				return true;
		} while (Process32Next(SnapShot, &procEntry));

		return false;
	}

	DWORD GetProcessIDByName(wstring name) {
		DWORD pid = 0;
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 process;
		ZeroMemory(&process, sizeof(process));
		process.dwSize = sizeof(process);

		if (Process32First(snapshot, &process)) {
			do {
				if (wstring(process.szExeFile) == name) {
					pid = process.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &process));
		}

		CloseHandle(snapshot);

		return pid;
	}

	void DoTimedFunction(int* timer, int timeMS, function<void()> function) {
		if (*timer < MISC::GetGameTimer()) {
			*timer = MISC::GetGameTimer() + timeMS;
			function();
		}
	}
	/*Game*/

	void PaintFader(Color* rgbs, Color origin) {
		switch (rgbs->m_a) {
			case 0:
				rgbs->m_r = origin.m_r;
				rgbs->m_g = origin.m_g;
				rgbs->m_b = origin.m_b;
				rgbs->m_a++;
				break;
			case 1:
				rgbs->m_g++;
				if (rgbs->m_g == 255)
					rgbs->m_a++;
				break;
			case 2:
				rgbs->m_r--;
				if (rgbs->m_r == 0)
					rgbs->m_a++;
				break;
			case 3:
				rgbs->m_b++;
				if (rgbs->m_b == 255)
					rgbs->m_a++;
				break;
			case 4:
				rgbs->m_g--;
				if (rgbs->m_g == 0)
					rgbs->m_a++;
				break;
			case 5:
				rgbs->m_r++;
				if (rgbs->m_r == 255)
					rgbs->m_a++;
				break;
			case 6:
				rgbs->m_b--;
				if (rgbs->m_b == 0)
					rgbs->m_a = 0;
				break;
		}
	}

	Hash GetHashKey(String str) {
		const auto len = strlen(str);
		unsigned int hash, i;
		for (hash = i = 0; i < len; ++i) {
			hash += tolower(str[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}

	uint64_t NumericStringAsInt64(const char *hex) {
		char *_ = 0;
		__int64 ret = _strtoui64(hex, &_, 0);
		return ret;
	}

	int PlayerIDFromName(char* name) {
		Hash hashed = GetHashKey(name);
		for (int i = 0; i < 32; i++) {
			if (GetHashKey(PLAYER::GetPlayerName(i)) == hashed)
				return i;
		}
		return -1;
	}

	int PlayerIDFromRID(string rid) {
		for (int i = 0; i < 32; i++) {
			if (ENTITY::DoesEntityExist(GetPlayer(i).m_ped)) {
				CPed* ped = (CPed*)(PoolManager::GetEntityAddress(GetPlayer(i).m_ped));
				long long ridParamBuffer = atoi(va("%i", atoi(rid.c_str())));
				if (ped != 0) {
					long long rid_ = ped->PlayerInfo->RockstarID;
					if ((rid_ - ridParamBuffer) == 0) {
						return i;
					}
				}
			}
		}
		return -1;
	}

	/*Math*/

	float Lerp(float toEase, float easeFrom, float percent) {
		return (toEase + percent * (easeFrom - toEase));
	}

	void Ease(float& toEase, float& easeFrom, float multiplier) {
		toEase += toEase < easeFrom ? abs(toEase - easeFrom) / multiplier : -abs(toEase - easeFrom) / multiplier;
	}

	int Clamp(int val, int min, int max) {
		return val < min ? min : val > max ? max : val;
	}

	float Clamp(float val, float min, float max) {
		return val < min ? min : val > max ? max : val;
	}

	void Clamp(int *val, int min, int max) {
		*val = *val < min ? min : *val > max ? max : *val;
	}

	bool Clamp(float *val, float min, float max) {
		*val = *val < min ? min : *val > max ? max : *val;
		return *val == min || *val == max;
	}

	float degToRad(float degs) {
		return degs * 3.141592653589793f / 180.f;
	}

	void GetCameraDirection(float *dirX, float *dirY, float *dirZ, Vector3 rotation) {
		float tX, tZ, num;
		Vector3 rot;
		if (rotation == Vector3())
			rot = CAM::GetGameplayCamRot(0);
		else
			rot = rotation;

		tZ = rot.z * 0.0174532924f;
		tX = rot.x * 0.0174532924f;
		num = abs(cos(tX));

		*dirX = (-sin(tZ)) * num;
		*dirY = (cos(tZ)) * num;
		*dirZ = sin(tX);
	}

	Vector3 get_coords_infront_of_coords(Vector3 pos, Vector3 rot, float dist) {
		Vector3 ret;

		float a = pos.x + (RotateToDirection(&rot).x * dist);
		float b = pos.y + (RotateToDirection(&rot).y * dist);
		float c = pos.z + (RotateToDirection(&rot).z * dist);

		ret.x = a;
		ret.y = b;
		ret.z = c;

		return ret;
	}

	Vector3 RotateToDirection(Vector3*rot) {
		float radiansZ = rot->z*0.0174532924f;
		float radiansX = rot->x*0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		Vector3 dir;
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ)))*(double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ))*(double)num);
		dir.z = (float)sin((double)radiansX);
		return dir;
	}

	Vector3 Rotate(Vector3 vec, float angle) {
		float radians = degToRad(angle);
		float sinT = sin(radians);
		float cosT = cos(radians);
		float x = vec.x*cosT - vec.y*sinT;
		float y = vec.x*sinT + vec.y*cosT;
		return { x, y, vec.z };
	}

	void ApplyForceToEntity(Entity entity, float x, float y, float z, float offX, float offY, float offZ) {
		ENTITY::ApplyForceToEntity(entity, 1, x, y, z, offX, offY, offZ, 0, 1, 1, 1, 0, 1);
	}

	int GetFreeSeat(int vehicle) {
		int numSeats = VEHICLE::GetVehicleMaxNumberOfPassengers(vehicle);
		int SeatIndex = -1;  //Driver seat = -1
		while (SeatIndex < numSeats) {
			if (VEHICLE::IsVehicleSeatFree(vehicle, SeatIndex, 1))
				return SeatIndex;
			SeatIndex++;
		}
		return -2;
	}

	Color HSVToRGB(float h, float s, float v) {
		float r = 0, g = 0, b = 0;

		if (s == 0) {
			r = v;
			g = v;
			b = v;
		} else {
			int i;
			double f, p, q, t;

			if (h == 360)h = 0;
			else h = h / 60;

			i = (int)trunc(h);
			f = h - i;

			p = v * (1.0f - s);
			q = v * (1.0f - (s * f));
			t = v * (1.0f - (s * (1.0f - f)));

			switch (i) {
				case 0: r = v; g = t; b = p; break;
				case 1: r = q; g = v; b = p; break;
				case 2: r = p; g = v; b = t; break;
				case 3: r = p; g = q; b = v; break;
				case 4: r = t; g = p; b = v; break;
				default: r = v; g = p; b = q; break;
			}

		}
		return { (int)(r * 255), (int)(g * 255), (int)(b * 255), 255 };
	}

	Hash GetJenkinsHashFromString(char* str) {
		if (str[0] == '0' && str[1] == 'x') {
			char *_ = 0;
			__int64 ret = _strtoui64(str, &_, 0);
			return ret;
		}
		return GetHashKey(str);
	}

	static const string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
	{
		std::string ret;

		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		while (in_len--)
		{
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3)
			{
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i < 4); i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

			for (j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];

			while ((i++ < 3))
				ret += '=';

		}

		return ret;
	}

	string FixedBuildBase64Handle(const int handle)
	{
		BYTE ghPayload[16];
		for (auto i = 0; i < 4; i++)
			ghPayload[i] = handle >> i * 8;

		//SecureZeroMemory(&ghPayload[4], 4);
		ghPayload[8] = 3;
		//SecureZeroMemory(&ghPayload[9], 7);

		return base64_encode(ghPayload, sizeof(handle));
	}

	String BuildBase64Handle(const int handle) {
		BYTE ghPayload[16];

		for (auto i = 0; i < 4; i++) {
			ghPayload[i] = handle >> i * 8;
		}

		SecureZeroMemory(&ghPayload[4], 4); // 4 bytes padding

		ghPayload[8] = 3;

		SecureZeroMemory(&ghPayload[9], 7); // fill the rest

		return EncryptionHelper::Base64Encode(reinterpret_cast<char *>(ghPayload)).c_str();
	}

	std::string xorStr(std::string data, char *key) {
		auto xorstring = data;

		for (auto i = 0; i < xorstring.size(); i++) {
			xorstring[i] = data[i] ^ key[i % strlen(key)];
		}

		return xorstring;
	}

	std::string RandomString(size_t length) {
		auto randchar = []() -> char {
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};
		std::string str(length, 0);
		std::generate_n(str.begin(), length, randchar);
		return str;
	}

	bool DoesItExistInBlacklist(int idToCheck, String name, bool isallplayers) {
		//LOG_PRINT("name coming in: %s", name);
		fstream i(GetConfig()->GetBlacklistPath());
		json j;
		if (i) {
			j = json::parse(i);

			for (int c = 0; c < j.size(); c++) {
				bool rockstar = false, socialclub = false; uint32_t id = 0;
				string JName = "";

				if (j[c][3] == 1) {
					rockstar = true;
					id = (uint32_t)(_atoi64(j[c][0].get<string>().c_str()));

				} else {
					socialclub = true;
					JName = j[c][0].get<string>();
					//LOG_PRINT("jName: %s socialclub: %i", JName, socialclub);
				}

				if (rockstar) {
					if (idToCheck == 0) continue;
					if (id == idToCheck) {
						if (!isallplayers) GetRenderer()->NotifyMap(va("%i is already within overseer", id));
						return true;
					}
				}
				else if (socialclub) {

					//LOG_PRINT("jName: %s name: %s", JName, name);
					if (JName == name) {
						if (!isallplayers) GetRenderer()->NotifyMap(va("%s is already within overseer", JName));
						return true;
					}

				}
			}
		}
		return false;
	}

}

namespace Stats {
	void SetStatI(String stat, int value, bool save) {
		if (HUD::_GetTextSubstring(stat, 0, 5) == "MPPLY")
			STATS::StatSetInt(Utils::GetHashKey(stat), value, save);
		else {
			char sbuf[50];
			int stat_r;
			STATS::StatGetInt(Utils::GetHashKey("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, stat);
			STATS::StatSetInt(Utils::GetHashKey(sbuf), value, save);
		}
	}
	void SetStatB(String stat, bool value, bool save) {
		if (HUD::_GetTextSubstring(stat, 0, 5) == "MPPLY")
			STATS::StatSetBool(Utils::GetHashKey(stat), value, save);
		else {
			char sbuf[50];
			int stat_r;
			STATS::StatGetInt(Utils::GetHashKey("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, stat);
			STATS::StatSetBool(Utils::GetHashKey(stat), value, save);
		}
	}
	void SetStatF(String stat, float value, bool save) {
		if (HUD::_GetTextSubstring(stat, 0, 5) == "MPPLY")
			STATS::StatSetFloat(Utils::GetHashKey(stat), value, save);
		else {
			char sbuf[50];
			int stat_r;
			STATS::StatGetInt(Utils::GetHashKey("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, stat);
			STATS::StatSetFloat(Utils::GetHashKey(sbuf), value, save);
		}
	}
	int GetStatI(String stat) {
		if (HUD::_GetTextSubstring(stat, 0, 5) == "MPPLY") {
			int stat_get;
			STATS::StatGetInt(Utils::GetHashKey(stat), &stat_get, 1);
			return stat_get;
		} else {
			char sbuf[50];
			int stat_r;
			STATS::StatGetInt(Utils::GetHashKey("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, stat);
			int stat_get;
			STATS::StatGetInt(Utils::GetHashKey(sbuf), &stat_get, 1);
			return stat_get;
		}
	}
	bool GetStatB(String stat) {
		if (HUD::_GetTextSubstring(stat, 0, 5) == "MPPLY") {
			bool stat_get;
			STATS::StatGetBool(Utils::GetHashKey(stat), &stat_get, 1);
			return stat_get;
		} else {
			char sbuf[50];
			int stat_r;
			STATS::StatGetInt(Utils::GetHashKey("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, stat);
			bool stat_get;
			STATS::StatGetBool(Utils::GetHashKey(sbuf), &stat_get, 1);
			return stat_get;
		}
	}
	float GetStatF(String stat) {
		if (HUD::_GetTextSubstring(stat, 0, 5) == "MPPLY") {
			float stat_get;
			STATS::StatGetFloat(Utils::GetHashKey(stat), &stat_get, 1);
			return stat_get;
		} else {
			char sbuf[50];
			int stat_r;
			STATS::StatGetInt(Utils::GetHashKey("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
			snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, stat);
			float stat_get;
			STATS::StatGetFloat(Utils::GetHashKey(sbuf), &stat_get, 1);
			return stat_get;
		}
	}
}

Raycast CastInfront(float length, Vector3 camCoord, int flag) {
	Vector3 infront;
	Utils::GetCameraDirection(&infront.x, &infront.y, &infront.z);

	Vector3 target = Vector3(camCoord.x + (infront.x * length), camCoord.y + (infront.y * length), camCoord.z + (infront.z * length));

	return Raycast(SHAPETEST::_StartShapeTestRay(camCoord.x, camCoord.y, camCoord.z, target.x, target.y, target.z, flag, GetLocalPlayer().m_ped, 0));
}

Vector3 FrontCoords(float length, Vector3 camCoord) {
	Vector3 infront;
	Utils::GetCameraDirection(&infront.x, &infront.y, &infront.z);

	Vector3 target = Vector3(camCoord.x + (infront.x * length), camCoord.y + (infront.y * length), camCoord.z + (infront.z * length));
	return target;
}

Raycast::Raycast(int handle) {
	Entity hitEn;
	SHAPETEST::GetShapeTestResult(handle, &hit, &endCoords, &surfaceNormal, &hitEn);
	if (ENTITY::DoesEntityExist(hit)) {
		if (hitEntity != PLAYER::PlayerPedId())
			hitEntity = hitEn;
		else
			hitEntity = NULL;
	}
	didHitEntity = hitEntity != NULL;
}

