#include "Etc/stdafx.h"
#include "Boom.h"


Boom::Boom(BoomState _boomstate, float addedTime, BlockPosition _bPos)
	:state(_boomstate), bPos(_bPos)
{
	explosionDuring += addedTime;
	collisionRect.left = _bPos.x * BLOCK_WIDTH + MAPOFFSET_X;
	collisionRect.right = (_bPos.x + 1) * (BLOCK_WIDTH) + MAPOFFSET_X;
	collisionRect.top = _bPos.y * BLOCK_HEIGHT + MAPOFFSET_Y;
	collisionRect.bottom = (_bPos.y + 1) * (BLOCK_HEIGHT) + MAPOFFSET_Y;

	switch (state)
	{
	case BoomState::BoomCenter:
		break;
	case BoomState::BoomHorizenRight:
		break;
	case BoomState::BoomHorizenRightEnd:
		break;
	case BoomState::BoomHorizenLeft:
		break;
	case BoomState::BoomHorizenLeftEnd:
		break;
	case BoomState::BoomVerticalUp:
		break;
	case BoomState::BoomVerticalUpEnd:
		break;
	case BoomState::BoomVerticalDown:
		break;
	case BoomState::BoomVerticalDownEnd:
		break;
	}
}
Boom::~Boom()
{
	curImage = nullptr;
}

void Boom::update(float deltaTime)
{
	pastTime += deltaTime;
	if (pastTime > explosionDuring)
		timeEnd = true;
}
void Boom::render(HDC hdc)
{
	switch (state)
	{
	case BoomState::BoomCenter:
		break;
	case BoomState::BoomHorizenRight:
		break;
	case BoomState::BoomHorizenRightEnd:
		break;
	case BoomState::BoomHorizenLeft:
		break;
	case BoomState::BoomHorizenLeftEnd:
		break;
	case BoomState::BoomVerticalUp:
		break;
	case BoomState::BoomVerticalUpEnd:
		break;
	case BoomState::BoomVerticalDown:
		break;
	case BoomState::BoomVerticalDownEnd:
		break;
	}
}
void Boom::debugRender(HDC hdc)
{
	DrawColorRect(hdc, collisionRect, RGB(22,237,237));
}

