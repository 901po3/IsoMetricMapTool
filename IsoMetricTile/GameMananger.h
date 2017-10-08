#pragma once
#include"Header.h"
#include"TileManager.h"
#include"ButtonManager.h"
#include"SoundManager.h"
#include"BKG.h"
#include"SceneMenu.h"
#include"SceneOne.h"
#include"SceneSaved.h"
#include"SaveLoadSlot.h"

class GameManager
{
private:
	GameManager()
	{
		CurrentDrawingZPos		= 0;
		SelectedTile				= TM.TileStructList[ROW_ONE_1];
		ScrollOffSet				= MakePoint(0.f, 0.f);
		bNowErase				= false;
		bNowDraw					= false;
		CheckTilePosSetting		= false;
		SetNumberTag				= 0;
		pNowRunningScene			= NULL;
		CurScene					= SCENE_MENU;
		SaveSlotPressed			= false;
		LoadSlotPressed			= false;
		SLS						= NULL;
	}
public:
	void initSaveScene()
	{
		LoadSlotPressed		= false;
		SaveSlotPressed		= false; 
		SetNumberTag			= 0;
		SelectedTile			= TM.TileStructList[ROW_ONE_1];
		ScrollOffSet			= MakePoint(0.f, 0.f);
		SM.stop(SND_BGM);
	}
	void initMenuScene()
	{
		SetNumberTag			= 0;
		CheckTilePosSetting	= false;
		SelectedTile			= TM.TileStructList[ROW_ONE_1];
		ScrollOffSet			= MakePoint(0.f, 0.f);
		CurScene				= SCENE_MENU;
		SaveSlotPressed		= false;
		LoadSlotPressed		= false;
		SM.stop(SND_BGM);
	}
public:
	static GameManager Instance;
	static GameManager *call() {return &Instance;}
public:
	HDC				backDC, memDC;
	HBITMAP			hBackBuf;
	HINSTANCE		hInstance;
	HWND				hWnd;
	TileStruct		SelectedTile;
	int				CurrentDrawingZPos;
	TileManager		TM;
	ButtonManager		BM;
	CGPoint			ScrollOffSet;
	bool				bNowDraw;
	bool				bNowErase;
	Scene			*pNowRunningScene;
	bool				CheckTilePosSetting;
	int				SetNumberTag;
	SceneList		CurScene;
	SoundManager		SM;

	SaveLoadSlot		*SLS;
	bool				SaveSlotPressed;
	bool				LoadSlotPressed;

	//기본
	void CreateBackBuf(HWND _hWnd);
	HBITMAP getBmp(int _index);
	void ReplaceScene(Scene * curScene);
	void dealloc();

	//유틸리티 관련
	void Scroll(float dt);

	//마우스 관련
	void MouseLButtonDown(WPARAM _wParam, LPARAM _lParam);
	void MouseMove(WPARAM _wParam, LPARAM _lParam);
	void MouseLButtonUp() { bNowDraw = false;}
	void MouseRButtonDown(WPARAM _wParam, LPARAM _lParam);
	void MouseRButtonUp() { bNowErase = false;};
	void MouseAdd(WPARAM _wParam, LPARAM _lParam);
	void MouseErase(WPARAM _wParam, LPARAM _lParam);

	//겹치는 구간 관리
	bool OverlappedManagement(WPARAM _wParam, LPARAM _lParam);
	//인벤토리 관련
	void IsButtonPressed(WPARAM _wParam, LPARAM _lParam);
	void ChangeTile(WPARAM _wParam, LPARAM _lParam);
	void ChangeHeight(WPARAM _wParam, LPARAM _lParam);

	//저장 로드 슬롯 관련
	void MakeMapSaveLoadSlot(WPARAM _wParam, LPARAM _lParam);
	void LoadSlotPressedFunc(CGPoint mouse);
	void SaveSlotPressedFunc(CGPoint mouse);
	void CurrentChoosenSlot(WPARAM _wParam, LPARAM _lParam);
};