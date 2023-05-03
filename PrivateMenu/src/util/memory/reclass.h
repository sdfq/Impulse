#pragma once
#pragma pack(push, 1)

// Generated using ReClassEx

class CWorld;
class CPed;
class CVehicle;
class CVehicleDeformation;
class CHandlingData;
class CPlayerInfo;
class CWeaponManager;
class CWeapon;
class CAmmoInfo;
class CVehicleDrawHandler;
class CVehicleSteamRenderGFX;
class CVehicleStreamRender;
class CWeaponInfo;
class CReplayInterface;
class CCameraInterface;
class CVehicleInterface;
class CPedInterface;
class CPickupInterface;
class CObjectInterface;
class CPickupList;
class CVehList;
class CObjectList;
class CObjectHandle;
class CAimingInfo;
class CNetGamePlayer;
class CAIHandlingInfo;
class CSubHandlingData;
class CFlyingHandlingData;
class CBoatHandlingData;
class CBikeHandlingData;
class CModelInfo;
class CPedDrawHandler;
class CVehicleWeaponHandlingData;
class CNetEventInfo;
class CNetEventVTable;
class CMetric;
class CFragInst;
class CArcheTypeDamp;
class CFragType;
class CFragPhysicsLODGroup;
class CFragPhysicsLOD;
class CGroupNames;
class Groups;
class phBoundComposite;
class CEntitySkeleton;
class crSkeletonData;
class NativeMatrix;
class crSkeletonBoneDataArray;
class crSkeletonBoneData;
class CHostStruct;

typedef unsigned __int64 QWORD;

class CDrawable {
public:
	char _0x0000[0x28];
	BYTE m_type; //0x28
	char _0x0029[0x53];
	float m_width; //0x7C
	char _0x0080[0xC];
	float m_height; //0x86
	Vector3_t m_position; //0x90
	float m_anotherX;
	char _0x00A0[0x10];
	int m_lod;

	Vector3 GetPosition() {
		Vector3 pos;
		pos.x = m_position.x;
		pos.y = m_position.y;
		pos.z = m_position.z;

		return pos;
	}

	void SetPosition(Vector3 pos) {
		m_position.x = pos.x;
		m_position.y = pos.y;
		m_position.z = pos.z;
		m_anotherX = pos.x;
	}

	bool IsDrawable() {
		return m_type == 1;
	}

	bool IsScaleAccurate() {
		return m_width == m_height;
	}

	float GetEstimatedScale() {
		return m_width > m_height ? m_width : m_height;
	}

	Vector2 GetScale() {
		return Vector2(m_width, m_height);
	}

	void AddToScale(float scale) {
		// maintain aspect-ratio?
		m_width = m_width + scale;
		m_height = m_height + scale;
	}

	void SetScale(float scale) {
		// i think that the width and height of an entity is defaulted at 1
		m_width = scale;
		m_height = scale;
	}

	int GetLod() {
		return m_lod;
	}

	void SetLod(int lod) {
		m_lod = lod;
	}
};

class CWorld {
public:
	char pad_0x0000[0x8]; //0x0000
	CPed* LocalPed; //0x0008 

}; //Size=0x0010

class CWorldManager {
public:
	char pad_0x0000[0xEA8];
	float WindSpeed;
};

struct CPedVTable {
	char pad_0x0[48];
	__int64(__fastcall *unk)(CPed *);
};


class CPed {
public:
	char pad_0x0000[0x20]; //0x0000
	CModelInfo* ModelInfo; //0x0020 
	char pad_0x0028[0x20]; //0x0028
	CPedDrawHandler* PedDrawHandler; //0x0048 
	char pad_0x0050[0x10]; //0x0050
	Matrix TransformationMatrix; //0x0060 
	char pad_0x00A0[0x1E0]; //0x00A0
	float Health; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float MaxHealth; //0x02A0 
	char pad_0x02A4[0xA84]; //0x02A4
	CVehicle* m_playerVehicle; //0x0D28 
	char pad_0x0D30[0x388]; //0x0D30
	CPlayerInfo* PlayerInfo; //0x10B8 
	char pad_0x10C0[0x8]; //0x10C0
	CWeaponManager* m_weaponManager; //0x10C8 
	char pad_0x10D0[0x13C0]; //0x10D0

}; //Size=0x2490

class CVehicle {
public:
	char pad_0x0000[0x30]; //0x0000
	CFragInst* m_fragInst; //0x0030 
	char pad_0x0038[0x10]; //0x0038
	CVehicleDrawHandler* m_vehicleDrawHandler; //0x0048 
	char pad_0x0050[0x230]; //0x0050
	float m_health; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float m_maxHealth; //0x02A0 
	char pad_0x02A4[0x77]; //0x02A4
	unsigned char m_rocketState; //0x031B 
	char pad_0x031C[0x1]; //0x031C
	unsigned char m_rocketEnergy; //0x031D 
	char pad_0x031E[0x5FA]; //0x031E
	CHandlingData* m_handlingData; //0x0918 
	char pad_0x0920[0x48]; //0x0920
	CVehicle* m_vehicle; //0x0968 
	char pad_0x0970[0x8]; //0x0970
	CVehicleDeformation* m_vehicleDeformation; //0x0978 
	char pad_0x0980[0x101C]; //0x0980
	float m_visualSuspension; //0x199C 
	char pad_0x19A0[0x240]; //0x19A0

}; //Size=0x1BE0

class CVehicleDrawHandler {
public:
	char pad_0x0000[0x370]; //0x0000
	//CVehicleSteamRenderGFX* m_vehicleStreamRenderGfx; //0x0370 
	CVehicleStreamRender* m_vehicleStreamRender; //0x0370
	char pad_0x0378[0x8B0]; //0x0378

}; //Size=0x0C28

class CVehicleSteamRenderGFX {
public:
	char pad_0x0000[0xB]; //0x0000
	unsigned char m_tireSize; //0x000B 
	char pad_0x000C[0x4]; //0x000C
	unsigned char m_customTires; //0x0010 
	char pad_0x0011[0xB8F]; //0x0011
	float m_tireWidth; //0x0BA0 
	char pad_0x0BA4[0x464]; //0x0BA4

}; //Size=0x1008

class CVehicleStreamRender {
public:
	char _0x0000[8];
	BYTE UNK1;
	BYTE UNK2;
	unsigned char TireSize; //0x000B 
	char pad_0x000C[0x4]; //0x000C
	unsigned char CustomTires; //0x0010 
	//char pad_0x0011[0xF]; //0x0011
	char pad_0x0011[0xB8F]; //0x0011
	float m_tireWidth; //0x0BA0 
	char pad_0x0BA4[0x464]; //0x0BA4

}; //Size=0x0020

class CWeaponInfo {
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CVehicleDeformation {
public:
	char pad_0x0000[0x20]; //0x0000
	float Rot1; //0x0020 
	float Width; //0x0024 
	float SideTilt; //0x0028 
	char pad_0x002C[0x4]; //0x002C
	float Rot2; //0x0030 
	float Length; //0x0034 
	float FrontUp; //0x0038 
	char pad_0x003C[0x4]; //0x003C
	float Sideways; //0x0040 
	float Forward; //0x0044 
	float Height; //0x0048 
	char pad_0x004C[0x4]; //0x004C
	Vector3_t Position; //0x0050 

}; //Size=0x005C

//class CVehicle
//{
//public:
//	char pad_0x0000[0x30]; //0x0000
//	__int64* pCNavigation; //0x0030 
//	char pad_0x0038[0x10]; //0x0038
//	//CVehicleMods* pCVehicleMods; //0x0048 
//	char pad_0x0050[0x40]; //0x0050
//	Vector3 v3VisualPos; //0x0090 
//	char pad_0x009C[0x3C]; //0x009C
//	BYTE btState; //0x00D8 
//	char pad_0x00D9[0xB0]; //0x00D9
//	BYTE btGodMode; //0x0189 
//	char pad_0x018A[0xF6]; //0x018A
//	float fHealth; //0x0280 
//	char pad_0x0284[0x1C]; //0x0284
//	float fHealthMax; //0x02A0 
//	char pad_0x02A4[0x4]; //0x02A4
//	__int64* pCAttacker; //0x02A8 
//	char pad_0x02B0[0x6A]; //0x02B0
//	BYTE btVolticRocketState; //0x031A 
//	char pad_0x031B[0x1]; //0x031B
//	float fVolticRocketEnergy; //0x031C 
//	char pad_0x0320[0x430]; //0x0320
//	Vector3 v3Velocity; //0x0750 
//	char pad_0x075C[0xF0]; //0x075C
//	float fHealth2; //0x084C 
//	char pad_0x0850[0x28]; //0x0850
//	char pad_0x0880[0x3]; //0x0880
//	BYTE btBulletproofTires; //0x0883 
//	char pad_0x0884[0x4]; //0x0884
//	BYTE btStolen; //0x0888 
//	char pad_0x0889[0x11]; //0x0889
//	BYTE N00000954; //0x089A 
//	char pad_0x089B[0x41]; //0x089B
//	float N0000081E; //0x08DC 
//	char pad_0x08E0[0x58]; //0x08E0
//	float fDirtLevel; //0x0938			max = 15.f
//	char pad_0x093C[0xA8]; //0x093C
//	DWORD dwCarAlarmLength; //0x09E4 
//	char pad_0x09E8[0x148]; //0x09E8
//	BYTE btOpenableDoors; //0x0B30 
//	char pad_0x0B31[0x4B]; //0x0B31
//	float fGravity; //0x0B7C
//	BYTE btMaxPassengers; //0x0B80 
//	char pad_0x0B81[0x1]; //0x0B81
//	BYTE btNumOfPassengers; //0x0B82 
//	char pad_0x0B83[0x3D]; //0x0B83
//}; //Size=0x0BC0


class CHandlingData {
public:
	char pad_0x0000[0x8]; //0x0000
	__int32 Hash; //0x0008 
	float fMass; //0x000C 
	char pad_0x0010[0x4]; //0x0010
	float fDownforceModifier; //0x0014 
	char pad_0x0018[0x8]; //0x0018
	Vector3_t vecCentreOfMassOffset; //0x0020 
	char pad_0x002C[0x4]; //0x002C
	Vector3_t vecInertiaMultiplier; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	float fPercentSubmerged; //0x0040 
	char pad_0x0044[0x8]; //0x0044
	float fDriveBiasFront; //0x004C 
	unsigned char nInitialDriveGears; //0x0050 
	char pad_0x0051[0x3]; //0x0051
	float fDriveInertia; //0x0054 
	float fClutchChangeRateScaleUpShift; //0x0058 
	float fClutchChangeRateScaleDownShift; //0x005C 
	float fInitialDriveForce; //0x0060 
	char pad_0x0064[0x8]; //0x0064
	float fBrakeForce; //0x006C 
	char pad_0x0070[0x4]; //0x0070
	float fInitialDriveMaxFlatVel; //0x0074 
	char pad_0x0078[0x4]; //0x0078
	float fHandBrakeForce; //0x007C 
	float fSteeringLock; //0x0080 
	char pad_0x0084[0x4]; //0x0084
	float fTractionCurveMax; //0x0088 
	char pad_0x008C[0x14]; //0x008C
	float fTractionSpringDeltaMax; //0x00A0 
	char pad_0x00A4[0x4]; //0x00A4
	float fLowSpeedTractionLossMult; //0x00A8 
	float fCamberStiffnesss; //0x00AC 
	char pad_0x00B0[0x8]; //0x00B0
	float fTractionLossMult; //0x00B8 
	float fSuspensionForce; //0x00BC 
	float fSuspensionCompDamp; //0x00C0 
	float fSuspensionReboundDamp; //0x00C4 
	float fSuspensionUpperLimit; //0x00C8 
	float fSuspensionLowerLimit; //0x00CC 
	char pad_0x00D0[0xC]; //0x00D0
	float fAntiRollBarForce; //0x00DC 
	char pad_0x00E0[0x8]; //0x00E0
	float fRollCentreHeightFront; //0x00E8 
	float fRollCentreHeightRear; //0x00EC 
	float fCollisionDamageMult; //0x00F0 
	float fWeaponDamageMult; //0x00F4 
	float fDeformationDamageMult; //0x00F8 
	float fEngineDamageMult; //0x00FC 
	float fPetrolTankVolume; //0x0100 
	float fOilVolume; //0x0104 
	char pad_0x0108[0x4]; //0x0108
	Vector3_t fSeatOffset; //0x010C 
	__int32 nMonetaryValue; //0x0118 
	char pad_0x011C[0x30]; //0x011C
	unsigned char N00002337; //0x014C 
	unsigned char N0000239F; //0x014D 
	char pad_0x014E[0x2]; //0x014E
	CAIHandlingInfo* AIHandlingInfo; //0x0150 
	CSubHandlingData* SubHandlingData; //0x0158 

}; //Size=0x0160

class CPlayerInfo {
public:
	char pad_0x0000[0x34]; //0x0000
	__int32 InternalIP; //0x0034 
	__int16 InternalPort; //0x0038 
	char pad_0x003A[0x2]; //0x003A
	__int32 RelayIP; //0x003C 
	__int16 RelayPort; //0x0040 
	char pad_0x0042[0x2]; //0x0042
	__int32 ExternalIP; //0x0044 
	__int16 ExternalPort; //0x0048 
	char pad_0x004A[0x1E]; //0x004A
	__int64 RockstarID; //0x0068 
	char pad_0x0070[0xC]; //0x0070
	char Name[20]; //0x7C 
	char pad_0x0090[0xB8]; //0x0090
	float SwimSpeed; //0x0148 
	float RunSpeed; //0x014C 
	char pad_0x0150[0x51]; //0x0150
	unsigned char IsRockstarDev; //0x01A1 
	char pad_0x01A2[0x26]; //0x01A2
	CPed* PlayerPed; //0x01C8 
	char pad_0x01D0[0x28]; //0x01D0
	__int32 FrameFlags; //0x01F8 
	char pad_0x01FC[0x618]; //0x01FC
	unsigned char WantedLevel1; //0x0814 
	char pad_0x0815[0x3]; //0x0815
	unsigned char WantedLevel2; //0x0818 
	char pad_0x0819[0x46F]; //0x0819
	float MeleeDamage; //0x0C88 
	char pad_0x0C8C[0x2F0]; //0x0C8C

}; //Size=0x0F7C

class CHostStruct {
public:
	char pad_0000[392]; //0x0000
	uint32_t SessionHost; //0x0188
}; //Size: 0x018C

class CWeaponManager {
public:
	char pad_0x0000[0x20]; //0x0000
	CWeapon* WeaponInfo; //0x0020 
	char pad_0x0028[0x178]; //0x0028
	Vector3_t LastAimedPosition; //0x01A0 
	char pad_0x01AC[0x4]; //0x01AC
	Vector3_t ImpactPosition; //0x01B0 
	char pad_0x01BC[0x2E4]; //0x01BC

}; //Size=0x04A0

class CWeapon {
public:
	char pad_0x0000[0x10]; //0x0000
	__int32 NameHash; //0x0010 
	__int32 ModelHash; //0x0014 
	char pad_0x0018[0x40]; //0x0018
	unsigned char WeaponWheelSlot; //0x0058 
	unsigned char N00002FF2; //0x0059 
	char pad_0x005A[0x6]; //0x005A
	CAmmoInfo* AmmoInfo; //0x0060 
	CAimingInfo* AimingInfo; //0x0068 
	unsigned char ClipSize; //0x0070 
	char pad_0x0071[0x3]; //0x0071
	float AccuracySpread; //0x0074 
	float AccurateModeAccuracyModifier; //0x0078 
	float RunAndGunAccuracyModifier; //0x007C 
	float RunAndGunAccuracyMinOverride; //0x0080 
	float RecoilAccuracyMax; //0x0084 
	float RecoilErrorTime; //0x0088 
	float RecoilRecoveryRate; //0x008C 
	float RecoilAccuracyToAllowHeadShotAI; //0x0090 
	float MinHeadShotDistanceAI; //0x0094 
	float MaxHeadShotDistanceAI; //0x0098 
	float HeadShotDamageModifierAI; //0x009C 
	float RecoilAccuracyToAllowHeadShotPlayer; //0x00A0 
	float MinHeadShotDistancePlayer; //0x00A4 
	float MaxHeadShotDistancePlayer; //0x00A8 
	float HeadShotDamageModifierPlayer; //0x00AC 
	float Damage; //0x00B0 
	float DamageTime; //0x00B4 
	float DamageTimeInVehicle; //0x00B8 
	float DamageTimeInVehicleHeadShot; //0x00BC 
	float HitLimbsDamageModifier; //0x00C0 
	float NetworkHitLimbsDamageModifier; //0x00C4 
	float LightlyArmouredDamageModifier; //0x00C8 
	float VehicleDamageModifier; //0x00CC 
	float Force; //0x00D0 
	float ForceHitPed; //0x00D4 
	float ForceHitVehicle; //0x00D8 
	float ForceHitFlyingHeli; //0x00DC 
	char pad_0x00E0[0x10]; //0x00E0
	float ForceMaxStrengthMult; //0x00F0 
	float ForceFalloffRangeStart; //0x00F4 
	float ForceFalloffRangeEnd; //0x00F8 
	float ForceFalloffMin; //0x00FC 
	float ProjectileForce; //0x0100 
	float FragImpulse; //0x0104 
	float Penetration; //0x0108 
	float VerticalLaunchAdjustment; //0x010C 
	float DropForwardVelocity; //0x0110 
	float Speed; //0x0114 
	unsigned char BulletsInBatch; //0x0118 
	char pad_0x0119[0x3]; //0x0119
	float BatchSpread; //0x011C 
	float ReloadTimeMP; //0x0120 
	float ReloadTimeSP; //0x0124 
	float VehicleReloadTime; //0x0128 
	float AnimReloadRate; //0x012C 
	unsigned char BulletsPerAnimLoop; //0x0130 
	char pad_0x0131[0x3]; //0x0131
	float TimeBetweenShots; //0x0134 
	float TimeLeftBetweenShotsWhereShouldFireIsCached; //0x0138 
	float SpinUpTime; //0x013C 
	float SpinTime; //0x0140 
	float SpinDownTime; //0x0144 
	float AlternateWaitTime; //0x0148 
	float BulletBendingNearRadius; //0x014C 
	float BulletBendingFarRadius; //0x0150 
	float BulletBendingZoomedRadius; //0x0154 
	float FirstPersonBulletBendingNearRadius; //0x0158 
	float FirstPersonBulletBendingFarRadius; //0x015C 
	float FirstPersonBulletBendingZoomedRadius; //0x0160 
	char pad_0x0164[0xDC]; //0x0164
	__int32 InitialRumbleDuration; //0x0240 
	float InitialRumbleIntensity; //0x0244 
	float InitialRumbleIntensityTrigger; //0x0248 
	__int32 RumbleDuration; //0x024C 
	float RumbleIntensity; //0x0250 
	float RumbleIntensityTrigger; //0x0254 
	float RumbleDamageIntensity; //0x0258 
	__int32 InitialRumbleDurationFps; //0x025C 
	float InitialRumbleIntensityFps; //0x0260 
	__int32 RumbleDurationFps; //0x0264 
	float RumbleIntensityFps; //0x0268 
	float NetworkPlayerDamageModifier; //0x026C 
	float NetworkPedDamageModifier; //0x0270 
	float NetworkHeadShotPlayerDamageModifier; //0x0274 
	float LockOnRange; //0x0278 
	float WeaponRange; //0x027C 
	char pad_0x0280[0x8]; //0x0280
	float DamageFallOffRangeMin; //0x0288 
	float DamageFallOffRangeMax; //0x028C 
	char pad_0x0290[0x4]; //0x0290
	float DamageFallOffModifier; //0x0294 
	char pad_0x0298[0x50]; //0x0298
	float FirstPersonFOV; //0x02E8 
	char pad_0x02EC[0x678]; //0x02EC

}; //Size=0x0964

class CAmmoInfo {
public:
	char pad_0x0000[0x20]; //0x0000
	unsigned char AmmoMax; //0x0020 
	char pad_0x0021[0x3]; //0x0021
	unsigned char AmmoMax50; //0x0024 
	char pad_0x0025[0x3]; //0x0025
	unsigned char AmmoMax100; //0x0028 
	char pad_0x0029[0x3]; //0x0029
	unsigned char AmmoMaxMP; //0x002C 
	char pad_0x002D[0x3]; //0x002D
	unsigned char AmmoMax50MP; //0x0030 
	char pad_0x0031[0x3]; //0x0031
	unsigned char AmmoMax100MP; //0x0034 
	char pad_0x0035[0xB]; //0x0035
	float Damage; //0x0040 
	float LifeTime; //0x0044 
	float FromVehicleLifeTime; //0x0048 
	float LifeTimeAfterImpact; //0x004C 
	float LifeTimeAfterExplosion; //0x0050 
	float ExplosionTime; //0x0054 
	float LaunchSpeed; //0x0058 
	float SeparationTime; //0x005C 
	float TimeToReachTarget; //0x0060 
	float Damping; //0x0064 
	float GravityFactor; //0x0068 
	float RicochetTolerance; //0x006C 
	float PedRicochetTolerance; //0x0070 
	float VehicleRicochetTolerance; //0x0074 
	float FrictionMultiplier; //0x0078 
	char pad_0x007C[0x64]; //0x007C
	Vector3_t LightColour; //0x00E0 
	char pad_0x00EC[0x4]; //0x00EC
	float LightIntensity; //0x00F0 
	float LightRange; //0x00F4 
	float LightFalloffExp; //0x00F8 
	float LightFrequency; //0x00FC 
	float LightPower; //0x0100 
	float CoronaSize; //0x0104 
	float CoronaIntensity; //0x0108 
	float CoronaZBias; //0x010C 
	char pad_0x0110[0x40]; //0x0110
	unsigned char AmmoMaxMPBonus; //0x0150 
	char pad_0x0151[0x7]; //0x0151

}; //Size=0x0158

class CReplayInterface {
public:
	char pad_0x0000[0x8]; //0x0000
	CCameraInterface* CameraInterface; //0x0008 
	CVehicleInterface* VehicleInterface; //0x0010 
	CPedInterface* PedInterface; //0x0018 
	CPickupInterface* PickupInterface; //0x0020 
	CObjectInterface* ObjectInterface; //0x0028 
	char pad_0x0030[0x10]; //0x0030

}; //Size=0x0040

class CCameraInterface {
public:
	char pad_0x0000[0x408]; //0x0000

}; //Size=0x0408

class CVehicleInterface {
public:
	char pad_0x0000[0x180]; //0x0000
	CVehList* VehList; //0x0180 
	__int32 MaxVehicles; //0x0188 
	char pad_0x018C[0x4]; //0x018C
	__int32 CurVehicles; //0x0190 
	char pad_0x0194[0x274]; //0x0194

}; //Size=0x0408

class CPedInterface {
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CPickupInterface {
public:
	char pad_0x0000[0x100]; //0x0000
	CPickupList* PickupList; //0x0100 
	__int32 MaxPickups; //0x0108 
	char pad_0x010C[0x4]; //0x010C
	__int32 CurPickups; //0x0110 
	char pad_0x0114[0x2F4]; //0x0114

}; //Size=0x0408

class CObjectInterface {
public:
	char pad_0x0000[0x158]; //0x0000
	CObjectList* ObjectList; //0x0158 
	__int32 MaxObjects; //0x0160 
	char pad_0x0164[0x4]; //0x0164
	__int32 CurObjects; //0x0168 
	char pad_0x016C[0x2DC]; //0x016C

}; //Size=0x0448

class CPickupList {
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CVehList {
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CObjectList {
public:
	char pad_0x0000[0x48]; //0x0000

}; //Size=0x0048

class CObjectHandle {
public:
	char pad_0x0000[0x8]; //0x0000
	__int32 Handle; //0x0008 
	char pad_0x000C[0x3C]; //0x000C

}; //Size=0x0048

class CAimingInfo {
public:
	__int32 Hash; //0x0000 
	float HeadingLimit; //0x0004 
	float SweepPitchMin; //0x0008 
	float SweepPitchMax; //0x000C 

}; //Size=0x0010

class CNetGamePlayer {
public:
	char pad_0x0000[0x2D]; //0x0000
	uint8_t m_playerID; //0x002D 
	char pad_0x002E[0x7A]; //0x002E
	CPlayerInfo* PlayerInfo; //0x00A8 
	char pad_0x00B0[0x20]; //0x00B0

}; //Size=0x00D0

class CAIHandlingInfo {
public:
	char pad_0x0000[0x48]; //0x0000

}; //Size=0x0048

class CFlyingHandlingData {
public:
	char pad_0x0000[0x8]; //0x0000
	float fThrust; //0x0008 
	float fThrustFallOff; //0x000C 
	float fThrustVectoring; //0x0010 
	char pad_0x0014[0x8]; //0x0014
	float fYawMult; //0x001C 
	float fYawStabilise; //0x0020 
	float fSideSlipMult; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	float fRollMult; //0x002C 
	float fRollStabilise; //0x0030 
	float N000026D3; //0x0034 
	float fPitchMult; //0x0038 
	float fPitchStabilise; //0x003C 
	char pad_0x0040[0x4]; //0x0040
	float fFormLiftMult; //0x0044 
	float fAttackLiftMult; //0x0048 
	float fAttackDiveMult; //0x004C 
	float fGearDownDragV; //0x0050 
	float fGearDownLiftMult; //0x0054 
	float fWindMult; //0x0058 
	float fMoveRes; //0x005C 
	Vector3_t vecTurnRes; //0x0060 
	char pad_0x006C[0x4]; //0x006C
	Vector3_t vecSpeedRes; //0x0070 
	char pad_0x007C[0x4]; //0x007C
	float fGearDoorFrontOpen; //0x0080 
	float fGearDoorRearOpen; //0x0084 
	float fGearDoorRearOpen2; //0x0088 
	float fGearDoorRearMOpen; //0x008C 
	float fTurublenceMagnitudeMax; //0x0090 
	float fTurublenceForceMulti; //0x0094 
	float fTurublenceRollTorqueMulti; //0x0098 
	float fTurublencePitchTorqueMulti; //0x009C 
	float fBodyDamageControlEffectMult; //0x00A0 
	float fInputSensitivityForDifficulty; //0x00A4 
	float fOnGroundYawBoostSpeedPeak; //0x00A8 
	float fOnGroundYawBoostSpeedCap; //0x00AC 
	float fEngineOffGlideMulti; //0x00B0 

}; //Size=0x00B4

class CBoatHandlingData {
public:
	char pad_0x0000[0x8]; //0x0000
	float fBoxFrontMult; //0x0008 
	float fBoxRearMult; //0x000C 
	float fBoxSideMult; //0x0010 
	float fSampleTop; //0x0014 
	float fSampleBottom; //0x0018 
	float N000028C4; //0x001C 
	float fAquaplaneForce; //0x0020 
	float fAquaplanePushWaterMult; //0x0024 
	float fAquaplanePushWaterCap; //0x0028 
	float fAquaplanePushWaterApply; //0x002C 
	float fRudderForce; //0x0030 
	float fRudderOffsetSubmerge; //0x0034 
	float fRudderOffsetForce; //0x0038 
	float fRudderOffsetForceZMult; //0x003C 
	float fWaveAudioMult; //0x0040 
	float N000028CE; //0x0044 
	float N0000283E; //0x0048 
	float N000028D0; //0x004C 
	Vector3_t vecMoveResistance; //0x0050 
	float N000028D4; //0x005C 
	Vector3_t vecTurnResistance; //0x0060 
	float N000028D8; //0x006C 
	float fLook_L_R_CamHeight; //0x0070 
	float fDragCoefficient; //0x0074 
	float fKeelSphereSize; //0x0078 
	float fPropRadius; //0x007C 
	float fLowLodAngOffset; //0x0080 
	float fLowLodDraughtOffset; //0x0084 
	float fImpellerOffset; //0x0088 
	float fImpellerForceMult; //0x008C 
	float fDinghySphereBuoyConst; //0x0090 
	float fProwRaiseMult; //0x0094 

}; //Size=0x0098

class CBikeHandlingData {
public:
	char pad_0x0000[0x8]; //0x0000
	float fLeanFwdCOMMult; //0x0008 
	float fLeanFwdForceMult; //0x000C 
	float fLeanBakCOMMult; //0x0010 
	float fLeanBakForceMult; //0x0014 
	float fMaxBankAngle; //0x0018 
	char pad_0x001C[0x4]; //0x001C
	float fFullAnimAngle; //0x0020 
	float fDesLeanReturnFrac; //0x0024 
	float fStickLeanMult; //0x0028 
	float fBrakingStabilityMult; //0x002C 
	float fInAirSteerMult; //0x0030 
	float fWheelieBalancePoint; //0x0034 
	float fStoppieBalancePoint; //0x0038 
	float fWheelieSteerMult; //0x003C 
	float fRearBalanceMult; //0x0040 
	float fFrontBalanceMult; //0x0044 
	float fBikeGroundSideFrictionMult; //0x0048 
	float fBikeWheelGroundSideFrictionMult; //0x004C 
	float fBikeOnStandLeanAngle; //0x0050 c
	float fBikeOnStandSteerAngle; //0x0054 
	float fJumpForce; //0x0058 

}; //Size=0x005C

typedef union {
	CFlyingHandlingData FlyingHandlingData;
	CBikeHandlingData BikeHandlingData;
	CBoatHandlingData BoatHandlingData;
} CSubHandlingDataType;

class CSubHandlingData {
public:
	CSubHandlingDataType * SubHandlingData; //0x0000 
	CVehicleWeaponHandlingData* VehicleWeaponHandlingData; //0x0008 
	char pad_0x0010[0x8]; //0x0010

}; //Size=0x0018

class CModelInfo {
public:
	char pad_0x0000[0x808]; //0x0000

}; //Size=0x0808

class CPedDrawHandler {
public:
	char pad_0x0000[0x144]; //0x0000
	__int32 Face; //0x0144 
	__int32 FaceVariation; //0x0148 
	__int32 N00002CBF; //0x014C 
	char pad_0x0150[0x2B8]; //0x0150

}; //Size=0x0408

class CVehicleWeaponHandlingData {
public:
	char pad_0x0000[0x48]; //0x0000

}; //Size=0x0048


class CScriptedGameEvent {
public:
	char pad_0x0000[0x48]; //0x0000
	uint64_t EventID; //0x0048 
	char pad_0x0050[0x1AC]; //0x0050
	uint32_t ArgCount; //0x01FC 
	char pad_0x0200[0x24C]; //0x0200

	uint64_t* GetArgs() {
		return (uint64_t*)((uintptr_t)(this) + 0x224);
	}

}; //Size=0x044C

class CNetworkIncrementStatEvent {
public:
	char pad_0x0000[0x8]; //0x0000
	uint32_t Hash; //0x0008 
	int64_t Value; //0x000C 

}; //Size=0x0014

class CExplosionEvent {
public:
	char pad_0x0000[0x8]; //0x0000
	uint32_t ExplosionType; //0x0008 
	char pad_0x000C[0xC]; //0x000C
	Vector3 Position;
	char pad_0x0024[0x20]; //0x0024
	float DamageScale; //0x0044 
	char pad_0x0048[0xB8]; //0x0048
}; //Size=0x0100

class CRequestControlEvent {
public:
	char pad_0x0000[0x4]; //0x0000
	int32_t EntityID; //0x0008 

}; //Size=0x000C

typedef union {
	CScriptedGameEvent ScriptedGameEvent;
	CNetworkIncrementStatEvent NetworkIncrementStatEvent;
	CExplosionEvent ExplosionEvent;
	CRequestControlEvent RequestControlEvent;
} NetEventContext;

class CNetEventInfo {
public:
	CNetEventVTable * VTable; //0x0000 
	int16_t ID; //0x0008 
	char pad_0x000A[0xE]; //0x000A
	CNetGamePlayer* Receiver; //0x0018 
	char pad_0x0020[0x8]; //0x0020
	NetEventContext* m_context; //0x0028 

}; //Size=0x0278

class CNetEventVTable {
public:
	char pad_0x0000[0x8]; //0x0000
	char*(*GetName)(); //0x0008 
	char pad_0x0010[0x8]; //0x0010
	void(*m_0x18)(int64_t a1, int64_t a2); //0x0018 
	char pad_0x0020[0x10]; //0x0020
	void(*Setup)(CNetEventInfo* event_info, int64_t a2, CNetGamePlayer* sender, int64_t a4); //0x0030 
	uint8_t(*Execute)(CNetEventInfo* event_info, CNetGamePlayer* sender, int64_t a3); //0x0038 
	char pad_0x0040[0x18]; //0x0040
	void(*m_0x58)(CNetEventInfo* event_info, int64_t a2, int64_t a3, CNetGamePlayer* sender); //0x0058 
	char pad_0x0060[0x78]; //0x0060

}; //Size=0x00D8

   /*Model info*/
class fwArchetypeDef {
public:
	virtual ~fwArchetypeDef();

	virtual int64_t GetTypeIdentifier();

	float lodDist;
	uint32_t flags; // 0x10000 = alphaclip
	uint32_t specialAttribute; // lower 5 bits == 31 -> use alpha clip, get masked to 31 in InitializeFromArchetypeDef
	uint32_t pad;
	void* pad2;
	float bbMin[4];
	float bbMax[4];
	float bsCentre[4];
	float bsRadius;
	float hdTextureDist;
	uint32_t name;
	uint32_t textureDictionary;
	uint32_t clipDictionary;
	uint32_t drawableDictionary;
	uint32_t physicsDictionary;
	uint32_t assetType;
	uint32_t assetName;
	uint32_t pad5[7];

public:
	fwArchetypeDef() {
		flags = 0x10000; // was 0x2000
		lodDist = 299.0f;
		hdTextureDist = 375.0f;

		drawableDictionary = 0;
		assetType = 3;
		assetName = 0x12345678;

		specialAttribute = 31;

		pad = 0;
		pad2 = 0;
		clipDictionary = 0;
		physicsDictionary = 0;
		memset(pad5, 0, sizeof(physicsDictionary));
	}
};
class fwArchetype {
public:
	virtual ~fwArchetype() = default;

	char _0x0008[0x10]; // 0x0000
	Hash m_hash; // 0x0018
	char _0x001C[0x10]; // 0x001C
	float m_radius; // 0x002C
	float m_aabbMin[4]; // 0x0030
	float m_aabbMax[4]; // 0x0040
	uint32_t m_flags; // 0x0050
	char _0x0054[0x12]; // 0x0054
	uint16_t m_index; // 0x0066
};
class fwEntity {
public:
	virtual ~fwEntity() = 0;

	virtual bool IsOfType(uint32_t hash) = 0;
};
class CBaseModelInfo : public fwArchetype {
public:
	virtual ~CBaseModelInfo() {}
	virtual void Initialize() {}
	virtual void InitializeFromArchetypeDef(uint32_t, fwArchetypeDef*, bool) {}
	virtual fwEntity* CreateEntity() { return nullptr; }
	// and lots of other functions...

public:
	uint8_t GetModelType() const {
		return m_modelType & 0x1F;
	}
protected:
	char _0x0068[0x35];	// 0x0068
	uint8_t m_modelType;	// 0x009D (& 0x1F)
	char _0x009E[0x2];	// 0x009E
	uint32_t m_unkFlag;	// 0x00A0
	char _0x00A4[0x4];	// 0x00A4
	void* m_0x00A8;		// 0x00A8
};
class CVehicleModelInfo : public CBaseModelInfo {
public:
	virtual ~CVehicleModelInfo() {}
	virtual void Initialize() {}
	virtual void InitializeFromArchetypeDef(uint32_t, fwArchetypeDef*, bool) {}
	virtual fwEntity* CreateEntity() { return nullptr; }
	// and lots of other functions...

public:
	void* m_0x00B0; // 0x00B0
	char _0x00B8[0x40]; // 0x00B8
	uint8_t m_primaryColorCombinations[25]; // 0x00F8
	uint8_t m_secondaryColorCombinations[25]; // 0x0111
	uint8_t m_unkColor1Combinations[25]; // 0x012A
	uint8_t m_unkColor2Combinations[25]; // 0x0143
	uint8_t m_interiorColorCombinations[25]; // 0x015C
	uint8_t m_dashboardColorCombinations[25]; // 0x0175
	char _0x018E[0xE2]; // 0x018E
	char m_displayName[12]; // 0x0270 (aka gameName)
	char m_manufacturerName[12]; // 0x027C (aka makeName)
	uint8_t* m_modKits; // 0x0288
	uint16_t m_modKitsCount; // 0x0290
	char _0x0292[0x46]; // 0x0292
	void* m_driverInfo; // 0x02D8
	uint8_t m_numDrivers; // 0x02E0
	char _0x02E1[0x37]; // 0x02E1
	uint32_t m_vehicleType; // 0x0318
	uint32_t m_unkVehicleType; // 0x031C
	uint32_t m_diffuseTint; // 0x0320
	char _0x0324[0x90]; // 0x0324
	uint8_t m_unkModKitVal; // 0x03B4
	char _0x03B5[0xA7]; // 0x03B5
	float m_wheelScale; // 0x045C
	float m_wheelScaleRear; // 0x0460
	float m_defaultBodyHealth; // 0x0464
	char _0x0468[0x20]; // 0x0468
	uint32_t m_handlingIndex; // 0x0488
	uint32_t m_identicalModelSpawnDistance; // 0x048C
	char _0x0490[0x4]; // 0x0490
	uint32_t m_numColorCombinations; // 0x0494
	char _0x0498[0x30]; // 0x0498
	void* m_0x04C8; // 0x04C8 (wheel data? 0xAC -> burnout mult?)
	char _0x04D0[0x3B]; // 0x04D0
	uint8_t m_sirenInfoId; // 0x050B
	char _0x050C[0xC]; // 0x050C
	uint8_t m_vehicleClass; // 0x0518 (& 0x1F; (>> 5) & 3 -> plate type)
	char _0x0519[0x2F]; // 0x0519
	int m_seatCount; // 0x0548
	uint32_t m_flags1; // 0x054C
	uint32_t m_flags2; // 0x0550
	uint32_t m_flags3; // 0x0554
	uint32_t m_flags4; // 0x0558
	uint32_t m_flags5; // 0x055C
};
class CVehicleModelInfo1290 : public CBaseModelInfo {
public:
	virtual ~CVehicleModelInfo1290() {}
	virtual void Initialize() {}
	virtual void InitializeFromArchetypeDef(uint32_t, fwArchetypeDef*, bool) {}
	virtual fwEntity* CreateEntity() { return nullptr; }
	// and lots of other functions...

public:
	void* m_0x00B0; // 0x00B0
	char _0x00B8[0x40]; // 0x00B8
	uint8_t m_primaryColorCombinations[25]; // 0x00F8
	uint8_t m_secondaryColorCombinations[25]; // 0x0111
	uint8_t m_unkColor1Combinations[25]; // 0x012A
	uint8_t m_unkColor2Combinations[25]; // 0x0143
	uint8_t m_interiorColorCombinations[25]; // 0x015C
	uint8_t m_dashboardColorCombinations[25]; // 0x0175
	char _0x018E[0x10A]; // 0x018E
	char m_displayName[12]; // 0x0298 (aka gameName)
	char m_manufacturerName[12]; // 0x02A4 (aka makeName)
	uint16_t* m_modKits; // 0x02B0
	uint16_t m_modKitsCount; // 0x02B8
	char _0x02BA[0x46]; // 0x02BA
	void* m_driverInfo; // 0x0300
	uint8_t m_numDrivers; // 0x0308
	char _0x0309[0x37]; // 0x02E3
	uint32_t m_vehicleType; // 0x0340
	uint32_t m_unkVehicleType; // 0x0344
	uint32_t m_diffuseTint; // 0x0348
	char _0x034C[0x90]; // 0x034C
	uint8_t m_unkModKitVal; // 0x03DC (also uint16_t now?)
	char _0x03DD[0xA7]; // 0x03DD
	float m_wheelScale; // 0x0484
	float m_wheelScaleRear; // 0x0488
	float m_defaultBodyHealth; // 0x048C
	char _0x0490[0x20]; // 0x0490
	uint32_t m_handlingIndex; // 0x04B8
	uint32_t m_identicalModelSpawnDistance; // 0x04BC
	char _0x04C0[0x4]; // 0x04C0
	uint32_t m_numColorCombinations; // 0x04C4
	uint32_t m_fragmentIndex; // 0x04C8
	char _0x04CC[0x2C]; // 0x04CC
	void* m_0x04F8; // 0x04F8 (wheel data? 0xAC -> burnout mult?)
	char _0x0500[0x3B]; // 0x0500
	uint8_t m_sirenInfoId; // 0x053B
	char _0x053C[0x7]; // 0x053C
	uint8_t m_0x0543; // 0x0543
	char _0x0544_[0x4]; // 0x0544
	uint8_t m_vehicleClass; // 0x0548 (& 0x1F; (>> 5) & 3 -> plate type)
	char _0x0549[0x2F]; // 0x0549
	int m_seatCount; // 0x0578 (use only if unk_0x00B0->seatCount can't be used)
	uint32_t m_flags1; // 0x057C
	uint32_t m_flags2; // 0x0580
	uint32_t m_flags3; // 0x0584
	uint32_t m_flags4; // 0x0588
	uint32_t m_flags5; // 0x058C
	uint32_t m_flags6; // 0x0590
	char _0x0594[0xC]; // 0x0594
};

class CNetworkBandwithManager {
public:
	char m_pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class CNetworkPlayerManager {
public:
	char m_pad_0x0000[0x10]; //0x0000
	CNetworkBandwithManager* m_bandwidthManager; //0x0010 
	char m_pad_0x0018[0xD0]; //0x0018
	CNetGamePlayer* m_localPlayer; //0x00E8 
	char m_pad_0x00F0[0x88]; //0x00F0
	uint8_t m_playersOnline; //0x0178 
	char m_pad_0x0179[0x7]; //0x0179
	CNetGamePlayer* m_players[0x20]; //0x0180 

}; //Size=0x0280

struct WorldManager {
	char field_0[3752];
	float WindSpeed;
	char field_2[16];
	float Fog;
	float RoadSlipperiness;
};


class CFragInst {
public:
	char pad_0x0000[0x10]; //0x0000
	CArcheTypeDamp* ArcheTypeDamp; //0x0010 
	char pad_0x0018[0x60]; //0x0018
	CFragType* FragType; //0x0078 
	char pad_0x0080[0x388]; //0x0080

}; //Size=0x0408

class CArcheTypeDamp {
public:
	char pad_0x0000[0x20]; //0x0000
	phBoundComposite* Bounds; //0x0020 
	char pad_0x0028[0x130]; //0x0028
	CEntitySkeleton* EntitySkeleton; //0x0158 
	char pad_0x0160[0x2A8]; //0x0160

}; //Size=0x0408

class CFragType {
public:
	char pad_0x0000[0xF0]; //0x0000
	CFragPhysicsLODGroup* FragPhysicsLODGroup; //0x00F0 
	char pad_0x00F8[0x390]; //0x00F8

}; //Size=0x0488

class CFragPhysicsLODGroup {
public:
	char pad_0x0000[0x10]; //0x0000
	CFragPhysicsLOD* FragPhysicsLOD1; //0x0010 
	char pad_0x0018[0x3F0]; //0x0018

}; //Size=0x0408

class CFragPhysicsLOD {
public:
	char pad_0x0000[0xC0]; //0x0000
	CGroupNames* GroupNames; //0x00C0 
	Groups* Groups; //0x00C8 
	char pad_0x00D0[0x3F8]; //0x00D0

}; //Size=0x04C8

class CGroupNames {
public:
	char pad_0x0000[0x8]; //0x0000

}; //Size=0x0008

class Groups {
public:
	char pad_0x0000[0x48]; //0x0000

}; //Size=0x0048

enum BoundType : byte {
	BTSphere = 0,
	BTCapsule = 1,
	BTBox = 3,
	BTGeometry = 4,
	BTBoundingVolumeHierarchy = 8,
	BTComposite = 10,
	BTDisc = 12,
	BTCylinder = 13,
};

class phBoundComposite {
public:
	char pad_0x0000[0x10]; //0x0000
	BoundType Type; //0x0010 
	char pad_0x0011[0x3]; //0x0011
	float BoundingSphereRadius; //0x0014 
	char pad_0x0018[0x8]; //0x0018
	Vector3_t BoundingBoxMax; //0x0020 
	char pad_0x002C[0x4]; //0x002C
	Vector3_t BoundingBoxMin; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	Vector3_t BoundingBoxCenter; //0x0040 
	char pad_0x004C[0x4]; //0x004C
	Vector3_t Center; //0x0050 
	char pad_0x005C[0x3AC]; //0x005C

}; //Size=0x0408


class CEntitySkeleton {
public:
	crSkeletonData * SkeletonData; //0x0000 
	NativeMatrix* EntityMatrix; //0x0008 
	NativeMatrix* desiredBonesMatricesArray; //0x0010 
	NativeMatrix* currentBonesMatricesArray; //0x0018 
	__int32 BonesCount; //0x0020 
	char pad_0x0024[0x3E4]; //0x0024

}; //Size=0x0408

class N000014A7 {
public:
	char pad_0x0000[0x60]; //0x0000
	float N000014C0; //0x0060 
	char pad_0x0064[0x3E4]; //0x0064

}; //Size=0x0448

class crSkeletonData {
public:
	char pad_0x0000[0x20]; //0x0000
	crSkeletonBoneDataArray* Bones; //0x0020 
	NativeMatrix* array_BonesTransformationsInverted; //0x0028 
	NativeMatrix* array_BonesTransformations; //0x0030 
	char pad_0x0038[0x40C]; //0x0038

}; //Size=0x0444

class NativeMatrix {
public:
	Matrix Matrix; //0x0000 
}; //Size=0x0040

class crSkeletonBoneData {
public:
	Vector4 Rotation; //0x0000 
	Vector3_t Position; //0x0010 
	char pad_0x001C[0x16]; //0x001C
	__int16 ParentIndex; //0x0032 
	char pad_0x0034[0x4]; //0x0034
	char* N0000160F; //0x0038 
	char pad_0x0040[0x2]; //0x0040
	__int16 index; //0x0042 
	char pad_0x0044[0xC]; //0x0044

}; //Size=0x0050

class crSkeletonBoneDataArray {
public:
	crSkeletonBoneData * array_boneDatas; //0x0000 

}; //Size=0x0050

template <class T>
class RageNode {
public:
	char pad_0000[8];
	T *Data;
	class RageNode *Next;
	class RageNode *Last;
};

enum TransactionService {
	SERVICE_EARN_AMBIENT_JOB_BEAST = 0xCF63BF45,
	SERVICE_EARN_AMBIENT_JOB_BLAST = 0xC84D30CC,
	SERVICE_EARN_AMBIENT_JOB_CHALLENGES = 0xA87819A3,
	SERVICE_EARN_AMBIENT_JOB_CHECKPOINT_COLLECTION = 0xFC71898E,
	SERVICE_EARN_AMBIENT_JOB_DEAD_DROP = 0x5AEF7C87,
	SERVICE_EARN_AMBIENT_JOB_DESTROY_VEH = 0x8D682613,
	SERVICE_EARN_AMBIENT_JOB_DISTRACT_COPS = 0x862FB02E,
	SERVICE_EARN_AMBIENT_JOB_HELI_HOT_TARGET = 0x06A679FE,
	SERVICE_EARN_AMBIENT_JOB_HOT_PROPERTY = 0xB8D124BE,
	SERVICE_EARN_AMBIENT_JOB_HOT_TARGET_DELIVER = 0x60988977,
	SERVICE_EARN_AMBIENT_JOB_HOT_TARGET_KILL = 0x74EC47CE,
	SERVICE_EARN_AMBIENT_JOB_KING = 0xF353DF93,
	SERVICE_EARN_AMBIENT_JOB_PASS_PARCEL = 0x5E0B0A1C,
	SERVICE_EARN_AMBIENT_JOB_PENNED_IN = 0x39B3A1A7,
	SERVICE_EARN_AMBIENT_JOB_PLANE_TAKEDOWN = 0x6A22D039,
	SERVICE_EARN_AMBIENT_JOB_TIME_TRIAL = 0x67878154,
	SERVICE_EARN_AMBIENT_JOB_URBAN_WARFARE = 0x0C92ECEF,
	SERVICE_EARN_AMBIENT_MUGGING = 0xEC745CB2,
	SERVICE_EARN_AMBIENT_PICKUP = 0x20D60B56,
	SERVICE_EARN_ARMORED_TRUCKS = 0xB94DDB9B,
	SERVICE_EARN_BANK_INTEREST = 0xF97DB87A,
	SERVICE_EARN_BEND_JOB = 0x176D9D54,
	SERVICE_EARN_BETTING = 0xACA75AAE, //only 600,000 per second and a max of 1 billion before requires a short cooldown
	SERVICE_EARN_BONUS = 0x5C7EA5E8,
	SERVICE_EARN_BOSS = 0x3E7AA93E,
	SERVICE_EARN_BOSS_AGENCY = 0xCCFA5F2D,
	SERVICE_EARN_BOUNTY_COLLECTED = 0xC4F96E65,
	SERVICE_EARN_CASHING_OUT = 0x50503398,
	SERVICE_EARN_CHALLENGE_WIN = 0xFC8D0020,
	SERVICE_EARN_CNCB = 0x4D8C639E,
	SERVICE_EARN_CNCW = 0xD89979EE,
	SERVICE_EARN_CRATE_DROP = 0x2195C3D1,
	SERVICE_EARN_DAILY_OBJECTIVES = 0xBFCBE6B6,
	SERVICE_EARN_DEATHMATCH_BOUNTY = 0x31D3FC9B,
	SERVICE_EARN_DEBUG = 0x762D6BF6,
	SERVICE_EARN_DOOMSDAY_FINALE_BONUS = 0xBA16F44B,
	SERVICE_EARN_FROM_DESTROYING_CONTRABAND = 0x328CD5AA,
	SERVICE_EARN_FROM_VEHICLE_EXPORT = 0xEE884170,
	SERVICE_EARN_GANGATTACK_PICKUP = 0x506A6AF5,
	SERVICE_EARN_GANGOPS_AWARD_FIRST_TIME_XM_BASE = 0xC5ED889C,
	SERVICE_EARN_GANGOPS_AWARD_FIRST_TIME_XM_SILO = 0xB99C11F6,
	SERVICE_EARN_GANGOPS_AWARD_FIRST_TIME_XM_SUBMARINE = 0xFFC0D962,
	SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_2 = 0xFF3F6FB2,
	SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_3 = 0xED74CC1D,
	SERVICE_EARN_GANGOPS_AWARD_LOYALTY_AWARD_4 = 0x33E1D8F6,
	SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_2 = 0x370A42A5,
	SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_3 = 0xED97AFC1,
	SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_4 = 0x23F59C7C,
	SERVICE_EARN_GANGOPS_AWARD_ORDER = 0x32537662,
	SERVICE_EARN_GANGOPS_AWARD_SUPPORTING = 0x8DACDD38,
	SERVICE_EARN_GANGOPS_ELITE_XM_BASE = 0x7353182D,
	SERVICE_EARN_GANGOPS_ELITE_XM_SILO = 0x7D1FD84C,
	SERVICE_EARN_GANGOPS_ELITE_XM_SUBMARINE = 0x6E63A5AC,
	SERVICE_EARN_GANGOPS_FINALE = 0x46521174,
	SERVICE_EARN_GANGOPS_PREP_PARTICIPATION = 0x53E15D9D,
	SERVICE_EARN_GANGOPS_RIVAL_DELIVERY = 0x7462F9E7,
	SERVICE_EARN_GANGOPS_SETUP = 0xA1DC5A42,
	SERVICE_EARN_GANGOPS_SETUP_FAIL = 0xFE5D3D39,
	SERVICE_EARN_GANGOPS_WAGES = 0xCBC91B24,
	SERVICE_EARN_GANGOPS_WAGES_BONUS = 0xD4E9820B,
	SERVICE_EARN_GOON = 0x21ECDA63,
	SERVICE_EARN_HOLDUPS = 0x676706D3,
	SERVICE_EARN_IMPORT_EXPORT = 0x381AE70B,
	SERVICE_EARN_INITIAL_CASH = 0x666D4B21,
	SERVICE_EARN_JBONUS = 0x631FCDF7,
	SERVICE_EARN_JOBS = 0xC2C5E339,
	SERVICE_EARN_JOBSHARE_CASH = 0x89AD02CE,
	SERVICE_EARN_JOB_BONUS = 0xA174F633,
	SERVICE_EARN_JOB_BONUS_CRIMINAL_MASTERMIND = 0x3EBB7442,
	SERVICE_EARN_JOB_BONUS_FIRST_TIME_BONUS = 0xB6D37A76,
	SERVICE_EARN_JOB_BONUS_HEIST_AWARD = 0x8107BB89,
	SERVICE_EARN_LESTER_TARGET_KILL = 0xEAFF75BD,
	SERVICE_EARN_LOTTERY = 0x628502B3,
	SERVICE_EARN_NOT_BADSPORT = 0xBCD304B8,
	SERVICE_EARN_PERSONAL_VEHICLE = 0x016B1CDE,
	SERVICE_EARN_PICKUP = 0xFE249573,
	SERVICE_EARN_PREMIUM_JOB = 0xFD2A7DE7,
	SERVICE_EARN_PROPERTY_SALES = 0xB77DD8B4, //only 600,000 per second and a max of 1 billion before requires a short cooldown
	SERVICE_EARN_RDR_BONUS_ALL_SLOTS = 0x82120337,
	SERVICE_EARN_REFUNDAMMODROP = 0xD8630BC3,
	SERVICE_EARN_REFUND_BACKUP_FAMILIES = 0x5841CC24,
	SERVICE_EARN_REFUND_BACKUP_LOST = 0x29358006,
	SERVICE_EARN_REFUND_BACKUP_VAGOS = 0x4CBAC3AA,
	SERVICE_EARN_REFUND_BOAT_PICKUP = 0x267CBC1B,
	SERVICE_EARN_REFUND_BUY_CARDROPOFF = 0xF6C6F8D3,
	SERVICE_EARN_REFUND_CHALLENGE = 0x2AD8ED30,
	SERVICE_EARN_REFUND_CLEAR_WANTED = 0x2DC5587F,
	SERVICE_EARN_REFUND_HEAD_2_HEAD = 0x8A91E076,
	SERVICE_EARN_REFUND_HELI_PICKUP = 0xAEC77375,
	SERVICE_EARN_REFUND_HIRE_MERCENARY = 0x2183C4D7,
	SERVICE_EARN_REFUND_HIRE_MUGGER = 0x5A26EAEF,
	SERVICE_EARN_REFUND_LOTTERY = 0x3530C574,
	SERVICE_EARN_REFUND_ORBITAL_AUTO = 0x0CD9EBA6, //only 500,000 per 2 seconds and a max of 5 per 2 minutes
	SERVICE_EARN_REFUND_ORBITAL_MANUAL = 0x6F225978,
	SERVICE_EARN_REFUND_SHARE_LAST_JOB = 0x8B70731D,
	SERVICE_EARN_ROCKSTAR = 0x129A5B6E,
	SERVICE_EARN_SALVAGE_CHECKPOINT_COLLECTION = 0x23C04B23,
	SERVICE_EARN_SMUGGLER_AGENCY = 0x1B9AFE05,
	SERVICE_EARN_VEHICLE_SALES = 0xFD389995,
	SERVICE_EARN_WAGE_PAYMENT = 0xF9F62A7C,
	SERVICE_EARN_WAGE_PAYMENT_BONUS = 0x5C66709A,
	SERVICE_SPEND_AIRSTRIKE = 0x5A58E3BD,
	SERVICE_SPEND_AMMO_DROP = 0x45F48C05,
	SERVICE_SPEND_ARREST_BAIL = 0x108CD6EE,
	SERVICE_SPEND_BACKUP_GANG = 0xCA5E1B40,
	SERVICE_SPEND_BACKUP_HELI = 0xD86D0371,
	SERVICE_SPEND_BANK_INTEREST = 0xB62639D4,
	SERVICE_SPEND_BA_ENFORCER_ARMOUR = 0x3A732240,
	SERVICE_SPEND_BA_SARGE_AMMO = 0xABCC04E3,
	SERVICE_SPEND_BA_SARGE_MOLOTOV = 0x24D87C9E,
	SERVICE_SPEND_BA_VP_BOUNTY = 0x6F6E2AEA,
	SERVICE_SPEND_BA_VP_BULLSHARK = 0xEBECC7F6,
	SERVICE_SPEND_BETTING = 0x6597C63C,
	SERVICE_SPEND_BOAT_PICKUP = 0x48090EBA,
	SERVICE_SPEND_BOSS_BUY_IN = 0xD8825569,
	SERVICE_SPEND_BOUNTY = 0xDB72FD6E,
	SERVICE_SPEND_BOUNTY_DM = 0xFA3E19A3,
	SERVICE_SPEND_BULL_SHARK = 0xD80064A4,
	SERVICE_SPEND_BUSINESS = 0x10077806,
	SERVICE_SPEND_CALL_PLAYER = 0x62A4B6CC,
	SERVICE_SPEND_CARWASH = 0x467E2916,
	SERVICE_SPEND_CAR_IMPOUND = 0x11611C06,
	SERVICE_SPEND_CAR_REPAIR = 0x8180486D,
	SERVICE_SPEND_CASH_DROP = 0x79D2BE32,
	SERVICE_SPEND_CASH_DROP_HOLDUP = 0x3CF098E4,
	SERVICE_SPEND_CASH_GIFT = 0xF2BEFF3E,
	SERVICE_SPEND_CASH_SHARED = 0xB3E76D2C,
	SERVICE_SPEND_CHALLENGE_WAGER = 0x2A6B291E,
	SERVICE_SPEND_CINEMA = 0xC571DB3D,
	SERVICE_SPEND_COPS_TURN_EYE = 0xE7BA9A2C,
	SERVICE_SPEND_EMPLOY_ASSASSINS = 0xC88FBB63,
	SERVICE_SPEND_EXEC_UTILITY_BILLS = 0x2D80114E,
	SERVICE_SPEND_FAIRGROUND = 0x61F840EB,
	SERVICE_SPEND_GANGOPS_CANNON = 0xAB4EA4F8,
	SERVICE_SPEND_GANGOPS_REPAIR_COST = 0x798D498F,
	SERVICE_SPEND_GANGOPS_SKIP_MISSION = 0x98AE71E5,
	SERVICE_SPEND_GANGOPS_START_STRAND = 0x8F2EC53A,
	SERVICE_SPEND_GANGOPS_TRIP_SKIP = 0xA3DDECA8,
	SERVICE_SPEND_HEALTHCARE = 0xE13B1F5A,
	SERVICE_SPEND_HELI_PICKUP = 0xD30E80F5,
	SERVICE_SPEND_HIRE_MERCENARY = 0x8F9E64E9,
	SERVICE_SPEND_HIRE_MUGGER = 0x7323DAB3,
	SERVICE_SPEND_IMPORT_EXPORT_REPAIR = 0xF7E7A848,
	SERVICE_SPEND_IMPROMPTU_RACE_FEE = 0x5D40F1F0,
	SERVICE_SPEND_JUKEBOX = 0x75CD3B70,
	SERVICE_SPEND_LOCATE_VEHICLE = 0x3F79E8B3,
	SERVICE_SPEND_LOSE_WANTED_LEVEL = 0xF54343EF,
	SERVICE_SPEND_LOTTERY = 0x847B5E8A,
	SERVICE_SPEND_MATCH_ENTRY_FEE = 0x73AF3590,
	SERVICE_SPEND_MECHANIC_WAGE = 0x9DEFCB5B,
	SERVICE_SPEND_MOVE_YACHT = 0x25A6481F,
	SERVICE_SPEND_OFF_THE_RADAR = 0x7F096F7D,
	SERVICE_SPEND_ORBITAL_AUTO = 0xBDE2A7A2,
	SERVICE_SPEND_ORBITAL_MANUAL = 0x3BE27CE6,
	SERVICE_SPEND_ORDER_BODYGUARD_VEHICLE = 0x27A4C3FB,
	SERVICE_SPEND_ORDER_WAREHOUSE_VEHICLE = 0xB0AE4A42,
	SERVICE_SPEND_OTHER_PLAYER_HEALTHCARE = 0x3DC70F44,
	SERVICE_SPEND_PASSIVE = 0x601646D2,
	SERVICE_SPEND_PAY_BOSS = 0x7A31F111,
	SERVICE_SPEND_PAY_GOON = 0x978B277B,
	SERVICE_SPEND_PA_SERVICE_DANCER = 0x810E1BBE,
	SERVICE_SPEND_PA_SERVICE_HELI = 0x3DB5C654,
	SERVICE_SPEND_PA_SERVICE_HELI_PICKUP = 0x73BA02A6,
	SERVICE_SPEND_PA_SERVICE_IMPOUND = 0x046F00FE,
	SERVICE_SPEND_PA_SERVICE_SNACK = 0xB3796027,
	SERVICE_SPEND_PA_SERVICE_VEHICLE = 0x30D378F8,
	SERVICE_SPEND_PEGASUS_DELIVERY = 0x10E398B4,
	SERVICE_SPEND_PERSONAL_ASSISTANT = 0x6E53C312,
	SERVICE_SPEND_PERSONAL_VEHICLE_DROPOFF = 0x15DAFB97,
	SERVICE_SPEND_PLAYER_APPEARANCE = 0x29EDC819,
	SERVICE_SPEND_PROSTITUTES = 0xAEF994E9,
	SERVICE_SPEND_RACE_VEHICLE_RENTAL = 0xAD32107E,
	SERVICE_SPEND_RENAME_ORGANIZATION = 0x25CFCEFF,
	SERVICE_SPEND_REQUEST_HEIST = 0xE1286116,
	SERVICE_SPEND_REQUEST_JOB = 0x741DADD0,
	SERVICE_SPEND_REVEAL_PLAYERS = 0x421452FF,
	SERVICE_SPEND_ROBBED_BY_MUGGER = 0x6DA50854,
	SERVICE_SPEND_STRIP_CLUB = 0x1B14F96B,
	SERVICE_SPEND_STYLIST_FEE = 0xAB5042C6,
	SERVICE_SPEND_TAXI = 0x92AEAB9C,
	SERVICE_SPEND_TELESCOPE = 0x26C85CA3,
	SERVICE_SPEND_UTILITY_BILLS = 0xDD16A585,
	SERVICE_SPEND_VEHICLE_EXPORT_MODS = 0x1A108B80,
	SERVICE_SPEND_VEHICLE_INSURANCE = 0xCBBC5D1E,
	SERVICE_SPEND_VEHICLE_INSURANCE_PREMIUM = 0x040E0F34,
	SERVICE_SPEND_WAGER = 0x2C41A631,
	TEST_1 = 0x408A6C26,
	TEST_2 = 0xD7858229
};

enum TransactionCategory {
	CATEGORY_SERVICE_WITH_THRESHOLD = 0x57DE404E,
	CATEGORY_SERVICE_UNLOCKED = 0x92257108,
	CATEGORY_SERVICE_WITH_LIMIT = 0xBC5B83BA,
	CATEGORY_SERVICE_ANTI_CHEAT = 0xAE04310C // sophisticated as fuck
};

enum TransactionActionType {
	ACTION_TYPE_SERVICE_SPEND = 0x2005D9A9,
	ACTION_TYPE_SERVICE_EARN = 0x562592BB,
};

enum TransactionTarget {
	TARGET_CASH = 1,
	TARGET_BANK = 2,
	TARGET_CASH_THEN_BANK = 8, // iirc
};

enum TransactionType {
	TYPE_DEFAULT = 0xBC537E0D // idk. that one is used for transactions from any script tho
};

class CNetShopTransaction {
public:
	char pad_0000[8]; //0x0000
	uint32_t TransactionId; //0x0008
	int32_t TypeHash; //0x000C
	char pad_0010[8]; //0x0010
	int32_t CategoryHash; //0x0018
	char pad_001C[8]; //0x001C
	int32_t ActionTypeHash; //0x0024
	uint32_t Target; //0x0028
	char pad_002C[180]; //0x002C
	int32_t ServiceHash; //0x00E0
	char pad_00E4[4]; //0x00E4
	uint64_t Amount; //0x00E8
	uint32_t Multiplier; //0x00F0
}; //Size: 0x0678

class NetshopQueue {
public:
	char pad_0000[32]; //0x0000
	class RageNode<CNetShopTransaction>* First; //0x0020
	class RageNode<CNetShopTransaction>* Last; //0x0028
	char pad_0030[9]; //0x0030
	bool IsBusy1; //0x0039
	char pad_003A[14]; //0x003A
	bool IsBusy2; //0x0048
	char pad_0049[7]; //0x0049
	bool IsBusy3; //0x0050
}; //Size: 0x0051

class NetCatalogBaseItem {
public:
	char pad_0000[8]; //0x0000
	uint32_t Hash; //0x0008
	uint32_t CategoryHash; //0x000C
	uint32_t Price; //0x0010
}; //Size: 0x0014

template<class T>
class HashList {

	char pad_0000[88]; //0x0000
	void* m_data; //0x0058
	uint16_t m_size; //0x0060

public:

	T *getEntry(const DWORD hash) {
		if (this->m_size) {
			const auto offset = hash % this->m_size * 8;

			for (auto i = *reinterpret_cast<unsigned __int64 *>(reinterpret_cast<unsigned __int64>(this->m_data) + offset); ; i = *reinterpret_cast<unsigned __int64 *>(i + 0x10)) {
				if (!i) {
					return nullptr;
				}

				if (*reinterpret_cast<DWORD *>(i) == hash) {
					return *reinterpret_cast<T **>(i + 8);
				}
			}
		}
	}
};

class NetCatalog {
public:
	char pad_0000[88]; //0x0000
	void* CatalogItems; //0x0058
	uint16_t CatalogSize; //0x0060
	char pad_0062[26]; //0x0062
	uint32_t CatalogVersion; //0x007C

	template<class T>
	T* getCatalogEntry(const DWORD hash) {
		if (this->CatalogSize) {
			const auto offset = hash % this->CatalogSize * 8;

			for (auto i = *reinterpret_cast<QWORD*>(reinterpret_cast<QWORD>(this->CatalogItems) + offset); ; i = *reinterpret_cast<QWORD*>(i + 0x10)) {
				if (!i) {
					return nullptr;
				}

				if (*reinterpret_cast<DWORD*>(i) == hash) {
					return *reinterpret_cast<T * *>(i + 8);
				}
			}
		}

		return nullptr;
	}

	int getServiceThreshold(const DWORD service) {
		const auto item = this->getCatalogEntry<NetCatalogBaseItem>(service);

		return item ? item->Price : -1;
	}
}; //Size: 0x0062

namespace ReClass {
	CWorld* GetWorld();
	CNetworkPlayerManager* GetNetworkPlayerManager();
}

enum eExplosionHashes {
	EXP_TAG_GRENADE = 0x8A81EE87,
	EXP_TAG_GRENADELAUNCHER = 0x70768AE2,
	EXP_TAG_STICKYBOMB = 0x00776EE2,
	EXP_TAG_MOLOTOV = 0xF06FF2EA,
	EXP_TAG_ROCKET = 0x6E26E617,
	EXP_TAG_TANKSHELL = 0xF7F926C6,
	EXP_TAG_HI_OCTANE = 0x06A02001,
	EXP_TAG_CAR = 0x873EFA90,
	EXP_TAG_PLANE = 0x1EFAECAF,
	EXP_TAG_PETROL_PUMP = 0xF9C8CA18,
	EXP_TAG_BIKE = 0xB0982FC3,
	EXP_TAG_DIR_STEAM = 0xA1DCCBA6,
	EXP_TAG_DIR_FLAME = 0x68AB5E33,
	EXP_TAG_DIR_WATER_HYDRANT = 0x1FD48F6A,
	EXP_TAG_DIR_GAS_CANISTER = 0xD26A85F8,
	EXP_TAG_BOAT = 0x78C99422,
	EXP_TAG_SHIP_DESTROY = 0xA30CE475,
	EXP_TAG_TRUCK = 0x38C51930,
	EXP_TAG_BULLET = 0xC10B20E5,
	EXP_TAG_SMOKEGRENADELAUNCHER = 0x8E6F4BED,
	EXP_TAG_SMOKEGRENADE = 0xF910656E,
	EXP_TAG_BZGAS = 0x69BBC23A,
	EXP_TAG_FLARE = 0x5E2703F4,
	EXP_TAG_GAS_CANISTER = 0xC946D0BE,
	EXP_TAG_EXTINGUISHER = 0x9D23C3A1,
	EXP_TAG_PROGRAMMABLEAR = 0x407BB75E,
	EXP_TAG_TRAIN = 0x6DC5550C,
	EXP_TAG_BARREL = 0x41218EB0,
	EXP_TAG_PROPANE = 0x6DF18414,
	EXP_TAG_BLIMP = 0x9FE41D96,
	EXP_TAG_DIR_FLAME_EXPLODE = 0xFFE56FF4,
	EXP_TAG_TANKER = 0x2FA09A72,
	EXP_TAG_PLANE_ROCKET = 0x932F3E8F,
	EXP_TAG_VEHICLE_BULLET = 0x64DB13C9,
	EXP_TAG_GAS_TANK = 0xC717B00D,
	EXP_TAG_PROXMINE = 0x5AF62252,
	EXP_TAG_SNOWBALL = 0x4C4099F,
	EXP_TAG_AIR_DEFENCE = 0xD1653345,
	EXP_TAG_PIPEBOMB = 0x8123C100,
	EXP_TAG_VEHICLEMINE = 0x2E172C48,
	EXP_TAG_EXPLOSIVEAMMO = 0x958EE7C8,
	EXP_TAG_APCSHELL = 0x62412BA9,
	EXP_TAG_VALKYRIE_CANNON = 0xB780A2D9,
};

enum eExplosionFXHashes {
	EXP_VFXTAG_GRENADE = 0x8CBD7381,
	EXP_VFXTAG_STICKYBOMB = 0x6818372E,
	EXP_VFXTAG_MOLOTOV = 0x289C84AB,
	EXP_VFXTAG_ROCKET = 0xC18A7083,
	EXP_VFXTAG_PETROL_PUMP = 0x5C685140,
	EXP_VFXTAG_VEHICLE = 0x1FDD8CC7,
	EXP_VFXTAG_BIKE = 0x2E89B6C6,
	EXP_VFXTAG_DIR_STEAM = 0xB096860,
	EXP_VFXTAG_DIR_FLAME = 0x61BEF304,
	EXP_VFXTAG_DIR_WATER_HYDRANT = 0xC9E6266C,
	EXP_VFXTAG_DIR_GAS_CANISTER = 0xDCD1237B,
	EXP_VFXTAG_TRUCK = 0x272C2A1C,
	EXP_VFXTAG_BULLET = 0x4A602D1B,
	EXP_VFXTAG_SMOKE_GRENADE = 0x1B171B0A,
	EXP_VFXTAG_BZGAS = 0xC36F9FF4,
	EXP_VFXTAG_FBI4_TRUCK_DOORS = 0x68EC3F3E,
	EXP_VFXTAG_GAS_CANISTER = 0x531AE6D7,
	EXP_VFXTAG_EXTINGUISHER = 0x3C212E68,
	EXP_VFXTAG_TRAIN = 0x7DF5D791,
	EXP_VFXTAG_BARREL = 0x26A49BC,
	EXP_VFXTAG_PROPANE = 0x2A8D8114,
	EXP_VFXTAG_BLIMP = 0xBA683EF5,
	EXP_VFXTAG_FLARE = 0x4DFE55EF,
	EXP_VFXTAG_PLANE_ROCKET = 0x549AE743,
	EXP_VFXTAG_TANKER = 0x6136E279,
	EXP_VFXTAG_PLANE = 0x174DDF67,
	EXP_VFXTAG_BOAT = 0x9AE5CE85,
	EXP_VFXTAG_TANKSHELL = 0xC6109DA9,
	EXP_VFXTAG_TREV3_TRAILER = 0x567CAF1C,
	EXP_VFXTAG_BLIMP2 = 0x9077376B,
	EXP_VFXTAG_BIRDCRAP = 0x8B716982,
	EXP_VFXTAG_FIREWORK = 0x1499FEF9,
	EXP_VFXTAG_SNOWBALL = 0x4B0245BA,
	EXP_VFXTAG_AIR_DEFENCE = 0x3C84F30B,
	EXP_VFXTAG_PIPEBOMB = 0x2E3BC2D6,
	EXP_VFXTAG_BOMB_CLUSTER = 0x7007891E,
	EXP_VFXTAG_BOMB_GAS = 0xAD0A7E5D,
	EXP_VFXTAG_BOMB_INCENDIARY = 0x62F8744D,
	EXP_VFXTAG_BOMB_STANDARD = 0x30A5254A,
	EXP_VFXTAG_TORPEDO_UNDERWATER = 0x8D16EE2E,
	EXP_VFXTAG_MINE_UNDERWATER = 0x4F7CD2DC
};