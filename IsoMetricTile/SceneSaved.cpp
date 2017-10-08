#include"SceneSaved.h"
#include"BKG.h"
#include"Invetory.h"
#include"TileManager.h"
#include"GameMananger.h"

Scene* SceneSaved::SetActive(int LoadFileNum)
{
	Scene *One = new SceneSaved;
	One->init(LoadFileNum);
	return One;
}

void SceneSaved::init(int LoadFileNum)
{
	GameManager::call()->initSaveScene();
	GameManager::call()->ReplaceScene(this);
	GameManager::call()->SM.play(SND_BGM);
	Scene::init();

	addObject(BKG::create());	
	GameManager::call()->BM.SetScene();

	if(GameManager::call()->SLS == NULL)
		GameManager::call()->SLS = SaveLoadSlot::create();
	addObject(GameManager::call()->SLS);

	addObject(Inventory::create());

	switch(LoadFileNum)
	{
	case 1:
		GameManager::call()->SLS->SetLoadSlotOne(true);
		break;
	case 2:
		GameManager::call()->SLS->SetLoadSlotTwo(true);
		break;
	case 3:
		GameManager::call()->SLS->SetLoadSlotThree(true);
		break;
	}

	GameManager::call()->TM.LoadTileSet();
}

void SceneSaved::CheckSelection(WPARAM _wParam, LPARAM _lParam)
{
	GameManager::call()->MouseLButtonDown(_wParam, _lParam);
	GameManager::call()->IsButtonPressed(_wParam, _lParam);
	GameManager::call()->ChangeTile(_wParam, _lParam);
	GameManager::call()->MakeMapSaveLoadSlot(_wParam, _lParam);
}