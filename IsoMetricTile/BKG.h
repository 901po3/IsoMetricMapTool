#pragma once
#include"Object.h"

class BKG : public Object
{
private:

public:
	BKG();
	virtual void dealloc();

	static BKG *create()
	{
		BKG *bkg = new BKG();
		return bkg;
	}
	void render();
	void update(float dt) {}
};