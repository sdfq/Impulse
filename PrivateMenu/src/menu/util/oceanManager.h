#pragma once
struct sWaterTune {
	int WaterColor;
	float RippleScale;
	float OceanFoamScale;
	float SpecularFalloff;
	float FogPierceIntensity;
	float RefractionBlend;
	float RefractionExponent;
	float WaterCycleDepth;
	float WaterCycleFade;
	float WaterLightningDepth;
	float WaterLightningFade;
	float DeepWaterModDepth;
	float DeepWaterModFade;
	float GodRaysLerpStart;
	float GodRaysLerpEnd;
	float DisturbFoamScale;
	float FogMin[2];
	float FogMax[2];
};

class OceanManager {
public:
	struct QuadInfo {
		uint64_t m_quadPool;
		short m_quadCount;
	};

	struct WaterQuads {
		QuadInfo* m_oceanQuads;
	} m_waterQuads;
	float* m_waveIntensity;

	sWaterTune* m_WaterTune;
public:
	bool Init();
	void NoOcean(bool toggle);
	void ClearWater(bool toggle);
	void SetWaveIntensity(float intensity);

	static bool Initialize();
};

OceanManager* GetOceanManager();