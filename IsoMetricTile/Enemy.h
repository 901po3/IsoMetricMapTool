#pragma once
#include"Object.h"



class Enemy : public Object
{
private:
	int			m_iCurHp;
	int			m_iMaxHp;
	int			m_iDmg;
	int			m_iMoveSpeed;
	int			m_iStadingHeight;
public:
	Enemy() {}
	void dealloc() {}
};