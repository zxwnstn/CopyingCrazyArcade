#include "Etc/stdafx.h"
#include "InGameScene.h"


InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

HRESULT InGameScene::init()
{
	//image settup
	IMAGEMANAGER->addImage("맵", "images/map.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어", "images/bazziReadyCharacter.bmp", 54, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("하드블록", "images/house.bmp", 180, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타일", "images/Tile.bmp", 300, 60);

	GET_SINGLE(BlockManager)->init();
	GET_SINGLE(CharacterManager)->init();
	GET_SINGLE(BombManager)->init();
	GET_SINGLE(ItemManager)->init();


	return S_OK;
}

void InGameScene::release()
{
	RELEASE_SINGLE(BlockManager);
	RELEASE_SINGLE(CharacterManager);
	RELEASE_SINGLE(BombManager);
	RELEASE_SINGLE(ItemManager);
}

void InGameScene::update(float deltaTime)
{
	GET_SINGLE(BlockManager)->update(deltaTime);
	GET_SINGLE(CharacterManager)->update(deltaTime);
	GET_SINGLE(BombManager)->update(deltaTime);
	GET_SINGLE(ItemManager)->update(deltaTime);
}

void InGameScene::render()
{
	GET_SINGLE(BlockManager)->render(getMemDC());
	GET_SINGLE(CharacterManager)->render(getMemDC());
	GET_SINGLE(BombManager)->render(getMemDC());
	GET_SINGLE(ItemManager)->render(getMemDC());
	IMAGEMANAGER->render("맵", getMemDC(), 0, 0);
}

void InGameScene::debugRender()
{
	GET_SINGLE(BlockManager)->debugRender(getMemDC());
	GET_SINGLE(CharacterManager)->debugRender(getMemDC());
	GET_SINGLE(BombManager)->debugRender(getMemDC());
	GET_SINGLE(ItemManager)->debugRender(getMemDC());
	
}
