#include"SceneOne.h"
#include"BKG.h"
#include"Invetory.h"
#include"TileManager.h"
#include"GameMananger.h"

Scene* SceneOne::SetActive()
{
	Scene *One = new SceneOne;
	One->init();
	return One;
}

void SceneOne::init()
{
	GameManager::call()->ReplaceScene(this);
	GameManager::call()->SM.play(SND_BGM);
	Scene::init();

	addObject(BKG::create());	
	GameManager::call()->BM.SetScene();

	if(GameManager::call()->SLS == NULL)
		GameManager::call()->SLS = SaveLoadSlot::create();
	addObject(GameManager::call()->SLS);

	addObject(Inventory::create());

	GameManager::call()->TM.SetScene();
}

void SceneOne::CheckSelection(WPARAM _wParam, LPARAM _lParam)
{
	GameManager::call()->MouseLButtonDown(_wParam, _lParam);
	GameManager::call()->IsButtonPressed(_wParam, _lParam);
	GameManager::call()->ChangeTile(_wParam, _lParam);
	GameManager::call()->MakeMapSaveLoadSlot(_wParam, _lParam);
}