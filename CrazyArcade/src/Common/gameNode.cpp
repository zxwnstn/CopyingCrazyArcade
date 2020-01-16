#include "Etc/stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

void gameNode::update(float deltaTime)
{
}
void gameNode::render()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	//매니저 초기화
	if (_managerInit) {
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
	}
	return E_NOTIMPL;
}

void gameNode::release()
{
	//매니저 해제
	if (_managerInit) {
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		RND->releaseSingleton();
	}
	ReleaseDC(m_hWnd, _hdc);
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			m_bLoop = false;
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		m_bLoop = false;
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}
