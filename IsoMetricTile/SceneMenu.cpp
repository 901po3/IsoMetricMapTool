#include"SceneMenu.h"
#include"MenuScreen.h"
#include"Invetory.h"
#include"TileManager.h"
#include"GameMananger.h"
#include"SceneOne.h"
#include"SaveLoadSlot.h"

Scene* SceneMenu::SetActive()
{
	Scene *One = new SceneMenu;
	One->init();
	return One;
}

void SceneMenu::init()
{
	GameManager::call()->initMenuScene();
	GameManager::call()->ReplaceScene(this);
	GameManager::call()->SM.play(SND_BGM2);
	Scene::init();

	addObject(MenuScreen::create());

	if(GameManager::call()->SLS == NULL)
		GameManager::call()->SLS = SaveLoadSlot::create();
	addObject(GameManager::call()->SLS);
}

void SceneMenu::CheckSelection(WPARAM _wParam, LPARAM _lParam)
{
	CGPoint mouse;
	mouse.x = LOWORD(_lParam);
	mouse.y = HIWORD(_lParam);

	MakeMapSlot(mouse);
	LoadSlot(mouse);
}

void SceneMenu::MakeMapSlot(CGPoint pos)
{
	if( ( pos.x > MakeMapButtonPosX &&
		pos.x < MakeMapButtonPosX + MENU_BUTTON_WITDH )
		&& ( pos.y > MakeMapButtonPosY && 
		pos.y < MakeMapButtonPosY + MENU_BUTTON_HEIGHT ) )
	{
		GameManager::call()->LoadSlotPressed = false;
		GameManager::call()->CurScene = SCENE_MAKEMAP;
		GameManager::call()->SM.stop(SND_BGM2);
		SceneOne::SetActive();
	}
}

void SceneMenu::LoadSlot(CGPoint pos)
{
	if( ( pos.x > MakeMapButtonPosX &&
		pos.x < MakeMapButtonPosX + MENU_BUTTON_WITDH  )
		&& ( pos.y > MakeMapButtonPosY + 80 && 
		pos.y < MakeMapButtonPosY + MENU_BUTTON_HEIGHT + 80) )
	{
		GameManager::call()->SLS->SetSaveOrLoadPos(LoadPos);
		GameManager::call()->SLS->SetOriginPos(MakePoint(MenuOriginPosX, MenuOriginPosY));
		GameManager::call()->LoadSlotPressed = true;
	}

	if(GameManager::call()->LoadSlotPressed)
	{
		if( ( pos.x > 365 && pos.x < 403   )
		&& ( pos.y > MakeMapButtonPosY + 80 && 
		pos.y < MakeMapButtonPosY + 120) )
		{
			GameManager::call()->LoadSlotPressed = false;
			return;
		}

		if(pos.x > 50 && pos.x < 50 + SlotWidth - 4 &&
			pos.y > 201 && pos.y < 201 + SlotHeight - 2)
		{
			GameManager::call()->LoadSlotPressed = false;
			GameManager::call()->CurScene = SCENE_SAVED;
			GameManager::call()->SM.stop(SND_BGM2);
			SceneSaved::SetActive(1);
			return;
		}
		if(pos.x > 50 && pos.x < 50 + SlotWidth - 4 &&
			pos.y > 314 && pos.y < 312 + SlotHeight - 2)
		{
			GameManager::call()->LoadSlotPressed = false;
			GameManager::call()->CurScene = SCENE_SAVED;
			GameManager::call()->SM.stop(SND_BGM2);
			SceneSaved::SetActive(2);
			return;
		}
		if(pos.x > 50 && pos.x < 50 + SlotWidth - 4 &&
			pos.y > 425 && pos.y < 423 + SlotHeight -2)
		{
			GameManager::call()->LoadSlotPressed = false;
			GameManager::call()->CurScene = SCENE_SAVED;
			GameManager::call()->SM.stop(SND_BGM2);
			SceneSaved::SetActive(3);
			return;
		}
	}
}

void SceneMenu::CurrentChoosenLoadSlot(WPARAM _wParam, LPARAM _lParam)
{
	if(GameManager::call()->LoadSlotPressed)
	{
		CGPoint pos;
		pos.x = LOWORD(_lParam);
		pos.y = HIWORD(_lParam);

		if(pos.x > 50 && pos.x < 50 + SlotWidth - 4 &&
			pos.y > 201 && pos.y < 201 + SlotHeight - 2)
		{
			GameManager::call()->SLS->MarkChoosenSlot(FirstSlotChoosen);
		}
		else if(pos.x > 50 && pos.x < 50 + SlotWidth - 4 &&
			pos.y > 314 && pos.y < 312 + SlotHeight - 2)
		{
			GameManager::call()->SLS->MarkChoosenSlot(SecondSlotChoosen);
		}
		else if(pos.x > 50 && pos.x < 50 + SlotWidth - 4 &&
			pos.y > 425 && pos.y < 423 + SlotHeight -2)
		{
			GameManager::call()->SLS->MarkChoosenSlot(ThirdSlotChoosen);
		}
		else
			GameManager::call()->SLS->MarkChoosenSlot(None);
	
	}
}