#include "Etc/stdafx.h"
#include "mainGame.h"
#include "CrazyArcadeClass/Scene/InGameScene.h"
#include "CrazyArcadeClass/Scene/MainMenu.h"
#include "CrazyArcadeClass/Scene/NetWorkScene.h"
#include "Manager/SoundManager.h"

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
	SCENEMANAGER->addScene("메인메뉴", new MainMenu);
	SCENEMANAGER->addScene("TCP/IP", new NetWorkScene);
	SCENEMANAGER->changeScene("메인메뉴");

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
}  

void mainGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
		m_showRect = !m_showRect;
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		m_showFPS = !m_showFPS;

	GET_SINGLE(SoundManager)->update();
	TIMEMANAGER->update(60.f);
	SCENEMANAGER->update(TIMEMANAGER->getElapsedTime());
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);


	SCENEMANAGER->render();
	SCENEMANAGER->afterRender();

	if (m_showRect == true)
		SCENEMANAGER->debugRender();

	if (m_showFPS)
		TIMEMANAGER->render(getMemDC());

	getBackBuffer()->render(getHDC(), 0, 0);
}