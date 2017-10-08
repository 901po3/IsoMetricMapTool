#pragma once
#include"Scene.h"

class SceneSaved : public Scene
{
public:
	static Scene* SetActive(int LoadFileNum);
	virtual void init(int LoadFileNum);

	static void CheckSelection(WPARAM _wParam, LPARAM _lParam);
};