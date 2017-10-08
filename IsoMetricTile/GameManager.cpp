#include"GameMananger.h"

void GameManager::ReplaceScene(Scene * curScene)
{
	if(pNowRunningScene != NULL)
	{
		pNowRunningScene->dealloc();
		delete pNowRunningScene;
		pNowRunningScene = NULL;
	}
	pNowRunningScene = curScene;
}

void GameManager::Scroll(float dt)
{
	if( GetAsyncKeyState(VK_LEFT))
	{
		ScrollOffSet.x-=450 *dt;
	}
	if( GetAsyncKeyState(VK_RIGHT))
	{
		ScrollOffSet.x+=450 *dt;
	}
	if( GetAsyncKeyState(VK_UP))
	{
		ScrollOffSet.y-=450 *dt;
	}
	if( GetAsyncKeyState(VK_DOWN))
	{
		ScrollOffSet.y+=450 *dt;
	}
}

void GameManager::ChangeTile(WPARAM _wParam, LPARAM _lParam)
{
	if(BM.pButtonList[TILE_INVENTORY] != NULL)
		if(!BM.pButtonList[TILE_INVENTORY]->GetPressed()) return;

	CGPoint mouse;
	mouse.x = LOWORD(_lParam);
	mouse.y = HIWORD(_lParam);

	int xpos = 10; //from inventory screen;
	int ypos = 53 + INVENTORY_CORD_Y;

	for(int i = 0; i < INVENTOTY_COLUMNS * INVENTORY_ROWS; i++)
	{
		if( i != 0 && i % INVENTOTY_COLUMNS == 0)
		{
			ypos += (SLOT_SIZE_Y + 5);
			xpos = 10;
		}

		if(( mouse.x > xpos && mouse. x < xpos+SLOT_SIZE_X) 
			&& (mouse.y > ypos && mouse.y < ypos + SLOT_SIZE_Y))
		{
			SelectedTile = TM.TileStructList[i];
			break;
		}
		xpos += (SLOT_SIZE_X + 7);
	}

	ChangeHeight(_wParam, _lParam);
}

void GameManager::ChangeHeight(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint mouse;
	mouse.x = LOWORD(_lParam);
	mouse.y = HIWORD(_lParam);
	if(mouse.x > 11 && mouse.x < 49 
		&& mouse.y > 733+INVENTORY_CORD_Y && mouse.y < 773+INVENTORY_CORD_Y)
	{
		CurrentDrawingZPos = 0;
		return;
	}
	if(mouse.x > 61 && mouse.x < 99 
		&& mouse.y+INVENTORY_CORD_Y > 733 && mouse.y < 773+INVENTORY_CORD_Y)
	{
		CurrentDrawingZPos = 1;
		return;
	}
	if(mouse.x > 111 && mouse.x < 149
		&& mouse.y > 733+INVENTORY_CORD_Y && mouse.y <773+INVENTORY_CORD_Y)
	{
		CurrentDrawingZPos = 2;
		return;
	}
}

bool GameManager::OverlappedManagement(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint mouse;
	mouse.x = LOWORD(_lParam);
	mouse.y = HIWORD(_lParam);

	if(BM.pButtonList[TILE_INVENTORY] != NULL)
	{
		if(BM.pButtonList[TILE_INVENTORY]->GetPressed())
			if(mouse.x <= INVENTORY_WIDTH + 55 && mouse.y <= INVENTORY_HEIGHT+85)
				return true;
	}
	return false;
}

void GameManager::IsButtonPressed(WPARAM _wParam, LPARAM _lParam)
{
	Button *pButton = NULL;
	pButton = GameManager::call()->BM.CheckButtonPressed(_wParam, _lParam);

	if(pButton != NULL)
	{
		if(pButton == BM.pButtonList[MENU])
		{
			SceneMenu::SetActive();
			return;
		}
		if(pButton == BM.pButtonList[SAVE])
		{ 
			SLS->SetSaveOrLoadPos(SavePos);
			SLS->SetOriginPos(MakePoint(MakeMapOriginPosX, MakeMapOriginPosY));
			LoadSlotPressed = false;
			SaveSlotPressed = true;
			return;
		}
		if(pButton == BM.pButtonList[LOAD])
		{
			SLS->SetSaveOrLoadPos(LoadPos);
			SLS->SetOriginPos(MakePoint(MakeMapOriginPosX, MakeMapOriginPosY));
			LoadSlotPressed = true;
			SaveSlotPressed = false;
			return;
		}
		if(pButton->GetPressed())
		{
			pButton->SetPressed(false);
			return;
		}
		pButton->SetPressed(true);
	}
}

void GameManager::MakeMapSaveLoadSlot(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint mouse;
	mouse.x = LOWORD(_lParam);
	mouse.y = HIWORD(_lParam);

	if(mouse.x > 345 + MakeMapOriginPosX && mouse.x < 383 + MakeMapOriginPosX 
		&& mouse.y > MakeMapOriginPosY && mouse.y < MakeMapOriginPosY + 38)
	{
		LoadSlotPressed = false;
		SaveSlotPressed = false;
		return;
	}

	if(LoadSlotPressed)
	{
		LoadSlotPressedFunc(mouse);
		return;
	}
	if(SaveSlotPressed)
	{
		SaveSlotPressedFunc(mouse);
		return;
	}

}

void GameManager::LoadSlotPressedFunc(CGPoint mouse)
{
	if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
		mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
		mouse.y > 265 + 2   && mouse.y < 265 - 2 + SlotHeight )
	{
		LoadSlotPressed = false;
		GameManager::call()->CurScene = SCENE_SAVED;
		SceneSaved::SetActive(1);
		return;
	}
	if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
		mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
		mouse.y > 379  && mouse.y < 379 -2 + SlotHeight )
	{
		LoadSlotPressed = false;
		GameManager::call()->CurScene = SCENE_SAVED;
		SceneSaved::SetActive(2);
		return;
	}
	if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
		mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
		mouse.y > 486 + 2   && mouse.y < 486 - 2 + SlotHeight )
	{
		LoadSlotPressed = false;
		GameManager::call()->CurScene = SCENE_SAVED;
		SceneSaved::SetActive(3);
		return;
	}
}

void GameManager::SaveSlotPressedFunc(CGPoint mouse)
{
	if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
		mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
		mouse.y > 265 + 2   && mouse.y < 265 - 2 + SlotHeight )
	{
		SaveSlotPressed = false;
		SLS->SetSaveSlotOne(true);
		TM.SaveTileSet();
		return;
	}
	if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
		mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
		mouse.y > 379  && mouse.y < 379 -2 + SlotHeight )
	{
		SaveSlotPressed = false;
		SLS->SetSaveSlotTwo(true);
		TM.SaveTileSet();
		return;
	}
	if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
		mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
		mouse.y > 486 + 2   && mouse.y < 486 - 2 + SlotHeight )
	{
		SaveSlotPressed = false;
		SLS->SetSaveSlotThree(true);
		TM.SaveTileSet();
		return;
	}
}

void GameManager::CurrentChoosenSlot(WPARAM _wParam, LPARAM _lParam)
{
	if(SaveSlotPressed || LoadSlotPressed)
	{
		CGPoint mouse;
		mouse.x = LOWORD(_lParam);
		mouse.y = HIWORD(_lParam);

		if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
			mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
			mouse.y > 265 + 2   && mouse.y < 265 - 2 + SlotHeight )
		{
			SLS->MarkChoosenSlot(FirstSlotChoosen);
		}
		else if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
			mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
			mouse.y > 379  && mouse.y < 379 -2 + SlotHeight )
		{
			SLS->MarkChoosenSlot(SecondSlotChoosen);
		}
		else if(mouse.x > MakeMapOriginPosX + FirstSlotPosX + 3 && 
			mouse.x < MakeMapOriginPosX + FirstSlotPosX - 3 + SlotWidth &&
			mouse.y > 486 + 2   && mouse.y < 486 - 2 + SlotHeight )
		{
			SLS->MarkChoosenSlot(ThirdSlotChoosen);
		}
		else
			SLS->MarkChoosenSlot(None);
	}
}

void GameManager::MouseAdd(WPARAM _wParam, LPARAM _lParam)
{
	if(OverlappedManagement(_wParam, _lParam) || LoadSlotPressed || SaveSlotPressed)
		return;

	for(int i = 0; i <LENTH; i++)
	{
		if(TM.TileRenderList[i] != NULL) continue;
		TM.TileRenderList[i] = TM.CompareMousePosAndTileToAdd(_wParam, _lParam);


		if(TM.TileRenderList[i] != NULL)
		{
			TM.TileRenderList[i]->SetMade(true);
			TM.TileRenderList[i]->SetActive(true);
			TM.TileRenderList[i]->ChangeTile(SelectedTile);
			pNowRunningScene->addObject(TM.TileRenderList[i]);
			break;
		}

	}
}

void GameManager::MouseErase(WPARAM _wParam, LPARAM _lParam)
{
	if(OverlappedManagement(_wParam, _lParam) || LoadSlotPressed || SaveSlotPressed)
		return;

	Tile *pt = TM.CompareMousePosAndTileToErase(_wParam, _lParam);
	if(pt != NULL)
	{
		if(pt->GetActive())
			pt->SetActive(false);

		for(int i = 0; i < LENTH; i++)
		{
			if(TM.TileRenderList[i] != NULL)
				if(TM.TileRenderList[i]->GetActive() == false)
				{
					TM.TileRenderList[i]->SetMade(false);
					TM.TileRenderList[i] = NULL;
				}
		}

		pNowRunningScene->CheckFalse();
	}
}

void GameManager::MouseRButtonDown(WPARAM _wParam, LPARAM _lParam)
{
	bNowErase = true;
	MouseErase(_wParam, _lParam);
}


void GameManager::MouseLButtonDown(WPARAM _wParam, LPARAM _lParam)
{
	bNowDraw = true;
	MouseAdd(_wParam, _lParam);
}

void GameManager::MouseMove(WPARAM _wParam, LPARAM _lParam)
{		
	if(bNowErase)
	{
		MouseErase(_wParam, _lParam);
	}
	else if(bNowDraw)
	{
		MouseAdd(_wParam, _lParam);
	}
}

void GameManager::CreateBackBuf(HWND _hWnd)
{
	hWnd			= _hWnd;
	hInstance	= (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
	HDC hDC		= GetDC(_hWnd);									
	memDC		= CreateCompatibleDC( hDC );					
	backDC		= CreateCompatibleDC(hDC);
	hBackBuf		= CreateCompatibleBitmap(hDC, 1850, 1300);	
	SelectObject( backDC, hBackBuf );					
	ReleaseDC(hWnd, hDC);
}

HBITMAP GameManager::getBmp(int _index)
{
	return LoadBitmap(hInstance, MAKEINTRESOURCE(_index));
}

void GameManager::dealloc()
{
	DeleteObject( backDC);
	DeleteDC( memDC );
	TM.dealloc();
	BM.dealloc();
}
