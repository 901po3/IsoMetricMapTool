#include"BKG.h"
#include"GameMananger.h"

BKG::BKG()
{
	Object::Object();
	m_HResource = GameManager::call()->getBmp(IDB_BKG);
	NumberTag = -20;
	IsoPos = MakePoint(0.f, 0.f);
}

void BKG::dealloc()
{
	if(m_HResource != NULL)
		DeleteObject(m_HResource);
	m_HResource = NULL;
}

void BKG::render()
{
	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;

	SelectObject(m, m_HResource);

	CGPoint scroll = GameManager::call()->ScrollOffSet;
	BitBlt(b, 0, 0, 1950, 1400, m, 0, 0, SRCCOPY);
}
