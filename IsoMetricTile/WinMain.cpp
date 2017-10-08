#include"GameMananger.h"
#include"BKG.h"
#include"SceneOne.h"
#include"SceneMenu.h"

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

GameManager GameManager::Instance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR strCmdLine, int nShowCmd)
{
	////��ϰ���

	WNDCLASSEX wcex;			//������ ���� ����ü
	memset(&wcex, 0, sizeof(wcex));

	wcex.cbSize			= sizeof(wcex);							//������ ����ü ũ��
	wcex.style			= CS_HREDRAW | CS_VREDRAW;					//Ŭ���� ��Ÿ��
	wcex.hbrBackground	= (HBRUSH)GetStockObject(LTGRAY_BRUSH);		//Ŭ���̾�Ʈ ����
	wcex.hCursor			= LoadCursor(NULL, IDC_ARROW);				//Ŀ�� ���
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);			//������ ���
	wcex.hInstance		= hInstance;								//���α׷� ��ȣ
	wcex.cbClsExtra		= 0;										//
	wcex.cbWndExtra		= 0;										//
	wcex.hIconSm			= NULL;									//
	wcex.lpszMenuName		= NULL;									//
	wcex.lpfnWndProc		= WinProc;								//�޽��� ó�� �Լ� (�Լ� �����͸� ��� ���)
	wcex.lpszClassName	= L"MyWindow";							//�� ������ ������ Ŭ���� �̸�
	RegisterClassEx(&wcex);
	///////


	//�����
	HWND hWnd = CreateWindow(L"MyWindow", L"MyWindow", WS_OVERLAPPEDWINDOW,
		0, 0, 1600, 1000, NULL, NULL, hInstance, NULL);

	if(hWnd == NULL)
	{
		MessageBox(NULL, L"������ ���� ����", L"����", MB_ICONERROR | MB_OK);
		return -1;
	}

	//���
	ShowWindow(hWnd, SW_SHOW);

	DWORD prevTime = timeGetTime();		
	DWORD delayTime = timeGetTime();

	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while( msg.message != WM_QUIT )
	{   
		delayTime = timeGetTime() - prevTime;
		prevTime = timeGetTime();
		float dt = delayTime / 1000.f;

		GameManager::call()->pNowRunningScene->run(dt);

		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		{
			GameManager::call()->CreateBackBuf(hWnd);	
			GameManager::call()->SM.init();
			GameManager::call()->SM.loading();
			SceneMenu::SetActive();
			break;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint( hWnd, &ps );

			BitBlt(hDC, 0, 0, 1950, 1400, GameManager::call()->backDC, 0, 0, SRCCOPY );
			EndPaint(hWnd, &ps);
			break;
		}
	case WM_RBUTTONDOWN:
		{
			GameManager::call()->MouseRButtonDown(wParam, lParam);
			break;
		}
	case WM_LBUTTONDOWN:
		{
			switch(GameManager::call()->CurScene)
			{
			case SCENE_MENU:
				SceneMenu::CheckSelection(wParam, lParam);
				break;
			case SCENE_MAKEMAP:
				SceneOne::CheckSelection(wParam, lParam);
				break;
			case SCENE_SAVED:
				SceneSaved::CheckSelection(wParam, lParam);
				break;
			}

			break;
		}
	case WM_MOUSEMOVE:
		{
			switch(GameManager::call()->CurScene)
			{
			case SCENE_MENU:
				SceneMenu::CurrentChoosenLoadSlot(wParam, lParam);
				break;
			case SCENE_MAKEMAP:
				GameManager::call()->CurrentChoosenSlot(wParam, lParam);
				break;
			case SCENE_SAVED:
				GameManager::call()->CurrentChoosenSlot(wParam, lParam);
				break;
			}
			GameManager::call()->MouseMove(wParam, lParam);
			break;
		}
	case WM_RBUTTONUP:
		{
			GameManager::call()->MouseRButtonUp();
			break;
		}
	case WM_LBUTTONUP:
		{
			GameManager::call()->MouseLButtonUp();
			break;
		}
	
	case WM_DESTROY:
		{
			GameManager::call()->dealloc();
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
