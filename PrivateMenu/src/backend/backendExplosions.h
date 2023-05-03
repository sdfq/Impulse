#pragma once
#include "stdafx.h"


class Explosions {
public:


	struct sExplosion {
		char* ExplosionName;
		int Unk1;
		int Unk2;
		float DamageAtCentre;
		float DamageAtEdge;
		float NetworkPlayerModifier;
		float NetworkPedModifier;
		float EndRadius;
		float InitSpeed;
		float DecayFactor;
		float ForceFactor;
		float RagdollForceModifier;
		float SelfForceModifier;
		float DirectedWidth;
		float DirectedLifeTime;
		float CamShake;
		float CamShakeRollOffScaling;
		float ShockingEventVisualRangeOverride;
		float ShockingEventAudioRangeOverride;
		float FragDamage;
		bool MinorExplosion;
		bool AppliesContinuousDamage;
		bool PostProcessCollisionsWithNoForce;
		bool DamageVehicles;
		bool DamageObjects;
		bool OnlyAffectsLivePeds;
		bool IgnoreExplodingEntity;
		bool NoOcclusion;
		bool ExplodeAttachEntityWhenFinished;
		bool CanSetPedOnFire;
		bool CanSetPlayerOnFire;
		bool SuppressCrime;
		bool UseDistanceDamageCalc;
		bool PreventWaterExplosionVFX;
		bool IgnoreRatioCheckForFire;
		bool AllowUnderwaterExplosion;
		int Unk3;
		float Unk4;
		float Unk5;
		int CamShakeNameHash;
		int VFXTagNameHash;
	};

	struct sExplosionFX {
		Hash NameHash;
		char Unk[0x20];
		float Scale;
		char Unk2[0x38];
	};

	struct HashTranslation {
		char *string;
		Hash hash;
	};

	static bool PreGame();
	static bool hasPopulated;

	static sExplosion* ExplosionsData;
	static sExplosionFX* ExplosionsFXData;

	static int GetExplosionFXEntry(Hash hash);
	static sExplosion* GetExplosion(Hash ExplosionHash);
	static sExplosionFX* GetExplosionFX(Hash ExplosionFXHash);
};