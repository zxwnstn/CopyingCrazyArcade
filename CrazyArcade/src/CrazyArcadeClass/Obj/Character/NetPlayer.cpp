#include "NetPlayer.h"
#include "Manager/NetworkManager.h"
#define TEMP_VALUE 0

NetPlayer::NetPlayer(int x, int y, int _netID, bool _isInNetWork)
	: character(x, y)
{
	netID = _netID;
	isInNetWork = _isInNetWork;

	if (isInNetWork && netID == GET_SINGLE(NetworkManager)->getThisClientNetID()) 
	{
		characterPointer = IMAGEMANAGER->findImage("플1포인터");
	}
}


NetPlayer::~NetPlayer()
{
}

void NetPlayer::update(float _deltaTime)
{
}

void NetPlayer::update(float _deltaTime, int _dir, int _isBomb)
{
	deltaTime = _deltaTime;
	//player movement
	if (state != CharacterState::CharacterDead) {
		if (state != CharacterState::CharacterInBalloon) {
			bool isAreadyMove = false;
			Direction moveResult = eNoMove;
			prevState = state;
			if (_dir == 0) {
				moveResult = move(eUp, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnUpMove;
				state |= CharacterState::CharacterOnMove;
			}
			else if (_dir == 1) {
				moveResult = move(eDown, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnDownMove;
				state |= CharacterState::CharacterOnMove;
			}
			else if (_dir == 2) {
				moveResult = move(eRight, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnRightMove;
				state |= CharacterState::CharacterOnMove;
			}
			if (_dir == 3) {
				moveResult = move(eLeft, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnLeftMove;
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

			if (_isBomb == 1) {
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

	/*if (isInNetWork && netID == GET_SINGLE(NetworkManager)->getThisClientNetID()) 
	{
		sendMovePacket();
	}*/
}

void NetPlayer::sendMovePacket()
{
	MovePacket movePacket;

	movePacket.NetID = netID;
	movePacket.isBomb = 0;
	movePacket.playerMoveDir = 4;
	bool isAlreadMove = false;

	if (KEYMANAGER->isStayKeyDown(P1_UP)) 
	{
		if (!isAlreadMove)
		{
			isAlreadMove = true;
			movePacket.playerMoveDir = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN))
	{
		if (!isAlreadMove)
		{
			isAlreadMove = true;
			movePacket.playerMoveDir = 1;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT))
	{
		if (!isAlreadMove)
		{
			isAlreadMove = true;
			movePacket.playerMoveDir = 2;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_LEFT))
	{
		if (!isAlreadMove)
		{
			isAlreadMove = true;
			movePacket.playerMoveDir = 3;
		}
	}
	if (KEYMANAGER->isStayKeyDown(P1_EVENT))
	{
		movePacket.isBomb = 1;
	}

	GET_SINGLE(NetworkManager)->sendMovePacket(movePacket);
}




bool NetPlayer::init(CharacterType _type)
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
