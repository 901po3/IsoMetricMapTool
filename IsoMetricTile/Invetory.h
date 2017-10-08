#pragma once
#include"Object.h"

class Inventory : public Object
{
public:
	Inventory();
	void dealloc();

	static Inventory *create()
	{
		Inventory *inven = new Inventory();
		return inven;
	}
	void render();
	void update(float dt);
};