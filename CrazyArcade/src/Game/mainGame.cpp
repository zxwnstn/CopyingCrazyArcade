#include "Etc/stdafx.h"
#include "mainGame.h"
#include "HomeWorkClass/Scene/InGameScene.h"

mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);
	//image init
	
	SCENEMANAGER->addScene("인게임", new InGameScene);
	SCENEMANAGER->changeScene("인게임");

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SCENEMANAGER->release();
}  

void mainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		m_showRect = !m_showRect;
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		m_showFPS = !m_showFPS;

	TIMEMANAGER->update(60.f);
	SCENEMANAGER->update(TIMEMANAGER->getElapsedTime());
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	//SCENEMANAGER->render();

	if (m_showRect)
		SCENEMANAGER->debugRender();

	if (m_showFPS)
		TIMEMANAGER->render(getMemDC());

	getBackBuffer()->render(getHDC(), 0, 0);
}