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
	pos.x = BLOCK_WIDTH / 2 + _blockPos.x * BLOCK_WIDTH + MAPOFFSET_X;
	pos.y = BLOCK_HEIGHT / 2 + _blockPos.y * BLOCK_HEIGHT + MAPOFFSET_Y;

	bPos = _blockPos;

	//set your character ablility	

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
				/*if (needSpeedAdjust) {
					ret = move(eUp, adjustSpeed(eUp));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else */
					ret = move(eUp, speed);
				state = CharacterState::CharacterOnUpMove;
				isAreadyMove = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN) && !isAreadyMove) {
				/*if (needSpeedAdjust) {
					ret = move(eDown, adjustSpeed(eDown));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else */
					ret = move(eDown, speed);
				state = CharacterState::CharacterOnDownMove;
				isAreadyMove = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !isAreadyMove) {
				/*if (needSpeedAdjust) {
					ret = move(eLeft, adjustSpeed(eLeft));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else */
					ret = move(eLeft, speed);
				state = CharacterState::CharacterOnLeftMove;
				isAreadyMove = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !isAreadyMove) {
				/*if (needSpeedAdjust) {
					ret = move(eRight, adjustSpeed(eRight));
					if (ret != eNoMove)
						needSpeedAdjust = false;
				}
				else */
					ret = move(eRight, speed);
				isAreadyMove = true;
				state = CharacterState::CharacterOnRightMove;
			}
			if (ret != eNoMove && isDropBombArea) {
				stayDropArea();
			}
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
				dropBomb();
			}
		}
	}

	if (m_debugMode) {
		if (KEYMANAGER->isOnceKeyDown(VK_TAB)) {
			state = CharacterState::CharacterOnIdle;
		}
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