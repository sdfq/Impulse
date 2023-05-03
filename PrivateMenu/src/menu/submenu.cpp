#include "stdafx.h"

void Submenu::MenuUpdate(bool withInput) {
	Update();
	GetRenderer()->DrawTitle(m_name.Get());
	GetSubmenuHandler()->m_currentOptionWithoutBreaks = 0;
	GetSubmenuHandler()->m_totalOptionsWithoutBreaks = 0;
	GetSubmenuHandler()->m_totalOptions = 0;
	vector<shared_ptr<Option>> tempOptions;
	tempOptions.reserve(m_options.size());
	if (m_options.size() > 0) {
		int relativeOptionPosition = 0, visibilityOffset = 0;
		for (int i = 0; i < m_options.size(); i++) {
			if (m_options.at(i)->isVisible()) {
				tempOptions.push_back(m_options.at(i));
				visibilityOffset++;
				GetSubmenuHandler()->m_totalOptions++;
				if (!m_options.at(i)->isBreak()) {
					if (visibilityOffset <= GetMenu()->m_currentOption) GetSubmenuHandler()->m_currentOptionWithoutBreaks++;
					GetSubmenuHandler()->m_totalOptionsWithoutBreaks++;
				}
			}
		}
		for (int i = GetMenu()->m_scrollOffset; i < GetMenu()->m_scrollOffset + GetMenu()->m_maxOptions; i++) {
			if (i >= 0 && i < tempOptions.size()) {
				if (relativeOptionPosition >= GetMenu()->m_maxOptions) break;
				tempOptions.at(i).get()->Render(relativeOptionPosition);
				if (GetMenu()->IsOpen() && withInput) tempOptions.at(i).get()->Input(relativeOptionPosition);
				if (relativeOptionPosition == GetMenu()->m_currentOption - GetMenu()->m_scrollOffset) {
					Option* option = tempOptions.at(i).get();
					GetRenderer()->RenderTooltip(option->getTooltip().Get(), option->m_canBeSaved, option->m_hasHotkey, option->m_hotkey);
					if (GetMenu()->IsOpen()) option->RenderSelected(relativeOptionPosition);
				} relativeOptionPosition++;
			}
		}
	}
}

//void Submenu::MenuUpdate(bool withInput) {
//	Update();
//	GetRenderer()->DrawTitle(m_name.Get());
//	GetSubmenuHandler()->m_currentOptionWithoutBreaks = 0;
//	GetSubmenuHandler()->m_totalOptionsWithoutBreaks = 0;
//	GetSubmenuHandler()->m_totalOptions = 0;
//	vector<Option*> tempOptions;
//	tempOptions.reserve(m_options.size());
//	if (m_options.size() > 0) {
//		int relativeOptionPosition = 0, visibilityOffset = 0;
//		for (int i = 0; i < m_options.size(); i++) {
//			if (m_options.at(i)->isVisible()) {
//				tempOptions.push_back(m_options.at(i).get());
//				visibilityOffset++;
//				GetSubmenuHandler()->m_totalOptions++;
//				if (!m_options.at(i)->isBreak()) {
//					if (visibilityOffset <= GetMenu()->m_currentOption) GetSubmenuHandler()->m_currentOptionWithoutBreaks++;
//					GetSubmenuHandler()->m_totalOptionsWithoutBreaks++;
//				}
//			}
//		}
//		for (int i = GetMenu()->m_scrollOffset; i < GetMenu()->m_scrollOffset + GetMenu()->m_maxOptions; i++) {
//			if (i >= 0 && i < tempOptions.size()) {
//				if (relativeOptionPosition >= GetMenu()->m_maxOptions) break;
//				if (tempOptions.at(i) == nullptr) break;
//				tempOptions.at(i)->Render(relativeOptionPosition);
//				if (GetMenu()->IsOpen() && withInput) tempOptions.at(i)->Input(relativeOptionPosition);
//				if (relativeOptionPosition == GetMenu()->m_currentOption - GetMenu()->m_scrollOffset) {
//					Option* option = tempOptions.at(i);
//					GetRenderer()->RenderTooltip(option->getTooltip().Get(), option->m_canBeSaved, option->m_hasHotkey, option->m_hotkey);
//					if (GetMenu()->IsOpen()) option->RenderSelected(relativeOptionPosition);
//				} relativeOptionPosition++;
//			}
//		}
//	}
//}

//In submenu.cpp replace these lines with the following:
//9: vector<Option*> tempOptions;
//15: tempOptions.push_back(m_options.at(i).get());
//
//remove the .get() at lines 27 and 30

Submenu::~Submenu() {}
void Submenu::Init() {}
void Submenu::UpdateOnce() {}
void Submenu::Update() {}
void Submenu::FeatureUpdate() {}
