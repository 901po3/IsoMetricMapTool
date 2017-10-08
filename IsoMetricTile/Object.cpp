#include"Object.h"

Object::Object()
{
	m_Position.x		= 0.f;
	m_Position.y		= 0.f;
	m_SrcSize.x		= 0.f;
	m_SrcSize.y		= 0.f;
	m_OffSet.x		= 0.f;
	m_OffSet.y		= 0.f;
	m_Active			= true;
	m_HResource		= NULL;
	IsoPos			= MakePoint(0.f, 0.f);

	TileHeight			= 0;
	TileXth				= 0;
	TileYth				= 0;
	NumberTag			= 0;
	Made					= false;
}
