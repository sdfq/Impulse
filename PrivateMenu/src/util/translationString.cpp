#include "stdafx.h"
#include "../menu/submenus/main/settings/languageMenu.h"
using namespace LanguageMenuVars;

void TranslationString::Register() {
	g_translationTable.push_back(this);
	m_hasTranslation = true;
}