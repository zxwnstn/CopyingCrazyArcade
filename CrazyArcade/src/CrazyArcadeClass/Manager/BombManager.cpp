#include "Etc/stdafx.h"
#include "BombManager.h"

#include "BlockManager.h"
#include "CharacterManager.h"
#include "Manager/SoundManager.h"
#include "ItemManager.h"
DEFINITION_SINGLE(BombManager)

BombManager::BombManager()
{
}
BombManager::~BombManager()
{
	release();
}

bool BombManager::init()
{
	return true;
}
void BombManager::update(float deltaTime)
{
	for (auto&e : booms)
		e->update(deltaTime);
	for (auto&e : bombs)
		e->update(deltaTime);
	
	for (auto it = bombs.begin(); it != bombs.end(); ) {
		if ((*it)->isTimeEnd()) {
			generateBoom((*it)->getPos(), (*it)->getExplosionRange());
			GET_SINGLE(SoundManager)->playSound("Æø¹ßÀ½", 2);
			it = bombs.erase(it);
		}
		else ++it;
	}
	for (auto it = booms.begin(); it != booms.end(); ) {
		if ((*it)->isTimeEnd()) {
			it = booms.erase(it);
		}
		else ++it;
	}

	collisionBoom();
	collisionPlayer();
	collisionItem();
}
void BombManager::render(HDC hdc)
{
	for (auto& e : bombs)
		e->render(hdc);
	for (auto& e : booms)
		e->render(hdc);
}
void BombManager::debugRender(HDC hdc)
{
	for (auto& e : bombs)
		e->debugRender(hdc);
	for (auto& e : booms)
		e->debugRender(hdc);
}
void BombManager::release()
{
	bombs.clear();
	booms.clear();
}

bool BombManager::inRange(int x, int y)
{
	if ((0 <= x && x < NUM_BLOCK_X) &&
		(0 <= y && y < NUM_BLOCK_Y))
		return true;
	return false;
}
void BombManager::rangeCheckAndGenBoom(const BlockPosition& startPoint, int dx, int dy, int Range)
{
	BoomState state;
	if (dx > 0)
		state = BoomState::BoomHorizenRight;
	else if (dx < 0)
		state = BoomState::BoomHorizenLeft;
	else if(dy > 0)
		state = BoomState::BoomVerticalDown;
	else if(dy < 0)
		state = BoomState::BoomVerticalUp;


	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	float addedTime = 0.f;

	for (int i = 1; i <= Range; ++i) {
		bool inBush = false;
		int nextX = startPoint.x + dx * i;
		int nextY = startPoint.y + dy * i;

		addedTime += boomAddedTime;

		if (inRange(nextX, nextY)) {
			bool reachEnd = false;
			if (i == Range) {
				switch (blocks[nextY][nextX].getType())
				{
				case BlockType::BlockHard:
					reachEnd = true;
					break;
				case BlockType::BlockTree:
					reachEnd = true;
					break;
				case BlockType::BlockSoft:
					if(!blocks[nextY][nextX].isWillDis())
						blocks[nextY][nextX].triggerDis(addedTime + BLOCK_DIS_DELAY);
					reachEnd = true;
					break;
				case BlockType::BlockBush:
					if (!blocks[nextY][nextX].isWillDis())
						blocks[nextY][nextX].triggerDis(addedTime + BLOCK_DIS_DELAY);
					inBush = true;
					reachEnd = true;
					break;
				case BlockType::BlockNone:
					if (state == BoomState::BoomHorizenRight)
						state = BoomState::BoomHorizenRightEnd;
					if (state == BoomState::BoomHorizenLeft)
						state = BoomState::BoomHorizenLeftEnd;
					if (state == BoomState::BoomVerticalUp)
						state = BoomState::BoomVerticalUpEnd;
					if (state == BoomState::BoomVerticalDown)
						state = BoomState::BoomVerticalDownEnd;
					booms.push_back(make_shared<Boom>(state, addedTime, BlockPosition(nextX, nextY), inBush));
					break;
				}
			}
			else {
				switch (blocks[nextY][nextX].getType())
				{
				case BlockType::BlockHard:
					reachEnd = true;
					break;
				case BlockType::BlockTree:
					reachEnd = true;
					break;
				case BlockType::BlockSoft:
					if (!blocks[nextY][nextX].isWillDis())
						blocks[nextY][nextX].triggerDis(addedTime + BLOCK_DIS_DELAY);
					reachEnd = true;
					break;
				case BlockType::BlockBush:
					if (!blocks[nextY][nextX].isWillDis())
						blocks[nextY][nextX].triggerDis(addedTime + BLOCK_DIS_DELAY);
					inBush = true;
					break;
				case BlockType::BlockNone:
					booms.push_back(make_shared<Boom>(state, addedTime, BlockPosition(nextX, nextY), inBush));
					break;
				}
			}
			if (reachEnd) break;
		}
		else break;
	}
}
void BombManager::generateBoom(const BlockPosition& startPoint, int explosionRange)
{
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	if (blocks[startPoint.y][startPoint.x].getType() == BlockType::BlockBush) {
		booms.push_back(make_shared<Boom>(BoomState::BoomCenter, 0.f, startPoint, true));//¼¾ÅÍ
		blocks[startPoint.y][startPoint.x].triggerDis(BLOCK_DIS_DELAY);
	}
	else booms.push_back(make_shared<Boom>(BoomState::BoomCenter, 0.f, startPoint));
	rangeCheckAndGenBoom(startPoint, -1, 0, explosionRange);//ÁÂ
	rangeCheckAndGenBoom(startPoint, 1, 0, explosionRange);	//¿ì
	rangeCheckAndGenBoom(startPoint, 0, -1, explosionRange);//»ó
	rangeCheckAndGenBoom(startPoint, 0, 1, explosionRange);	//ÇÏ


}

void BombManager::collisionBoom()
{
	for (int i = 0; i < bombs.size(); ++i) {
		for (int j = 0; j < booms.size(); ++j) {
			if (isRectRectCollision(booms[j]->getCollisionRect(), bombs[i]->getCollisionRect()))
				bombs[i]->explosionNow();
		}
	}
}
void BombManager::collisionPlayer()
{
	auto& characters = GET_SINGLE(CharacterManager)->getCharacters();
	for (auto& character : characters) {
		for (auto& boom : booms) {
			if (character->getState() != CharacterState::CharacterInBalloon) {
				if (isRectRectCollision(boom->getCollisionRect(), character->getOtherCollisionRect())) {
					character->fallDown();
				}
			}			
		}
	}
}
void BombManager::collisionItem() {
	auto& items = GET_SINGLE(ItemManager)->GetItems();
	for (auto& boom : booms) {
		for (auto it = items.begin(); it != items.end(); ) {
			if (isRectRectCollision(boom->getCollisionRect(), (*it)->getCollisionRect())) 
				it = items.erase(it);
			else ++it;
		}
	}
}