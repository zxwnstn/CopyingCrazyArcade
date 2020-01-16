#pragma once
#include "Manager/Image.h"

static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);


class gameNode
{
private:
	//void setBackBuffer();
	HDC		_hdc;
	bool	_managerInit;

public:
	gameNode();
	~gameNode();

	virtual HRESULT init(bool managerInit);
	virtual HRESULT init();
	virtual void release();
	virtual void update(float deltaTime);
	virtual void render();
	virtual void debugRender() {};

	Image* getBackBuffer() { return _backBuffer; }
	HDC getHDC() { return _hdc; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};