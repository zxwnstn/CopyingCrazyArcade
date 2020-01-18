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

}

Bomb::~Bomb()
{
}

void Bomb::update(float deltaTime)
{
	pastTime += deltaTime;
	if (pastTime > explosionTime && !timeEnd) {
		timeEnd = true;
	}
}
void Bomb::render(HDC hdc)
{
}
void Bomb::debugRender(HDC hdc)
{
	DrawColorRect(hdc, collisionRect, RGB(255, 0, 255));
}


void Bomb::explosionNow()
{
	timeEnd = true;
}
