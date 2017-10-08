#include"Button.h"
#include"GameMananger.h"

Button::Button()
{
	Object::Object();
	m_HResource = GameManager::call()->BM.m_phResource;
	NumberTag = 999999;
	CurButton.ButtonSize = MakePoint(0.f, 0.f);
	CurButton.ButtonSrcPos = MakePoint(0.f, 0.f);
	m_bPressed = false;
	IsoPos = MakePoint(0.f, 0.f);
}

void Button::render()
{
	CGPoint pos = GetPosition();

	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;

	SelectObject(m, m_HResource);

	CGPoint scroll = GameManager::call()->ScrollOffSet;
	BitBlt(b, pos.x, pos.y, CurButton.ButtonSize.x, CurButton.ButtonSize.y
		, m, CurButton.ButtonSrcPos.x, CurButton.ButtonSrcPos.y, SRCCOPY);
}


void Button::update(float dt)
{

}
