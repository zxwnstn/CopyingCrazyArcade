#include "Etc/stdafx.h"
#include "Game/mainGame.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console" )

mainGame mg;
HINSTANCE m_hInstance;
HWND m_hWnd;
POINT m_ptMouse;
bool m_bLoop = true;
bool m_showFPS = false;
bool m_showRect = false;
bool m_debugMode = false;
LPTSTR m_lpszClass = TEXT("Crazy Arcade");

//메인게임

//윈도우 클래스 이름
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(97);

	m_hInstance = hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = m_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	
	m_hWnd = CreateWindow(
		WINNAME,			
		WINNAME,			
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,			
		WINSTARTY,			
		WINSIZEX,			
		WINSIZEY,			
		NULL,				
		(HMENU)NULL,		
		hInstance,			
		NULL);

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(m_hWnd, nCmdShow);
	ShowCursor(false);
	//SetFocus(m_hWnd);

	if (FAILED(mg.init()))
	{
		return 0;
	}
	MSG message;


	while (m_bLoop) {
		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		mg.update();
		mg.render();
	}
	mg.release();

	return message.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam){
	return mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height){
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(m_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}