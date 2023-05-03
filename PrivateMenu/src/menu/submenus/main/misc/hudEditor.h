#pragma once
#include "menu/submenu.h"

class HudEditor : public Submenu {
public:
	static HudEditor* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	HudEditor() : Submenu() {}
	~HudEditor();
};

namespace HudEditorMenuVars
{
	struct Vars {
		Color m_hudColor[171];
	};
}