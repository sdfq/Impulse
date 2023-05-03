#pragma once

struct SavedRemoteEvent {
	int64_t m_args[10];
	bool m_redirected;
	int m_count;
};

class NetEvent {
public:
	static bool Initialize();

	struct Vars {
		bool notifyER = true;
		bool notifyNE = true;
		bool notifyPE = true;
		bool notifySE = true;
		bool notifyAT = true;
		bool stat = true;
		bool control;
		bool weatherTime = true;
		bool redirectNetEvents;
		bool redirectScriptEvents;
		bool smartProtex = true;
		bool voteKick;
		bool wantedLevel;
		bool clearTasks;
		bool takeWeapons;
		bool giveWeapons;
		bool explosions;
		bool particleEffects;
		bool sound;
		bool scriptEvents;
		bool pickups;
		bool evolveBlock;
		bool rockstarid;
		bool blockpednet;
		bool blockobjectnet;
		bool blockplanenet;
		bool blockautomobilenet;
		bool blockbikenet;
		bool blockhelinet;
		bool IsNetObjSaved;
		bool ePqGPRWkeLpOicfiJfNO;
		bool blockalltransactions;
		bool bypassweatherchangequick;
		bool blockallnetevents;
		bool blockallncriptevents;
		bool logallnetevents;
	};

	static Vars vars;
	static int SavedRemoteEventCount;
	static SavedRemoteEvent SavedRemoteEvents[10];
	static vector<int64_t> EventsWhitelist;
	static String GetTeleportLocation(int id);
};

extern bool IsNetObjSaved(int NetID, Player* Owner = NULL);
extern int GetEntityNetID(Entity entity);