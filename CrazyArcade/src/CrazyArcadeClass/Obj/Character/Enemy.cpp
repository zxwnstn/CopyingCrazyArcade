#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

bool Enemy::init()
{
	return true;
}

void Enemy::moveAI(float deltaTime)
{
}

void Enemy::update(float deltaTime)
{
	moveAI(deltaTime);
}

void Enemy::render(HDC hdc)
{
}

void Enemy::debugRender(HDC hdc)
{
	DrawColorRect(hdc, rect, RGB(125, 125, 125));
}
