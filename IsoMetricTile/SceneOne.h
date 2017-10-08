#pragma once
#include"Scene.h"

class SceneOne : public Scene
{
public:
	static Scene* SetActive();
	virtual void init();

	static void CheckSelection(WPARAM _wParam, LPARAM _lParam);
};