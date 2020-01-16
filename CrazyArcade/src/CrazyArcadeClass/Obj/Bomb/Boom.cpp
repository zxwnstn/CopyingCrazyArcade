#include "Etc/stdafx.h"
#include "Boom.h"


Boom::Boom(BoomState _boomstate, float addedTime, BlockPosition _pos)
	:boomState(_boomstate), pos(_pos)
{
	explosionDuring += addedTime;
	rect.left = _pos.x * BLOCK_WIDTH + MAPOFFSET_X;
	rect.right = (_pos.x + 1) * (BLOCK_WIDTH) + MAPOFFSET_X;
	rect.top = _pos.y * BLOCK_HEIGHT + MAPOFFSET_Y;
	rect.bottom = (_pos.y + 1) * (BLOCK_HEIGHT) + MAPOFFSET_Y;
}

Boom::~Boom()
{
}

void Boom::update(float deltaTime)
{
	pastTime += deltaTime;
	if (pastTime > explosionDuring)
		timeEnd = true;
}

void Boom::render(HDC hdc)
{
}

void Boom::debugRender(HDC hdc)
{
	DrawColorRect(hdc, rect, RGB(22,237,237));
}

