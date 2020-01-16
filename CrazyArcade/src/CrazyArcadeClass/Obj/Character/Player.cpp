#include "Player.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"

void Player::rectSetFromPos()
{
	rect.left = pos.x - BLOCK_WIDTH / 2 + xMargin;
	rect.right = pos.x + BLOCK_WIDTH / 2 - xMargin;
	rect.bottom = pos.y + BLOCK_HEIGHT / 2 - yMargin;
	rect.top = pos.y - BLOCK_HEIGHT / 2 + yMargin;
}

Player::Player()
{
	pos.x = BLOCK_WIDTH / 2 + MAPOFFSET_X;
	pos.y = BLOCK_HEIGHT / 2 + MAPOFFSET_Y;
	prevPos = pos;
	rectSetFromPos();

	state = CharacterState::CharacterOnIdle;
	bombLimit = 3;
	bombRange = 3;
}


Player::~Player()
{
}

bool Player::init() 
{
	lastBlockPos = { -1, -1 };
	return true;
}


void Player::update(float deltaTime) 
{
	//player movement
	float dist = deltaTime * speed;
	if (state != CharacterState::CharacterDead) {
		if (state != CharacterState::CharacterInBalloon) {
			if (KEYMANAGER->isStayKeyDown(VK_UP)) {
				move(eUp, dist);
				state = CharacterState::CharacterOnUpMove;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
				move(eDown, dist);
				state = CharacterState::CharacterOnDownMove;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
				move(eLeft, dist);
				state = CharacterState::CharacterOnLeftMove;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
				move(eRight, dist);
				state = CharacterState::CharacterOnRightMove;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
				dropBomb();
			}
			checkGetItem();
		}
	}
	
	//for drop and move 
	if ((lastBlockPos.x != -1)) {
		if (!isRectRectCollision(dropAndMoveRect, rect)) {
			lastBlockPos.x = -1;
			lastBlockPos.y = -1;
		}
	}
	


	//Inballoon
	if(state != CharacterState::CharacterDead && state == CharacterState::CharacterInBalloon){
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
void Player::render(HDC hdc) {

}

void Player::debugRender(HDC hdc)
{
	if (state == CharacterState::CharacterDead) {
		DrawColorRect(hdc, rect, RGB(0, 0, 0));
		return;
	}
	if(state != CharacterState::CharacterInBalloon)
		DrawColorRect(hdc, rect, RGB(16, 248, 238));
	else if (state == CharacterState::CharacterInBalloon)
		DrawColorRect(hdc, rect, RGB(18, 67, 197));
}

void Player::dropBomb()
{
	if (bombLimit > curBombList.size()) {

		shared_ptr<Bomb> newBomb = make_shared<Bomb>();
		newBomb->init(pos, bombRange);

		

		lastBlockPos = newBomb->getPos();
		dropAndMoveRect = RectMake(
			lastBlockPos.x * BLOCK_WIDTH  + MAPOFFSET_X, 
			lastBlockPos.y * BLOCK_HEIGHT + MAPOFFSET_Y,
			BLOCK_WIDTH, BLOCK_HEIGHT
		);

		curBombList.push_back(newBomb);
		GET_SINGLE(BombManager)->GetBombs().push_back(newBomb);
	}
	
}