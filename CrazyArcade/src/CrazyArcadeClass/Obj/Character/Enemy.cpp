#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(int x, int y)
	: character(x, y)
{
}


Enemy::~Enemy()
{
}

void Enemy::moveAI(float deltaTime)
{
}

void Enemy::update(float deltaTime)
{
	moveAI(deltaTime);
	if (state != CharacterState::CharacterDead && state == CharacterState::CharacterInBalloon) {
		deadPastTime += deltaTime;
		if (deadPastTime > deadTime)
			die();
	}
}

bool Enemy::init(CharacterType _type)
{
	return true;
}

