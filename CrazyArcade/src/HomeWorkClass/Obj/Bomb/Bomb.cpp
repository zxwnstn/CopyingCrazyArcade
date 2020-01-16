#include "Etc/stdafx.h"
#include "Bomb.h"
#include "HomeWorkClass/Manager/BlockManager.h"

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

bool Bomb::init(const FPOINT & _pos, int _explosionRange)
{
	explosionRange = _explosionRange;
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			if (isPointRectCollison(_pos, blocks[i][j].getRect())) {
				auto temp = blocks[i][j].getRect();
				pos.x = i;
				pos.y = j;
				rect = temp;
			}
		}
	}
	return true;
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
	DrawColorRect(hdc, rect, RGB(255, 0, 255));
}

void Bomb::release()
{
}

void Bomb::explosionNow()
{
	timeEnd = true;
}
