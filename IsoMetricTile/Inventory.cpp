#include"Invetory.h"
#include"GameMananger.h"

Inventory::Inventory()
{
	Object::Object();
	m_HResource = GameManager::call()->getBmp(IDB_INVENTORY);
	NumberTag = 1000000;
}

void Inventory::dealloc()
{
	if(m_HResource != NULL)
		DeleteObject(m_HResource);
	m_HResource = NULL;
}

void Inventory::render()
{
	if(!GameManager::call()->BM.pButtonList[TILE_INVENTORY]->GetPressed()) 
		return;
	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;

	SelectObject(m, m_HResource);

	CGPoint scroll = GameManager::call()->ScrollOffSet;
	BitBlt(b, 0, INVENTORY_CORD_Y, 450, 800, m, 0, 0, SRCCOPY);
}


void Inventory::update(float dt)
{

}

