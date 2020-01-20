#include "Etc/stdafx.h"
#include "Bomb.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"

Bomb::Bomb()
{
}
Bomb::Bomb(const POINT & _pos, int _explosionRange)
{
	explosionRange = _explosionRange;
	bPos.x = (_pos.x - MAPOFFSET_X) / BLOCK_WIDTH;
	bPos.y = (_pos.y - MAPOFFSET_Y) / BLOCK_HEIGHT;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(bPos.x, bPos.y);
	curImage = IMAGEMANAGER->findImage("¹°ÆøÅº");
}

Bomb::~Bomb()
{
}

void Bomb::update(float _deltaTime)
{
	deltaTime = _deltaTime;
	pastTime += _deltaTime;
	if (pastTime > explosionTime && !timeEnd) {
		timeEnd = true;
	}
}
void Bomb::render(HDC hdc)
{
	frameCounter += deltaTime;
	if (frameCounter > frameChageTimer) {
		frameCounter = 0;
		frameIndex++;
		if (frameIndex > curImage->getMaxFrameX())
			frameIndex = 0;
	}
	curImage->frameRender(hdc, collisionRect.left + 2, collisionRect.top - 7, frameIndex, 0);
}
void Bomb::debugRender(HDC hdc)
{
	DrawColorRect(hdc, collisionRect, RGB(255, 0, 255));
}


void Bomb::explosionNow()
{
	timeEnd = true;
}
