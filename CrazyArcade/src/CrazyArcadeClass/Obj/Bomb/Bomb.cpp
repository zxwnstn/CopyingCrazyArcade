#include "Etc/stdafx.h"
#include "Bomb.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"

Bomb::Bomb()
{
}
Bomb::Bomb(const POINT & _pos, int _explosionRange)
{
	explosionRange = _explosionRange;
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			auto temp = blocks[i][j].getCollisionRect();
			if (isPointRectCollision(_pos, temp)) {
				bPos.x = j;
				bPos.y = i;
				collisionRect = temp;
				return;
			}
		}
	}
}

Bomb::Bomb(const BlockPosition & _bPos, int _explosionRange)
{
	explosionRange = _explosionRange;
	bPos = _bPos;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(_bPos.x, _bPos.y);
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
