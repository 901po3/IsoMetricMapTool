#pragma once
#include"Object.h"

class MenuScreen : public Object
{
private:

public:
	MenuScreen();
	void dealloc();

	static MenuScreen *create()
	{
		MenuScreen *menuScreen = new MenuScreen();
		return menuScreen;
	}
	void render();
	void update(float dt) {}
};