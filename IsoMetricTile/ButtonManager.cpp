#include"ButtonManager.h"
#include"GameMananger.h"

ButtonManager::ButtonManager()
{
	memset(pButtonList, NULL, sizeof(pButtonList));

	TileStructList[TILE_INVENTORY].typeName		= TILE_INVENTORY;
	TileStructList[TILE_INVENTORY].ButtonSize	= MakePoint(106.f, 31.f);
	TileStructList[TILE_INVENTORY].ButtonSrcPos	= MakePoint(0.f, 0.f);

	TileStructList[SAVE].typeName				= SAVE;
	TileStructList[SAVE].ButtonSize				= MakePoint(106.f, 32.f);
	TileStructList[SAVE].ButtonSrcPos			= MakePoint(0.f, 46.f);

	TileStructList[LOAD].typeName				= LOAD;
	TileStructList[LOAD].ButtonSize				= MakePoint(106.f, 32.f);
	TileStructList[LOAD].ButtonSrcPos			= MakePoint(0.f, 92.f);

	TileStructList[MENU].typeName				= TILE_INVENTORY;
	TileStructList[MENU].ButtonSize				= MakePoint(106.f, 31.f);
	TileStructList[MENU].ButtonSrcPos			= MakePoint(0.f, 140.f);

	//106*3 = 318;
}

void ButtonManager::dealloc()
{
	for(int i=0; i<MAX_BUTTON; i++)
	{
		if(pButtonList[i] != NULL)
			delete pButtonList[i];
		pButtonList[i] = NULL;
	}

	if(m_phResource != NULL)
	{
		DeleteObject(m_phResource);
		m_phResource = NULL;
	}
}


void ButtonManager::SetScene()
{
	ButtonManager();
	if(m_phResource == NULL)
		m_phResource	= GameManager::call()->getBmp(IDB_BUTTON);
	Button *pbutton = NULL;

	for(int i = 0; i < MAX_BUTTON; i++)
	{
		pButtonList[i] = Button::create();
		pButtonList[i]->SetActive(true);
		pButtonList[i]->SetPosition(MakePoint(TileStructList[i].ButtonSize.x * i, 0.f));
		GameManager::call()->pNowRunningScene->addObject(pButtonList[i]);
	}

	pButtonList[TILE_INVENTORY]->SetCurButton(TileStructList[TILE_INVENTORY]);
	pButtonList[SAVE]->SetCurButton(TileStructList[SAVE]);
	pButtonList[LOAD]->SetCurButton(TileStructList[LOAD]);
	pButtonList[MENU]->SetCurButton(TileStructList[MENU]);
}

Button *ButtonManager::CheckButtonPressed(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint mouse;
	mouse.x = LOWORD(_lParam);
	mouse.y = HIWORD(_lParam);

	if( (mouse.x >= 0 && mouse.x <= 424) && (mouse.y >= 0 && mouse.y <= 32) )
	{
		if(mouse.x < 104)
		{
			return pButtonList[TILE_INVENTORY];
		}
		else if( mouse.x > 108 && mouse.x < 210)
		{
			return pButtonList[SAVE];
		}
		else if( mouse.x > 212 && mouse.x < 316)
		{
			return pButtonList[LOAD];
		}
		else if( mouse.x > 318 && mouse.x < 422)
		{
			return pButtonList[MENU];
		}
	}

	return NULL;
}