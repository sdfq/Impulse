#pragma once

class Global {
private:
	void* _handle;

public:
	Global(int index) : _handle(&Backend::GetGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF]) {}
	Global(void* p) : _handle(p) {}
	Global(const Global& copy) : _handle(copy._handle) {}

	Global At(int index) const {
		return Global(reinterpret_cast<void**>(this->_handle) + (index));
	}

	Global At(int index, int size) const {
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get() {
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As() {
		return *this->Get<T>();
	}
};

namespace SCRIPTEVENTS {
	static const int64_t START_TYPING = 3033046699;
	static const int64_t STOP_TYPING = 2994416968;
	static const int64_t PAUSE_ENTER = 2329576889; // 1.46 = 1613784162
	static const int64_t PAUSE_LEAVE = 457878498;

	static const int64_t JOINED_PLAYER = 1829532170; // 1.46 = 256098994

	static const int64_t ECLIPSETELEPORT = 1365267338; // 1.46 = 1000837481
	static const int64_t INCREASERP = -181444979; // NOT USED
	static const int64_t KICKFROMVEHICLE = 1796063150; // 1.46 = 325218053
	static const int64_t FORCEINTOMISSION = -2145536660; // 1.46 = -15432926
	static const int64_t NOTIFICATION = 111286607; // 1.46 = 713068249
	static const int64_t NOTIFICATION2 = -270262485; // 1.46 = 1009196241

	static const int64_t NONHOSTKICK1 = 423635655; // 1.46 = -120668417
	static const int64_t NONHOSTKICK2 = 400031869; // 1.46 = 1222825035
	static const int64_t NONHOSTKICK3 = -510378036; // 1.46 = 769347061
	static const int64_t NONHOSTKICK4 = -815817885; // 1.46 = 999090520
	static const int64_t NONHOSTKICK5 = -1264063129; // 1.46 = 1642479322
	static const int64_t NONHOSTKICK6 = -941739545; // 1.46 = 2055958901

	static const int64_t KICKTOSP1 = -1424895288; // 1.46 = 994306218
	static const int64_t KICKTOSP2 = 1314698923; // 1.46 = -928998106
	static const int64_t KICKTOSP3 = -158670784; // 1.46 = 1153942884

	static const int64_t CEOKICK = -606032195; // 1.46 = -1190833098
	static const int64_t CEOBAN = -326132866; // 1.46 = 360381720
	static const int64_t INVITE = 715645088; // 1.46 = -175474624
	static const int64_t GOTR = 1848739240; // 1.46 = 1344161996
	static const int64_t GNEVERWANTED = 685727305; // 1.46 = 1475266103
	static const int64_t GCOPSTURNBLINDEYE = -1635856102; // 1.46 = 1555129594

	static const int64_t SPECTATINGMESSAGE = 446273009; // 1.46 = 436170208
	static const int64_t FACECAMERAFORWARD = -42615386; // 1.46 = 566035618
	static const int64_t FACECAMERAFORWARD2 = 745899999; // 1.46 = -1432407380

	static const int64_t DISPLAYINSURANCEMESSAGE = 252265430; // 1.46 = 380155193
	static const int64_t TRANSACTIONERRORSPAM = -1049031463;
};

namespace Globals {
	static const int LEVEL = 289559; // 1.46 = 287850
	static const int MPINSP = 4267883; // UPDATED
	static const int PLAYER_BASE = 1589819; // 1.46 = 1589747
	static const int PLAYER_PADDING = 818; // 1.46 = 790
	static const int PLAYER_EXTRA = 237; // 1.46 = 237
	static const int PLAYER_OFFSET = 211; // SAME
	static const int PLAYER_OFFSET_WALLET = 3; // SAME
	static const int PLAYER_OFFSET_TOTAL = 56; // SAME
	static const int PLAYER_OFFSET_XP = 5; // SAME
	static const int PLAYER_OFFSET_LEVEL = 6; // SAME
	static const int PLAYER_OFFSET_KD = 26; // SAME
	static const int PLAYER_OFFSET_KILLS = 28; // SAME
	static const int PLAYER_OFFSET_DEATHS = 29; // SAME
	static const int OTR_BASE = 2424047; // 1.46 = 2423801
	static const int OTR_PADDING = 416; // 1.46 = 413
	static const int OTR_OFFSET = 200; // SAME
	static const int OTR_PLAYERS_OFFSET = 222; // SAME
	static const int EFFECT_TIME_BASE = 2437364; // 1.46 = 2437022
	static const int TIME_BASE = 2528542; // 1.46 = 2524719
	static const int TIME_OFFSET = 70; // SAME
	static const int NOIDLEKICK = 1371947; // 1.46 = 1368245
	static const int TESTOSTERONE_OFFSET = 3880; // 1.46 = 3876
	static const int BLINDEYEOFFSET1 = 4546; // 1.46 = 4542
	static const int BLINDEYEOFFSET2 = 4549; // 1.46 = 4545
	static const int SNOW_BASE = 262145; // SAME
	static const int SNOW_OFFSET = 4721; // SAME

	/*Interaction menu instructional queue*/
	static const int IMIQUEUE_BASE = 17411; // 1.46 = 17367
	static const int IMIQUEUE_OFFSET = 4769; // 1.46 = 4767
	static const int IMIQUEUE_OFFSET2 = 4770; // 1.46 = 4768
	static const int PHONE_BASE = 14553; // UPDATED
	static const int PHONE_BOOL1 = 14725; // 1.46 = 14681
	static const int PHONE_POSSET = 14481; // 1.46 = 14441
	static const int PHONE_POSGET = 14498; // 1.46 = 14458
	static const int PHONE_BITSET1 = 2424; // 1.46 = 2384
	static const int PHONE_BITSET2 = 2423; // 1.46 = 2383

	static const int REMOTE_BASE = 1626536; // 1.46 = 1625435
	static const int REMOTE_SIZE = 603; // 1.46 = 560
	static const int REMOTE_OFFSET = 529; // 1.46 = 491

	/* Added before casino dlc */
	static const int NOIDLEKICK2 = 1165; // 1.46 = 1165
	static const int NOIDLEKICK3 = 1149; // 1.46 = 1149
};

