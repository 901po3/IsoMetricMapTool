#pragma once
#include"Tile.h"
#include"Scene.h"

#define LENTH			2400
#define TILEKINDS		54

class TileManager
{
public:
	Tile *TileList[Z][ROWS][COLUMNS];
	Tile *TileRenderList[LENTH];

	HBITMAP		m_phResource;
	TileStruct	TileStructList[TILEKINDS];
	
public:
	TileManager();
	void dealloc();

	HBITMAP	GetpResource() {return m_phResource; }

	void SetIsSomethingOnTop(int _zth, int _xth, int _yth);
	bool	IsSomethingOnBottom(int _zth, int _xth, int _yth);
	bool IsSomethingOnTop(int _zth, int _xth, int _yth);

	void SetScene();
	
	void SaveTileSet();
	void LoadTileSet();

	CGPoint MousePosToGridPos(CGPoint mouse, WPARAM _wParam, LPARAM _lParam);
	Tile * CompareMousePosAndTileToAdd(WPARAM _wParam, LPARAM _lParam);
	Tile * CompareMousePosAndTileToErase(WPARAM _wParam, LPARAM _lParam);
};