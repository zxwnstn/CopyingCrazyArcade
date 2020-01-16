#include "Player.h"
#include "HomeWorkClass/Manager/BombManager.h"
#include "HomeWorkClass/Manager/CharacterManager.h"
#include "HomeWorkClass/Manager/BlockManager.h"
#include "HomeWorkClass/Manager/ItemManager.h"

void Player::rectSetFromPos()
{
	rect.left = pos.x - BLOCK_WIDTH / 2 + xMargin;
	rect.right = pos.x + BLOCK_WIDTH / 2 - xMargin;
	rect.bottom = pos.y + BLOCK_HEIGHT / 2 - yMargin;
	rect.top = pos.y - BLOCK_HEIGHT / 2 + yMargin;
}

Player::Player()
{
	pos.x = BLOCK_WIDTH / 2;
	pos.y = BLOCK_HEIGHT / 2;
	prevPos = pos;
	rectSetFromPos();

	speed = 100.f;
	state = CharacterState::CharacterOnIdle;
	bombLimit = 3;
	bombRange = 3;
}


Player::~Player()
{
}

bool Player::init() 
{
	return true;
}
void Player::update(float deltaTime) 
{
	//player movement
	if ((state != CharacterState::CharacterInBallon)) {
		if (KEYMANAGER->isStayKeyDown(VK_UP)) {
			pos.y -= deltaTime * speed;
			state = CharacterState::CharacterOnUpMove;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			pos.y += deltaTime * speed;
			state = CharacterState::CharacterOnDownMove;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
			pos.x -= deltaTime * speed;
			state = CharacterState::CharacterOnLeftMove;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
			pos.x += deltaTime * speed;
			state = CharacterState::CharacterOnRightMove;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			dropBomb();
		}

		rectSetFromPos();
		if (isCollison()) {
			pos = prevPos;
			rectSetFromPos();
		}
		prevPos = pos;
	}
	if (state == CharacterState::CharacterInBallon) {
		deadPastTime += deltaTime;
		if (deadPastTime > deadTime) {
			state = CharacterState::CharacterDead;
		}
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
	if(state != CharacterState::CharacterInBallon)
		DrawColorRect(hdc, rect, RGB(16, 248, 238));
	else if (state == CharacterState::CharacterInBallon)
		DrawColorRect(hdc, rect, RGB(18, 67, 197));
	else if (state == CharacterState::CharacterDead) {
		DrawColorRect(hdc, rect, RGB(0, 0, 0));
	}
}

bool Player::isCollison()
{
	auto& bombs = GET_SINGLE(BombManager)->GetBombs();
	auto& items = GET_SINGLE(ItemManager)->GetItems();
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	auto& booms = GET_SINGLE(BombManager)->GetBooms();
	//auto& enemy = GET_SINGLE(CharacterManager)

	for (auto it = booms.begin(); it != booms.end(); ) {
		if (isRectRectCollision((*it)->getRect(), rect)) {
			state = CharacterState::CharacterInBallon;
			return true;
		}
		else ++it;
	}
	
	for (auto it = items.begin(); it != items.end(); ) {
		if (isRectRectCollision(rect, (*it)->getRect())) {
			switch ((*it)->getType())
			{
			case ItemType::ItemRangeUp:
				++bombRange;
				break;
			case ItemType::ItemSpeedUp:
				speed += SPEED_UP_RATE;
				break;
			case ItemType::ItemBombLimitUp:
				++bombLimit;
				break;
			case ItemType::ItemKick:
				usableItemList.push_back((*it));
				break;
			case ItemType::ItemDart:
				usableItemList.push_back((*it));
				break;
			case ItemType::ItemNone:
				break;
			}
			it = items.erase(it);
		}
		else ++it;
	}




	/*for (auto& e : bombs) {
		if (isRectRectCollision(rect, e->getRect()))
			return true;
	}*/

	for (int i = 0; i < NUM_BLOCK_X; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			if (blocks[i][j].getType() != BlockType::BlockNone) {
				if (isRectRectCollision(rect, blocks[i][j].getRect()))
					return true;
			}
		}
	}

	

	return false;
}

void Player::dropBomb()
{
	if (bombLimit > curBombList.size()) {
		shared_ptr<Bomb> newBomb = make_shared<Bomb>();
		newBomb->init(pos, bombRange);
		curBombList.push_back(newBomb);
		GET_SINGLE(BombManager)->GetBombs().push_back(newBomb);
	}
	
}
