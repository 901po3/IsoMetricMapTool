#pragma once
#include"Scene.h"

#define MakeMapButtonPosX			24
#define MakeMapButtonPosY			66

#define LodButtonPosX				24
#define LoadButtonPosY				149

#define MENU_BUTTON_WITDH			232
#define MENU_BUTTON_HEIGHT			60

class SceneMenu : public Scene
{
public:
	static Scene* SetActive();
	virtual void init();

	static void CheckSelection(WPARAM _wParam, LPARAM _lParam);
	static void MakeMapSlot(CGPoint pos);
	static void LoadSlot(CGPoint pos);
	static void CurrentChoosenLoadSlot(WPARAM _wParam, LPARAM _lParam);
};