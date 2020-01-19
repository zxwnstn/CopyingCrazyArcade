#include "Etc/stdafx.h"
#include "InGameScene.h"
#include "Manager/SoundManager.h"

InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

HRESULT InGameScene::init()
{
	//=============== inGameScene image settup ======================//

	//map
	IMAGEMANAGER->addImage		("ÀÎ°ÔÀÓ¾À¹è°æ", "images/map.bmp",					WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//character
	IMAGEMANAGER->addImage		("ÇÃ·¹ÀÌ¾î",	"images/bazziReadyCharacter.bmp",	54, 63, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("¹èÂîÀÌµ¿",	"images/BazziMove.bmp",				560, 320, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("¹èÂîÇ³¼±¾È",	"images/bazziBubble.bmp",			960, 65, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("¹èÂîÁ×À½",	"images/bazziDie.bmp",				770, 110, 11, 1, true, RGB(255, 0, 255));

	//block
	IMAGEMANAGER->addImage		("ÇÏµåºí·Ï",	"images/house.bmp",					180, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("¼ÒÇÁÆ®ºí·Ï",	"images/box.bmp",					180, 67, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage		("Å¸ÀÏ",		"images/Tile.bmp",					300, 60);

	//bomb
	IMAGEMANAGER->addFrameImage	("¹°ÆøÅº",		"images/bomb_already.bmp",			222, 75, 4, 1, true, RGB(255, 0, 255));

	//boom
	IMAGEMANAGER->addFrameImage	("Æø¹ßÀ§ÂÊ³¡",	"images/bomb_top.bmp",				540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ßÀ§ÂÊ",	"images/bomb_top_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¾Æ·¡ÂÊ³¡","images/bomb_bottom.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¾Æ·¡ÂÊ",	"images/bomb_bottom_ex.bmp",		540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¿À¸¥ÂÊ³¡","images/bomb_right.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¿À¸¥ÂÊ",	"images/bomb_right_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¿ÞÂÊ³¡",	"images/bomb_left.bmp",				540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¿ÞÂÊ",	"images/bomb_left_ex.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage	("Æø¹ß¼¾ÅÍ",	"images/bomb_center.bmp",			540, 60, 9, 1, true, RGB(255, 0, 255));

	//item
	IMAGEMANAGER->addFrameImage	("¾ÆÀÌÅÛ",		"images/item.bmp", 160, 234, 3, 4, true, RGB(255, 0, 255));

	GET_SINGLE(SoundManager)->addSound("ºÕÈú", "music/Boomhill.mp3");
	//============================================================//

	//InGameScene manager init
	GET_SINGLE(BlockManager)->init();
	GET_SINGLE(CharacterManager)->init();
	GET_SINGLE(BombManager)->init();
	GET_SINGLE(ItemManager)->init();

	//for debugMode
	sprintf(str, "DEBUG ENABLED A : speed up S : limit up D : range up");
	len = strlen(str);

	GET_SINGLE(SoundManager)->playeSound("ºÕÈú", 0);
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
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
		m_debugMode = !m_debugMode;

	GET_SINGLE(BlockManager)->update(deltaTime);
	GET_SINGLE(BombManager)->update(deltaTime);
	GET_SINGLE(CharacterManager)->update(deltaTime);
	GET_SINGLE(ItemManager)->update(deltaTime);
}

void InGameScene::render()
{
	DrawColorRect(getMemDC(), IRECT(0, 0, WINSIZEX, WINSIZEY), RGB(95, 95, 95));
	IMAGEMANAGER->render("ÀÎ°ÔÀÓ¾À¹è°æ", getMemDC(), 0, 0);

	GET_SINGLE(BlockManager)->render(getMemDC());
	GET_SINGLE(BombManager)->render(getMemDC());
	GET_SINGLE(ItemManager)->render(getMemDC());
	GET_SINGLE(CharacterManager)->render(getMemDC());

	if (m_debugMode) {
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 100, 20, str, len);
	}
}

void InGameScene::afterRender()
{
	GET_SINGLE(BlockManager)->afterRender(getMemDC());
}

void InGameScene::debugRender()
{
	GET_SINGLE(BlockManager)->debugRender(getMemDC());
	GET_SINGLE(CharacterManager)->debugRender(getMemDC());
	GET_SINGLE(BombManager)->debugRender(getMemDC());
	GET_SINGLE(ItemManager)->debugRender(getMemDC());

}
