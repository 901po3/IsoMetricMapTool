#include"Scene.h"
#include"GameMananger.h"

void Scene::init()
{
	memset(m_pObjectList, NULL, sizeof(m_pObjectList));
	rect.BOTTOM		= 1400;
	rect.LEFT		= -64;
	rect.RIGHT		= 1900;
	rect.TOP			= -64;
}

bool Scene::PointExitCheck(CGPoint pos)
{
	if(pos.x > rect.LEFT && pos.x < rect.RIGHT
		&& pos.y > rect.TOP && pos.y < rect.BOTTOM) return false;
	return true;
}

void Scene::run(float dt)
{
	if(GameManager::call()->CurScene == SCENE_MAKEMAP)
		if(!GameManager::call()->CheckTilePosSetting) return;

	GameManager::call()->Scroll(dt);

	Order();

	for(int i=0; i< MAX_OBJECT; i++)
	{
		if(m_pObjectList[i] == NULL) continue;
		if(!m_pObjectList[i]->GetActive()) continue;

		m_pObjectList[i]->update(dt);
		m_pObjectList[i]->render();
	}

	InvalidateRect(GameManager::call()->hWnd, NULL, false);
}

void Scene::addObject(Object * obj)
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		if(m_pObjectList[i] != NULL) continue;
		
		m_pObjectList[i] = obj;
		break;
	}
}

void Scene::dealloc()
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		if(m_pObjectList[i] == NULL) continue;

		//현제 메모리 누수 발생 
		//m_pObjectList[i]->dealloc();
		//delete m_pObjectList[i];
		m_pObjectList[i] = NULL;
	}
}

void Scene::Order()
{
	int i,j;
	int step;
	Object* saveValue = NULL;
	int saveIndex;
	int val = 0;

	for(step=1; step<MAX_OBJECT; step = 3*step+1);
	for(step/=3; step>0; step/=3)
	{
		for(i=0; i<step; i++)
		{
			for(j=step+i; j<MAX_OBJECT; j+=step)
			{
				saveValue = m_pObjectList[j];
				saveIndex = j;
				if(saveValue == NULL) continue;

				val = saveValue->GetNumberTag();
				while(saveIndex > step-1)
				{
					if(m_pObjectList[saveIndex-step] != NULL)
					{
						if(val < m_pObjectList[saveIndex-step]->GetNumberTag())
						{
							m_pObjectList[saveIndex] = m_pObjectList[saveIndex-step];
						}
						else if(val >= m_pObjectList[saveIndex-step]->GetNumberTag())
						{
							break;
						}
					}
					saveIndex -= step;
				}
				m_pObjectList[saveIndex] = saveValue;
				saveValue = NULL;
				val = 0;
			}
		}
	}
}

void Scene::CheckFalse()
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		if(m_pObjectList[i] == NULL) continue;
		if(m_pObjectList[i]->GetActive() == false)
		{
			m_pObjectList[i] = NULL;
		}
	}
}