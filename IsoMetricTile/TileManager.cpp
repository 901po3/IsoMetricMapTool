#include"TileManager.h"
#include"GameMananger.h"

TileManager::TileManager()
{
	memset(TileList, NULL, sizeof(TileList));
	memset(TileRenderList, NULL, sizeof(TileRenderList));
	m_phResource = NULL;

	FILE *fp = fopen("TILE_INFORMATION.txt", "r+");
	if(fp == NULL) return;
	int tileType = 0;
	CGPoint tilePos;
	for(int i=0; i<TILEKINDS; i++)
	{
		if(feof(fp)) break;

		fscanf(fp, "%d", &tileType);
		TileStructList[i].typeName = (TileType)tileType;
		fscanf(fp, "%f", &tilePos.x);
		fscanf(fp, "%f", &tilePos.y);
		TileStructList[i].TileSrcPos = tilePos;

		TileStructList[i].TileSize = MakePoint(TILE_WITDH, TILE_HEIGHT);
	}
	fclose(fp);
}

void TileManager::dealloc()
{
	for(int i = 0; i < Z; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			for(int k = 0; k < COLUMNS; k++)
			{ 
				if(TileList[i][j][k] != NULL)
				{
					TileList[i][j][k]->dealloc();
					delete TileList[i][j][k];
					TileList[i][j][k] = NULL;
				}
			}
		}
	}
	if(m_phResource != NULL)
	{
		DeleteObject(m_phResource);
		m_phResource = NULL;
	}
}

void TileManager::SetScene()
{
	TileManager();
	if(m_phResource == NULL)
		m_phResource	= GameManager::call()->getBmp(IDB_TILE);
	GameManager::call()->CheckTilePosSetting = true;
	
	for(int i = 0; i < Z; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			for(int k = 0; k < COLUMNS; k++)
			{
				TileList[i][j][k] = Tile::create();
				if(i == 0) TileList[i][j][k]->SetActive(false);
				else TileList[i][j][k]->SetActive(false);
				TileList[i][j][k]->ChangeTile(TileStructList[ROW_ONE_1]);
				TileList[i][j][k]->render(i, k, j);
			}
		}
	}
}

void TileManager::SaveTileSet()
{
	bool fpOpen  = false;
	FILE *fp;
	if(GameManager::call()->SLS->GetSaveSlotOne())
	{
		fp = fopen("SaveSlotOne.txt", "w+");
		GameManager::call()->SLS->SetSaveSlotOne(false);
		fpOpen = true;
	}
	else if(GameManager::call()->SLS->GetSaveSlotTwo())
	{
		fp = fopen("SaveSlotTwo.txt", "w+");
		GameManager::call()->SLS->SetSaveSlotTwo(false);
		fpOpen = true;
	}
	else if(GameManager::call()->SLS->GetSaveSlotThree())
	{
		fp = fopen("SaveSlotThree.txt", "w+");
		GameManager::call()->SLS->SetSaveSlotThree(false);
		fpOpen = true;
	}

	if(fpOpen)
	{
		for(int i = 0; i < Z; i++)
		{
			for(int j = 0; j < ROWS; j++)
			{
				for(int k = 0; k < COLUMNS; k++)
				{
					if(!TileList[i][j][k]->GetActive()) continue;
					fprintf(fp, "%d\n", TileList[i][j][k]->GetNumberTag());
					fprintf(fp, "%d\n", TileList[i][j][k]->GetCurTile());
					fprintf(fp, "%d\n%d\n%d\n",
						TileList[i][j][k]->GetTileHeight(), TileList[i][j][k]->GetTileXth(),
						TileList[i][j][k]->GetTileYth());
				}
			}
		}
		fclose(fp);
	}
	GameManager::call()->SaveSlotPressed = false;
}

void TileManager::LoadTileSet()
{
	SetScene();

	FILE *fp;
	bool fpOpen = false;
	if(GameManager::call()->SLS->GetLoadSlotOne())
	{
		fp = fopen("SaveSlotOne.txt", "r+");
		GameManager::call()->SLS->SetLoadSlotOne(false);
		fpOpen = true;
	}
	else if(GameManager::call()->SLS->GetLoadSlotTwo())
	{
		fp = fopen("SaveSlotTwo.txt", "r+");
		GameManager::call()->SLS->SetLoadSlotTwo(false);
		fpOpen = true;
	}
	else if(GameManager::call()->SLS->GetLoadSlotThree())
	{
		fp = fopen("SaveSlotThree.txt", "r+");
		GameManager::call()->SLS->SetLoadSlotThree(false);
		fpOpen = true;
	}

	if(fpOpen)
	{
		if(fp == NULL)
		{
			GameManager::call()->LoadSlotPressed = false;
			return; 
		}
		int tagNum;
		TileType t;
		int z, x, y;

		for(int i=0; i<LENTH; i++)
		{
			if(feof(fp)) break;
			fscanf(fp, "%d", &tagNum);
			fscanf(fp, "%d", &t);
			fscanf(fp, "%d%d%d", &z,&x,&y);
			TileList[z][y][x]->SetNumberTag(tagNum);
			TileList[z][y][x]->SetActive(true);
			TileList[z][y][x]->SetMade(true);
			TileList[z][y][x]->ChangeTile(TileStructList[t]);

			TileRenderList[i] = TileList[z][y][x];
			GameManager::call()->pNowRunningScene->addObject(TileRenderList[i]);

		}
		fclose(fp);
	}
	GameManager::call()->LoadSlotPressed = false;
}


CGPoint TileManager::MousePosToGridPos(CGPoint mouse, WPARAM _wParam, LPARAM _lParam)
{
	CGPoint scroll = GameManager::call()->ScrollOffSet;

	mouse.x = LOWORD(_lParam) - (TILE_WITDH *9 + scroll.x) - 55;	
	mouse.y = HIWORD(_lParam) - (TILE_HEIGHT + scroll.y) + 30;
	mouse.y += ((GameManager::call()->CurrentDrawingZPos-1) * (TILE_HEIGHT)/2)
		- (TILE_HEIGHT);

	return mouse;
}

Tile * TileManager::CompareMousePosAndTileToAdd(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint MousePos = MakePoint(0, 0);

	MousePos = MousePosToGridPos(MousePos, _wParam, _lParam);

	CGPoint Mouse_grid;
	Mouse_grid.x = (2 * MousePos.y + MousePos.x) / 2;
	Mouse_grid.y = (2 * MousePos.y - MousePos.x) / 2;

	int X = (int)( Mouse_grid.x / TILE_WITDH *2 );
	int Y = (int)( Mouse_grid.y / TILE_HEIGHT *2 );

	int _zth = GameManager::call()->CurrentDrawingZPos;

	//오브젝트형 타일 관

	if(X  >= 0 && X < COLUMNS)
	{
		if(Y >=0 && Y < ROWS)
		{
			if(GameManager::call()->SelectedTile.typeName > ROW_SEVEN_4)
			{
				_zth += 1;

				if(GameManager::call()->TM.TileList[_zth][Y][X]->GetTileHeight() >= Z-1)
					return NULL;

				if( !GameManager::call()->TM.IsSomethingOnBottom(TileList[_zth][Y][X]->GetTileHeight(),
					TileList[_zth][Y][X]->GetTileXth(), TileList[_zth][Y][X]->GetTileYth()) )
				{
					return NULL;
				}
			}
			if(TileList[_zth][Y][X]->GetMade())
				return NULL;

			return TileList[_zth][Y][X];
		}
	}
	return NULL;
}


Tile * TileManager::CompareMousePosAndTileToErase(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint MousePos = MakePoint(0, 0);

	MousePos = MousePosToGridPos(MousePos, _wParam, _lParam);

	CGPoint Mouse_grid;
	Mouse_grid.x = (2 * MousePos.y + MousePos.x) / 2;
	Mouse_grid.y = (2 * MousePos.y - MousePos.x) / 2;

	int X = (int)( Mouse_grid.x / TILE_WITDH *2 );
	int Y = (int)( Mouse_grid.y / TILE_HEIGHT *2 );


	int _zth = GameManager::call()->CurrentDrawingZPos;

	if(X  >= 0 && X < COLUMNS)
	{
		if(Y >=0 && Y < ROWS)
		{
			if(TileList[_zth][Y][X] != NULL)
				if( GameManager::call()->TM.IsSomethingOnTop(TileList[_zth][Y][X]->GetTileHeight(),
					TileList[_zth][Y][X]->GetTileXth(), TileList[_zth][Y][X]->GetTileYth()) )
				{
					GameManager::call()->CurrentDrawingZPos+=1;
					if(GameManager::call()->SelectedTile.typeName > ROW_SEVEN_4)
					{
						GameManager::call()->CurrentDrawingZPos-=1;
						return TileList[_zth+1][Y][X];
					}
					GameManager::call()->CurrentDrawingZPos-=1;
				}

				return TileList[_zth][Y][X];
		}
	}
	return NULL;
}


void TileManager::SetIsSomethingOnTop(int _zth, int _xth, int _yth)
{

	if(TileList[_zth+1][_yth][_xth]->GetActive())
	{
		TileList[_zth][_yth][_xth]->SetWallOnTop(true);
	}
	else if(!TileList[_zth+1][_yth][_xth]->GetActive())
	{
		TileList[_zth][_yth][_xth]->SetWallOnTop(false);
	}	
}

bool TileManager::IsSomethingOnBottom(int _zth, int _xth, int _yth)
{
	if(TileList[_zth-1][_yth][_xth]->GetActive())
	{
		return true;
	}
	else if(!TileList[_zth-1][_yth][_xth]->GetActive())
	{
		return false;
	}	
	return false;
}

bool TileManager::IsSomethingOnTop(int _zth, int _xth, int _yth)
{
	if(TileList[_zth+1][_yth][_xth]->GetActive())
	{
		return true;
	}
	else if(!TileList[_zth+1][_yth][_xth]->GetActive())
	{
		return false;
	}	
	return false;
}
