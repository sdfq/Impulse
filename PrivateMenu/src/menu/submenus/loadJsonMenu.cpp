#include "stdafx.h"
#include "loadJsonMenu.h"

using namespace LoadJsonMenuVars;

namespace LoadJsonMenuVars {
	bool m_shouldUpdate = false;
	void(*m_callback)(json& jsonOb);
	vector<string> m_files;
	String m_path;
	int m_TIMER;
}

void LoadJsonMenu::Open(Submenu* parent, String path, void(*callback)(json& jsonOb)) {
	GetSubmenuHandler()->SetSubmenu(this);
	setParentSubmenu(parent);
	m_callback = callback;
	m_path = path;
	m_TIMER = 0;
}

void LoadJsonMenu::Init() {
	setName("", false, false);
}

/*Update once when submenu is opened*/
void LoadJsonMenu::UpdateOnce() {}

/*Update while submenu is active*/

TranslationString strAddFiles("Add files to", true, true);
void LoadJsonMenu::Update() {
	Utils::DoTimedFunction(&m_TIMER, 2500, [] {m_shouldUpdate = true; });
	if (m_shouldUpdate) {
		clearOptions();
		GetConfig()->GetFilesFromDirectory(m_files, m_path, ".json");
		if (!m_files.empty()) {
			for (string& file : m_files) {
				addOption(ButtonOption(file.c_str())
					.addFunction([&] {
					char buff[MAX_PATH];
					vaBuff(buff, MAX_PATH, "%s/%s.json", m_path, file);
					ifstream i(buff);
					json jsonOb;
					i >> jsonOb;
					m_callback(jsonOb);
					i.close(); })
					.addTooltip(file.c_str()));
			}
		} else {
			addOption(ButtonOption(va("~c~%s %s", strAddFiles.Get(), m_path))
				.addTooltip(va("~c~%s %s", strAddFiles.Get(), m_path)));
		}
		m_shouldUpdate = false;
	}
}

/*Background update*/
void LoadJsonMenu::FeatureUpdate() {}

/*Singleton*/
LoadJsonMenu* _instance;
LoadJsonMenu* LoadJsonMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new LoadJsonMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
LoadJsonMenu::~LoadJsonMenu() { delete _instance; }