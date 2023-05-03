#pragma once
#include "menu/submenu.h"

class ChatCommandMenu : public Submenu {
public:
	static ChatCommandMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	ChatCommandMenu() : Submenu() {}
	~ChatCommandMenu();
};

namespace ChatCommandMenuVars
{
	struct Vars {

	};

	void HandleCommand(int id, string message);
}