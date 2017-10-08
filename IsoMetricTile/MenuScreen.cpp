#include"MenuScreen.h"
#include"GameMananger.h"

MenuScreen::MenuScreen()
{
	Object::Object();
	m_HResource = GameManager::call()->getBmp(IDB_MENU_SCREEN);
	IsoPos = MakePoint(0.f, 0.f);
	NumberTag = -2;
}

void MenuScreen::dealloc()
{
	if(m_HResource != NULL)
		DeleteObject(m_HResource);
	m_HResource = NULL;
}

void MenuScreen::render()
{
	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;

	SelectObject(m, m_HResource);

	BitBlt(b, 0, 0, 1950, 1400, m, 0, 0, SRCCOPY);
}
