#pragma once

class VFXVehicle;
class VFXVehicleFade;
class VFXVehicleHeadlights;
class VFXTrafficLight;
class VFXTrain;
class VFXCorona;
class VFXDistantLights;
class VFXToneMapping;
class VFXSky;
class VFXPuddles;
class VFXPuddlesRipples;
class VFXVehicleNeon;

class VFXVehicle {
public:
	float m_headLightAngle; //0x0000 
	float m_headLightSplit; //0x0004 
	char pad_0x0008[0x2C38]; //0x0008

}; //Size=0x2C40

class VFXVehicleFade {
public:
	float m_fadeDistance; //0x0000 
	char pad_0x0004[0x3C]; //0x0004

}; //Size=0x0040

class VFXVehicleHeadlights {
public:
	float m_headlightIntensity; //0x0000 
	char pad_0x0004[0x80]; //0x0004
	float m_headlightDistance; //0x0084 
	char pad_0x0088[0x7D0]; //0x0088
	float m_headlightPlayerIntensity; //0x0858 
	float m_headlightPlayerDistance; //0x085C 
	char pad_0x0860[0x108]; //0x0860
	float m_headlightPlayerExponent; //0x0968 
	char pad_0x096C[0x6D4]; //0x096C

}; //Size=0x1040

class VFXTrafficLight {
public:
	float m_walkR; //0x0000 
	float m_walkG; //0x0004 
	float m_walkB; //0x0008 
	char pad_0x000C[0x14]; //0x000C
	float m_greenR; //0x0020 
	float m_greenG; //0x0024 
	float m_greenB; //0x0028 
	char pad_0x002C[0x2A74]; //0x002C
	float m_dontWalkR; //0x2AA0 
	float m_dontWalkG; //0x2AA4 
	float m_dontWalkB; //0x2AA8 
	char pad_0x2AAC[0x2584]; //0x2AAC
	float m_orangeR; //0x5030 
	float m_orangeG; //0x5034 
	float m_orangeB; //0x5038 
	char pad_0x503C[0xDE4]; //0x503C
	float m_redR; //0x5E20 
	float m_redG; //0x5E24 
	float m_redB; //0x5E28 
	char pad_0x5E2C[0x4A14]; //0x5E2C

}; //Size=0xA840

class VFXTrain {
public:
	float m_colorR; //0x0000 
	float m_colorG; //0x0004 
	char pad_0x0008[0xA8]; //0x0008
	float m_colorB; //0x00B0 
	float m_intensity; //0x00B4 
	char pad_0x00B8[0x788]; //0x00B8

}; //Size=0x0840

class VFXCorona {
public:
	float m_globalSize; //0x0000 
	float m_globalIntensity; //0x0004 
	float m_waterIntensity; //0x0008 
	float m_waterSize; //0x000C 
	float m_sizeScaleParaboloid; //0x0010 
	float m_globalScreenspaceExpansion; //0x0014 
	float m_waterScreenspaceExpansion; //0x0018 
	float m_zBiasMultiplier; //0x001C 
	char pad_0x0020[0x24]; //0x0020
	float m_rotationSpeed; //0x0044 
	char pad_0x0048[0x38]; //0x0048
	float N0000216D; //0x0080 
	float m_colorR; //0x0084 
	float m_colorG; //0x0088 
	float m_colorB; //0x008C 
	char pad_0x0090[0x3F0]; //0x0090

}; //Size=0x0480

class VFXDistantLights {
public:
	float m_size; //0x0000 
	float m_reflectionsSize; //0x0004 
	float m_sizeMin; //0x0008 
	float m_sizeUpscale; //0x000C 
	float m_sizeUpscaleReflections; //0x0010 
	float m_vehicleHDRIntensity; //0x0014 
	float m_streetlightHDRIntensity; //0x0018 
	float m_flicker; //0x001C 
	float m_twinkleSpeed; //0x0020 
	float m_twinkleAmount; //0x0024 
	float m_vehicleZOffset; //0x0028 
	char pad_0x002C[0x8]; //0x002C
	float m_hourStart; //0x0034 
	float m_hourEnd; //0x0038 
	float m_streetlightHourStart; //0x003C 
	float m_streetlightHourEnd; //0x0040 
	char pad_0x0044[0x8]; //0x0044
	Vector3_t m_speed; //0x004C 
	char pad_0x0058[0x38]; //0x0058
	float m_vehicleColorR; //0x0090 
	float m_vehicleColorG; //0x0094 
	float m_vehicleColorB; //0x0098 
	char pad_0x009C[0x14]; //0x009C
	float m_vehicleColor2R; //0x00B0 
	float m_vehicleColor2G; //0x00B4 
	float m_vehicleColor2B; //0x00B8 
	char pad_0x00BC[0x14]; //0x00BC
	float m_streetlightColorR; //0x00D0 
	float m_streetlightColorG; //0x00D4 
	float m_streetlightColorB; //0x00D8 
	char pad_0x00DC[0x764]; //0x00DC

}; //Size=0x0840

class VFXToneMapping {
public:
	float m_darkFilmicA; //0x0000 
	float m_darkFilmicB; //0x0004 
	float m_darkFilmicC; //0x0008 
	float m_darkFilmicD; //0x000C 
	float m_darkFilmicE; //0x0010 
	float m_darkFilmicF; //0x0014 
	float m_darkFilmicW; //0x0018 
	float m_darkFilmicExposure; //0x001C 
	float m_brightFilmicA; //0x0020 
	float m_brightFilmicB; //0x0024 
	float m_brightFilmicC; //0x0028 
	float m_brightFilmicD; //0x002C 
	float m_brightFilmicE; //0x0030 
	float m_brightFilmicF; //0x0034 
	float m_brightFilmicW; //0x0038 
	float m_brightFilmicExposure; //0x003C 
	char pad_0x0040[0x1DD8]; //0x0040
	float m_sunExposure; //0x1E18 
	char pad_0x1E1C[0x224]; //0x1E1C

}; //Size=0x2040

class VFXSky {
public:
	char pad_0x0000[0x220]; //0x0000
	float m_sunDiscColorR; //0x0220 
	float m_sunDiscColorG; //0x0224 
	float m_sunDiscColorB; //0x0228 
	char pad_0x022C[0x138]; //0x022C
	float m_edgeDetailScale; //0x0364 
	char pad_0x0368[0x4]; //0x0368
	float m_overlayDetailScale; //0x036C 
	char pad_0x0370[0x150]; //0x0370
	float m_cloudSpeedLarge; //0x04C0 
	float m_cloudSpeedSmall; //0x04C4 
	float m_cloudSpeedOverall; //0x04C8 
	float m_speedEdge; //0x04CC 
	float m_speedHats; //0x04D0 
	char pad_0x04D4[0x36C]; //0x04D4

}; //Size=0x0840

class VFXPuddles {
public:
	char pad_0x0000[0x70]; //0x0000
	float m_scale; //0x0070 
	float m_range; //0x0074 
	float m_depth; //0x0078 
	char pad_0x007C[0x34]; //0x007C
	VFXPuddlesRipples* m_ripples; //0x00B0 

}; //Size=0x00B8

class VFXPuddlesRipples {
public:
	char pad_0x0000[0xF50]; //0x0000
	float m_minSize; //0x0F50 
	float m_maxSize; //0x0F54 
	float m_minDuration; //0x0F58 
	float m_maxDuration; //0x0F5C 
	float m_speed; //0x0F60 
	float m_dropFactor; //0x0F64 
	char pad_0x0F68[0x8]; //0x0F68
	float m_rippleStrength; //0x0F70 
	char pad_0x0F74[0x494]; //0x0F74

}; //Size=0x1408

class VFXVehicleNeon {
public:
	float m_intensity; //0x0000 
	float m_radius; //0x0004 
	char pad_0x0008[0x1F0]; //0x0008
	float m_falloffExponent; //0x01F8 
	char pad_0x01FC[0x2C]; //0x01FC
	float m_extentFront; //0x0228 
	char pad_0x022C[0x1C]; //0x022C
	float m_extendSides; //0x0248 
	char pad_0x024C[0x4]; //0x024C
	float m_clippingPaneHeight; //0x0250 
	char pad_0x0254[0x5EC]; //0x0254

}; //Size=0x0840

class VFX {
private:
	static VFXVehicleHeadlights* m_VFXVehicleHeadlights;
	static VFXVehicleHeadlights m_OVFXVehicleHeadlights;
	static VFXPuddlesRipples m_OVFXPuddlesRipples;
	static VFXDistantLights* m_VFXDistantLights;
	static VFXDistantLights m_OVFXDistantLights;
	static VFXTrafficLight* m_VFXTrafficlights;
	static VFXTrafficLight m_OVFXTrafficlights;
	static VFXVehicleNeon* m_VFXVehicleNeon;
	static VFXVehicleNeon m_OVFXVehicleNeon;
	static VFXToneMapping* m_VFXToneMapping;
	static VFXToneMapping m_OVFXToneMapping;
	static VFXVehicleFade* m_VFXVehicleFade;
	static VFXVehicleFade m_OVFXVehicleFade;
	static VFXVehicle* m_VFXVehicle;;
	static VFXVehicle m_OVFXVehicle;;
	static VFXPuddles* m_VFXPuddles;
	static VFXPuddles m_OVFXPuddles;
	static VFXCorona* m_VFXCoronas;
	static VFXCorona m_OVFXCoronas;
	static VFXTrain* m_VFXTrains;
	static VFXTrain m_OVFXTrains;
	static VFXSky* m_VFXSky;
	static VFXSky m_OVFXSky;

public:
	bool Initialize();

	VFXVehicleHeadlights* GetVehicleHeadlights() { return m_VFXVehicleHeadlights; }
	VFXDistantLights* GetDistantLights() { return m_VFXDistantLights; }
	VFXTrafficLight* GetTrafficLights() { return m_VFXTrafficlights; }
	VFXVehicleNeon* GetVehicleNeon() { return m_VFXVehicleNeon; }
	VFXToneMapping* GetTonemapping() { return m_VFXToneMapping; }
	VFXVehicleFade* GetVehicleFade() { return m_VFXVehicleFade; }
	VFXVehicle* GetVehicle() { return m_VFXVehicle; }
	VFXPuddles* GetPuddles() { return m_VFXPuddles; }
	VFXCorona* GetCoronas() { return m_VFXCoronas; }
	VFXTrain* GetTrains() { return m_VFXTrains; }
	VFXSky* GetSky() { return m_VFXSky; }

	void ResetVehicleHeadlights() {
		if (!m_VFXVehicleHeadlights) return;
		m_VFXVehicleHeadlights->m_headlightDistance = m_OVFXVehicleHeadlights.m_headlightDistance;
		m_VFXVehicleHeadlights->m_headlightIntensity = m_OVFXVehicleHeadlights.m_headlightIntensity;
		m_VFXVehicleHeadlights->m_headlightPlayerDistance = m_OVFXVehicleHeadlights.m_headlightPlayerDistance;
		m_VFXVehicleHeadlights->m_headlightPlayerExponent = m_OVFXVehicleHeadlights.m_headlightPlayerExponent;
		m_VFXVehicleHeadlights->m_headlightPlayerIntensity = m_OVFXVehicleHeadlights.m_headlightPlayerIntensity;
	}

	void ResetDistantLights() {
		if (!m_VFXDistantLights) return;
		m_VFXDistantLights->m_flicker = m_OVFXDistantLights.m_flicker;
		m_VFXDistantLights->m_hourEnd = m_OVFXDistantLights.m_hourEnd;
		m_VFXDistantLights->m_hourStart = m_OVFXDistantLights.m_hourStart;
		m_VFXDistantLights->m_reflectionsSize = m_OVFXDistantLights.m_reflectionsSize;
		m_VFXDistantLights->m_size = m_OVFXDistantLights.m_size;
		m_VFXDistantLights->m_sizeMin = m_OVFXDistantLights.m_sizeMin;
		m_VFXDistantLights->m_sizeUpscale = m_OVFXDistantLights.m_sizeUpscale;
		m_VFXDistantLights->m_sizeUpscaleReflections = m_OVFXDistantLights.m_sizeUpscaleReflections;
		m_VFXDistantLights->m_speed = m_OVFXDistantLights.m_speed;
		m_VFXDistantLights->m_streetlightColorR = m_OVFXDistantLights.m_streetlightColorR;
		m_VFXDistantLights->m_streetlightColorG = m_OVFXDistantLights.m_streetlightColorG;
		m_VFXDistantLights->m_streetlightColorB = m_OVFXDistantLights.m_streetlightColorB;
		m_VFXDistantLights->m_streetlightHDRIntensity = m_OVFXDistantLights.m_streetlightHDRIntensity;
		m_VFXDistantLights->m_streetlightHourEnd = m_OVFXDistantLights.m_streetlightHourEnd;
		m_VFXDistantLights->m_streetlightHourStart = m_OVFXDistantLights.m_streetlightHourStart;
		m_VFXDistantLights->m_twinkleAmount = m_OVFXDistantLights.m_twinkleAmount;
		m_VFXDistantLights->m_twinkleSpeed = m_OVFXDistantLights.m_twinkleSpeed;
		m_VFXDistantLights->m_vehicleColorR = m_OVFXDistantLights.m_vehicleColorR;
		m_VFXDistantLights->m_vehicleColorG = m_OVFXDistantLights.m_vehicleColorG;
		m_VFXDistantLights->m_vehicleColorB = m_OVFXDistantLights.m_vehicleColorB;
		m_VFXDistantLights->m_vehicleColor2R = m_OVFXDistantLights.m_vehicleColor2R;
		m_VFXDistantLights->m_vehicleColor2G = m_OVFXDistantLights.m_vehicleColor2G;
		m_VFXDistantLights->m_vehicleColor2B = m_OVFXDistantLights.m_vehicleColor2B;
		m_VFXDistantLights->m_vehicleHDRIntensity = m_OVFXDistantLights.m_vehicleHDRIntensity;
		m_VFXDistantLights->m_vehicleZOffset = m_OVFXDistantLights.m_vehicleZOffset;
	}

	void ResetTrafficLights() {
		if (!m_VFXTrafficlights) return;
		m_VFXTrafficlights->m_dontWalkR = m_OVFXTrafficlights.m_dontWalkR;
		m_VFXTrafficlights->m_dontWalkG = m_OVFXTrafficlights.m_dontWalkG;
		m_VFXTrafficlights->m_dontWalkB = m_OVFXTrafficlights.m_dontWalkB;
		m_VFXTrafficlights->m_walkR = m_OVFXTrafficlights.m_walkR;
		m_VFXTrafficlights->m_walkG = m_OVFXTrafficlights.m_walkG;
		m_VFXTrafficlights->m_walkB = m_OVFXTrafficlights.m_walkB;
		m_VFXTrafficlights->m_greenR = m_OVFXTrafficlights.m_greenR;
		m_VFXTrafficlights->m_greenG = m_OVFXTrafficlights.m_greenG;
		m_VFXTrafficlights->m_greenB = m_OVFXTrafficlights.m_greenB;
		m_VFXTrafficlights->m_orangeR = m_OVFXTrafficlights.m_orangeR;
		m_VFXTrafficlights->m_orangeG = m_OVFXTrafficlights.m_orangeG;
		m_VFXTrafficlights->m_orangeB = m_OVFXTrafficlights.m_orangeB;
		m_VFXTrafficlights->m_redR = m_OVFXTrafficlights.m_redR;
		m_VFXTrafficlights->m_redG = m_OVFXTrafficlights.m_redG;
		m_VFXTrafficlights->m_redB = m_OVFXTrafficlights.m_redB;
	}

	void ResetVehicleNeon() {
		if (!m_VFXVehicleNeon)return;
		m_VFXVehicleNeon->m_clippingPaneHeight = m_OVFXVehicleNeon.m_clippingPaneHeight;
		m_VFXVehicleNeon->m_extendSides = m_OVFXVehicleNeon.m_extendSides;
		m_VFXVehicleNeon->m_extentFront = m_OVFXVehicleNeon.m_extentFront;
		m_VFXVehicleNeon->m_falloffExponent = m_OVFXVehicleNeon.m_falloffExponent;
		m_VFXVehicleNeon->m_intensity = m_OVFXVehicleNeon.m_intensity;
		m_VFXVehicleNeon->m_radius = m_OVFXVehicleNeon.m_radius;
	}

	void ResetTonemapping() {
		if (!m_VFXToneMapping) return;
		m_VFXToneMapping->m_brightFilmicA = m_OVFXToneMapping.m_brightFilmicA;
		m_VFXToneMapping->m_brightFilmicB = m_OVFXToneMapping.m_brightFilmicB;
		m_VFXToneMapping->m_brightFilmicC = m_OVFXToneMapping.m_brightFilmicC;
		m_VFXToneMapping->m_brightFilmicD = m_OVFXToneMapping.m_brightFilmicD;
		m_VFXToneMapping->m_brightFilmicE = m_OVFXToneMapping.m_brightFilmicE;
		m_VFXToneMapping->m_brightFilmicF = m_OVFXToneMapping.m_brightFilmicF;
		m_VFXToneMapping->m_brightFilmicW = m_OVFXToneMapping.m_brightFilmicW;
		m_VFXToneMapping->m_brightFilmicExposure = m_OVFXToneMapping.m_brightFilmicExposure;
		m_VFXToneMapping->m_darkFilmicA = m_OVFXToneMapping.m_darkFilmicA;
		m_VFXToneMapping->m_darkFilmicB = m_OVFXToneMapping.m_darkFilmicB;
		m_VFXToneMapping->m_darkFilmicC = m_OVFXToneMapping.m_darkFilmicC;
		m_VFXToneMapping->m_darkFilmicD = m_OVFXToneMapping.m_darkFilmicD;
		m_VFXToneMapping->m_darkFilmicE = m_OVFXToneMapping.m_darkFilmicE;
		m_VFXToneMapping->m_darkFilmicF = m_OVFXToneMapping.m_darkFilmicF;
		m_VFXToneMapping->m_darkFilmicW = m_OVFXToneMapping.m_darkFilmicW;
		m_VFXToneMapping->m_darkFilmicExposure = m_OVFXToneMapping.m_darkFilmicExposure;
	}

	void ResetVehicleFade() {
		if (!m_VFXVehicleFade) return;
		m_VFXVehicleFade->m_fadeDistance = m_OVFXVehicleFade.m_fadeDistance;
	}

	void ResetVehicle() {
		if (!m_VFXVehicle) return;
		m_VFXVehicle->m_headLightAngle = m_OVFXVehicle.m_headLightAngle;
		m_VFXVehicle->m_headLightSplit = m_OVFXVehicle.m_headLightSplit;
	}

	void ResetPuddles() {
		if (!m_VFXPuddles) return;
		m_VFXPuddles->m_depth = m_OVFXPuddles.m_depth;
		m_VFXPuddles->m_range = m_OVFXPuddles.m_range;
		m_VFXPuddles->m_scale = m_OVFXPuddles.m_scale;
		if (!m_VFXPuddles->m_ripples) return;
		m_VFXPuddles->m_ripples->m_dropFactor = m_OVFXPuddlesRipples.m_dropFactor;
		m_VFXPuddles->m_ripples->m_maxDuration = m_OVFXPuddlesRipples.m_maxDuration;
		m_VFXPuddles->m_ripples->m_maxSize = m_OVFXPuddlesRipples.m_maxSize;
		m_VFXPuddles->m_ripples->m_minDuration = m_OVFXPuddlesRipples.m_minDuration;
		m_VFXPuddles->m_ripples->m_minSize = m_OVFXPuddlesRipples.m_minSize;
		m_VFXPuddles->m_ripples->m_rippleStrength = m_OVFXPuddlesRipples.m_dropFactor;
		m_VFXPuddles->m_ripples->m_speed = m_OVFXPuddlesRipples.m_speed;
	}

	void ResetCoronas() {
		if (!m_VFXCoronas) return;
		m_VFXCoronas->m_colorR = m_OVFXCoronas.m_colorR;
		m_VFXCoronas->m_colorG = m_OVFXCoronas.m_colorG;
		m_VFXCoronas->m_colorB = m_OVFXCoronas.m_colorB;
		m_VFXCoronas->m_globalIntensity = m_OVFXCoronas.m_globalIntensity;
		m_VFXCoronas->m_globalScreenspaceExpansion = m_OVFXCoronas.m_globalScreenspaceExpansion;
		m_VFXCoronas->m_globalSize = m_OVFXCoronas.m_globalSize;
		m_VFXCoronas->m_rotationSpeed = m_OVFXCoronas.m_rotationSpeed;
		m_VFXCoronas->m_sizeScaleParaboloid = m_OVFXCoronas.m_sizeScaleParaboloid;
		m_VFXCoronas->m_waterIntensity = m_OVFXCoronas.m_waterIntensity;
		m_VFXCoronas->m_waterScreenspaceExpansion = m_OVFXCoronas.m_waterScreenspaceExpansion;
		m_VFXCoronas->m_waterSize = m_OVFXCoronas.m_waterSize;
		m_VFXCoronas->m_zBiasMultiplier = m_OVFXCoronas.m_zBiasMultiplier;
	}

	void ResetTrains() {
		if (!m_VFXTrains) return;
		m_VFXTrains->m_colorR = m_OVFXTrains.m_colorR;
		m_VFXTrains->m_colorG = m_OVFXTrains.m_colorG;
		m_VFXTrains->m_colorB = m_OVFXTrains.m_colorB;
		m_VFXTrains->m_intensity = m_OVFXTrains.m_intensity;
	}

	void ResetSky() {
		if (!m_VFXSky) return;
		m_VFXSky->m_cloudSpeedLarge = m_OVFXSky.m_cloudSpeedLarge;
		m_VFXSky->m_cloudSpeedOverall = m_OVFXSky.m_cloudSpeedOverall;
		m_VFXSky->m_cloudSpeedSmall = m_OVFXSky.m_cloudSpeedSmall;
		m_VFXSky->m_edgeDetailScale = m_OVFXSky.m_edgeDetailScale;
		m_VFXSky->m_overlayDetailScale = m_OVFXSky.m_overlayDetailScale;
		m_VFXSky->m_speedEdge = m_OVFXSky.m_speedEdge;
		m_VFXSky->m_speedHats = m_OVFXSky.m_speedHats;
		m_VFXSky->m_sunDiscColorR = m_OVFXSky.m_sunDiscColorR;
		m_VFXSky->m_sunDiscColorG = m_OVFXSky.m_sunDiscColorG;
		m_VFXSky->m_sunDiscColorB = m_OVFXSky.m_sunDiscColorB;
	}

	void ResetAll() {
		ResetVehicleHeadlights();
		ResetDistantLights();
		ResetTrafficLights();
		ResetVehicleNeon();
		ResetTonemapping();
		ResetVehicleFade();
		ResetVehicle();
		ResetPuddles();
		ResetCoronas();
		ResetTrains();
		ResetSky();
	}
};

VFX* GetVFX();