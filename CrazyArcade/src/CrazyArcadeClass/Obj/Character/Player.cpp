#include "Player.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Type.h"


Player::Player()
{
}
Player::Player(int x, int y)
	: character(x, y)
{
}
Player::~Player()
{
}


bool Player::init(CharacterType _type)
{
	//TODO : init specific player info
	type = _type;

	//imageSettup
	switch (type)
	{
	case CharacterType::Dao:
		break;
	case CharacterType::Bazzi:
		moveImage		=	IMAGEMANAGER->findImage("¹èÂîÀÌµ¿");
		deadImage		=	IMAGEMANAGER->findImage("¹èÂîÁ×À½");
		inBalloonImage	=	IMAGEMANAGER->findImage("¹èÂîÇ³¼±¾È");
		break;
	}
	return true;
}

void Player::update(float _deltaTime)
{
	deltaTime = _deltaTime;
	//player movement
	if (state != CharacterState::CharacterDead) {
		if (state != CharacterState::CharacterInBalloon) {
			bool isAreadyMove = false;
			Direction moveResult = eNoMove;
			prevState = state;
			if (KEYMANAGER->isStayKeyDown(VK_UP) && !isAreadyMove) {
				moveResult = move(eUp, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnUpMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !isAreadyMove) {
				moveResult = move(eDown, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnDownMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !isAreadyMove) {
				moveResult = move(eLeft, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnLeftMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !isAreadyMove) {
				moveResult = move(eRight, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnRightMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (!isAreadyMove) {
				state ^= CharacterState::CharacterOnMove;
				state ^= CharacterState::CharacterNoMove;
			}
			if (moveResult != eNoMove && isDropBombArea) {
				stayDropArea();
			}
			
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
				dropBomb();
			}
		}
	}

	if (m_debugMode) {
		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
			state = CharacterState::CharacterOnIdle;
		if (KEYMANAGER->isOnceKeyDown('A'))
			speedUp();
		if (KEYMANAGER->isOnceKeyDown('S'))
			bombLimitUp();
		if (KEYMANAGER->isOnceKeyDown('D'))
			bombRangeUp();
	}

	//Inballoon
	if (state != CharacterState::CharacterDead && state == CharacterState::CharacterInBalloon) {
		deadPastTime += deltaTime;
		if (deadPastTime > deadTime)
			die();
	}

	//player bomb check
	for (auto it = curBombList.begin(); it != curBombList.end();) {
		if ((*it)->isTimeEnd())
			it = curBombList.erase(it);
		else ++it;
	}
}