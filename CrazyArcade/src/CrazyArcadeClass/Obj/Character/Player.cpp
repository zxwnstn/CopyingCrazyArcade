#include "Player.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"



Player::Player()
{
}

Player::~Player()
{
}

bool Player::init(BlockPosition _blockPos = BlockPosition(0,0))
{
	pos.x = BLOCK_WIDTH / 2 + MAPOFFSET_X;
	pos.y = BLOCK_HEIGHT / 2 + MAPOFFSET_Y;
	rectSetFromPos();

	state = CharacterState::CharacterOnIdle;


	return true;
}

void Player::update(float deltaTime)
{
	//player movement
	if (state != CharacterState::CharacterDead) {
		if (state != CharacterState::CharacterInBalloon) {

			bool isAreadyMove = false;
			Direction ret = eNoMove;
			if (KEYMANAGER->isStayKeyDown(VK_UP) && !isAreadyMove) {
				if (needSpeedAdjust) {
					ret = move(eUp, adjustSpeed(eUp));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else move(eUp, speed);
				state = CharacterState::CharacterOnUpMove;
				isAreadyMove = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !isAreadyMove) {
				if (needSpeedAdjust) {
					ret = move(eDown, adjustSpeed(eDown));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else move(eDown, speed);
				state = CharacterState::CharacterOnDownMove;
				isAreadyMove = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !isAreadyMove) {
				if (needSpeedAdjust) {
					move(eLeft, adjustSpeed(eLeft));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else move(eLeft, speed);
				state = CharacterState::CharacterOnLeftMove;
				isAreadyMove = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !isAreadyMove) {
				if (needSpeedAdjust) {
					move(eRight, adjustSpeed(eRight));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else move(eRight, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnRightMove;
			}
			if (KEYMANAGER->isOnceKeyDown('A')) {
				if (speed < 6) {
					speed += 1;
					needSpeedAdjust = true;
				}
			}

			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
				dropBomb();
			}
		}
	}

	//for drop and move 
	/*if ((lastBlockPos.x != -1)) {
		if (!isRectRectCollision(dropAndMoveRect, rect)) {
			lastBlockPos.x = -1;
			lastBlockPos.y = -1;
		}
	}*/

	//Inballoon
	if (state != CharacterState::CharacterDead && state == CharacterState::CharacterInBalloon) {
		deadPastTime += deltaTime;
		if (deadPastTime > deadTime)
			state = CharacterState::CharacterDead;
	}

	//player bomb check
	for (auto it = curBombList.begin(); it != curBombList.end();) {
		if ((*it)->isTimeEnd())
			it = curBombList.erase(it);
		else ++it;
	}
}