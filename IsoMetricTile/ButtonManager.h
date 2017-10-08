#pragma once
#include"Button.h"

#define MAX_BUTTON		4

class ButtonManager
{
public:
	Button		*pButtonList[MAX_BUTTON];
	HBITMAP		m_phResource;
	ButtonStruct	TileStructList[MAX_BUTTON];
	
public:
	ButtonManager();
	void dealloc();

	HBITMAP	GetpResource() {return m_phResource; }
	
	Button *CheckButtonPressed(WPARAM _wParam, LPARAM _lParam);

	void SetScene();
};