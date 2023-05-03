#pragma once
#include "menu/submenu.h"

class ModelMenu : public Submenu {
public:
	static ModelMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ModelMenu() : Submenu() {}
	~ModelMenu();
};

namespace ModelMenuVars
{
	struct Vars {
		bool width;
		bool height;
		bool tickness;
		float editWidth = -1.0f;
		float editHeight = 1.0f;
		float edittickness = 1.0f;

		float editWidth2 = 203.f;
		float editHeight2 = 128.f;
		bool rainbowhair = false;
	};

	struct ModelStruct {
		String m_name;
		String m_model;
	};

	extern ModelStruct m_models[726];

	void SetModelI(Hash model);
}