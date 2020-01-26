#include "Player.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "Manager/SoundManager.h"
#include "CrazyArcadeClass/Type.h"


Player::Player(int x, int y, bool _isInNetWork)
	: character(x, y)
{
	characterPointer = IMAGEMANAGER->findImage("플1포인터");
	isInNetWork = _isInNetWork;
}
Player::~Player()
{
}


bool Player::init(CharacterType _type)
{
	type = _type;

	//imageSettup
	switch (type)
	{
	case CharacterType::Dao:
		moveImage = IMAGEMANAGER->findImage("다오이동");
		deadImage = IMAGEMANAGER->findImage("다오죽음");
		inBalloonImage = IMAGEMANAGER->findImage("다오풍선안");
		break;
	case CharacterType::Bazzi:
		moveImage = IMAGEMANAGER->findImage("배찌이동");
		deadImage = IMAGEMANAGER->findImage("배찌죽음");
		inBalloonImage = IMAGEMANAGER->findImage("배찌풍선안");
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
			if (KEYMANAGER->isStayKeyDown(P1_UP) && !isAreadyMove) {
				moveResult = move(eUp, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnUpMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !isAreadyMove) {
				moveResult = move(eDown, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnDownMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !isAreadyMove) {
				moveResult = move(eLeft, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnLeftMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && !isAreadyMove) {
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
			
			inBush = isInBush();

			if (KEYMANAGER->isOnceKeyDown(P1_EVENT)) {
				dropBomb();
			}
		}
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