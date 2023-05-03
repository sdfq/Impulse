#pragma once
#include "menu/submenu.h"

class BodyguardMenuEditor : public Submenu {
public:
	static BodyguardMenuEditor* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	BodyguardMenuEditor() : Submenu() {}
	~BodyguardMenuEditor();
};

namespace BodyguardMenuEditorVars
{
	struct SpawnedBodyguard
	{
		TranslationString Model;
		Ped Handle;
		bool BlipBool;
		bool Ragdoll;
		bool Godmode;
		Blip Marker;
		bool Invisible;
	};
	struct Vars
	{
		std::vector<SpawnedBodyguard> SpawnedBodyguards;
	};
	extern Vars vars;
}