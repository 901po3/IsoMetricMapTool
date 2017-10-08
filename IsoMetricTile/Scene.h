#pragma once
#include"Object.h"

#define MAX_OBJECT		3043

class Scene
{
	Object*		m_pObjectList[MAX_OBJECT];
	Rect			rect;
public:
	virtual void init();
	virtual void init(int LoadFileNum) {}
	virtual void run(float dt);
	virtual void addObject(Object * obj);
	virtual void dealloc();
	void CheckFalse();
	bool PointExitCheck(CGPoint pos);
	void	 Order();
};