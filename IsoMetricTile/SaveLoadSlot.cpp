#include"SaveLoadSlot.h"
#include"GameMananger.h"

SaveLoadSlot::SaveLoadSlot()
{
	Object::Object();
	m_HResource		= GameManager::call()->getBmp(IDB_SAVE_SLOT);
	NumberTag		= 1000001;
	OriginPos		= MakePoint( MenuOriginPosX, MenuOriginPosY);
	SaveOrLoadPos		= 397;
	CurrentChoosenSlotPos = 0;
	SaveSlotOne		= false;
	SaveSlotTwo		= false;
	SaveSlotThree		= false;
	LoadSlotOne		= false;
	LoadSlotTwo		= false;
	LoadSlotThree		= false;
}

void SaveLoadSlot::dealloc()
{
	if(m_HResource != NULL)
		DeleteObject(m_HResource);
	m_HResource = NULL;
}

void SaveLoadSlot::render()
{
	if(SavePos == SaveOrLoadPos)
		if(!GameManager::call()->SaveSlotPressed) return;
	if(LoadPos == SaveOrLoadPos)
		if(!GameManager::call()->LoadSlotPressed) return;

	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;

	SelectObject(m, m_HResource);

	if(GameManager::call()->LoadSlotPressed)

	CGPoint scroll = GameManager::call()->ScrollOffSet;
	BitBlt(b, OriginPos.x, OriginPos.y, SaveScreenWidth, SaveScreenHeight, m,
		CurrentChoosenSlotPos, SaveOrLoadPos, SRCCOPY);
}


