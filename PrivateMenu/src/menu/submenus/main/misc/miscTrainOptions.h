#pragma once
#include "../../../submenu.h"

class MiscTrainOptions : public Submenu {
public:
	static MiscTrainOptions* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	MiscTrainOptions() : Submenu() {}
	~MiscTrainOptions();
};

namespace MiscTrainOptionsMenuVars
{
	struct Vars {
		bool trainkeyboard = false;
	};
}