#include "character.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include <iostream>

//init
character::character() 
{
}
character::character(int x, int y)
{
	pos.x = BLOCK_WIDTH / 2 + x * BLOCK_WIDTH + MAPOFFSET_X;
	pos.y = BLOCK_HEIGHT / 2 + y * BLOCK_HEIGHT + MAPOFFSET_Y;

	bPos = BlockPosition(x, y);

	//set your character ablility	

	rectSetFromPos();

	state = CharacterState::CharacterOnIdle;
}
character::~character()
{
}
void character::rectSetFromPos()
{
	blockCollisionRect.left = pos.x - BLOCK_WIDTH / 2;
	blockCollisionRect.right = pos.x + BLOCK_WIDTH / 2;
	blockCollisionRect.bottom = pos.y + BLOCK_HEIGHT / 2;
	blockCollisionRect.top = pos.y - BLOCK_HEIGHT / 2;

	otherCollisionRect.left = pos.x - BLOCK_WIDTH / 2 + xMargin;
	otherCollisionRect.right = pos.x + BLOCK_WIDTH / 2 - xMargin;
	otherCollisionRect.bottom = pos.y + BLOCK_HEIGHT / 2 - yMargin;
	otherCollisionRect.top = pos.y - BLOCK_HEIGHT / 2 + yMargin;
}

//render
void character::render(HDC hdc) {
	IMAGEMANAGER->render("플레이어", hdc, pos.x - BLOCK_WIDTH / 2 + 3, pos.y - BLOCK_HEIGHT / 2);
}
void character::debugRender(HDC hdc)
{
	if (state == CharacterState::CharacterDead) {
		DrawColorRect(hdc, blockCollisionRect, RGB(0, 0, 0));
		return;
	}
	if (state != CharacterState::CharacterInBalloon) {
		DrawColorRect(hdc, blockCollisionRect, RGB(16, 248, 238));
		DrawColorRect(hdc, otherCollisionRect, RGB(255, 0, 0));
	}
	else if (state == CharacterState::CharacterInBalloon)
		DrawColorRect(hdc, blockCollisionRect, RGB(18, 67, 197));
}

//move
Direction character::move(Direction dir, int dist)
{
	switch (dir)
	{
	//UP move can be change Right or Left
	case eUp:
		dist = adjustSpeed(eUp);
		blockCollisionRect.moveUp(dist);
		dir = isCanMove(eDown, dir);
	//no need change
		if (dir == eMove) {
			pos.y -= dist;
			otherCollisionRect.moveUp(dist);
			return eUp;
		}

	//need change
		blockCollisionRect.moveDown(dist);
		//Left change
		if (dir == eLeft) {
			dist = adjustSpeed(eLeft);
			blockCollisionRect.moveLeft(dist);
			otherCollisionRect.moveLeft(dist);
			pos.x -= dist;
			return eLeft;
		}
		//Right change
		if (dir == eRight) {
			dist = adjustSpeed(eRight);
			blockCollisionRect.moveRight(dist);
			otherCollisionRect.moveRight(dist);
			pos.x += dist;
			return eRight;
		}
		return eNoMove;

	//Down Move can be change Right or Left
	case eDown:
		dist = adjustSpeed(eDown);
		blockCollisionRect.moveDown(dist);
		dir = isCanMove(eDown, dir);
	//No need change
		if (dir == eMove) {
			pos.y += dist;
			otherCollisionRect.moveDown(dist);
			return eDown;
		}

	//need Change
		blockCollisionRect.moveUp(dist);
		//Right
		if (dir == eLeft) {
			dist = adjustSpeed(eLeft);
			blockCollisionRect.moveLeft(dist);
			otherCollisionRect.moveLeft(dist);
			pos.x -= dist;
			return eLeft;
		}
		//Left
		if (dir == eRight) {
			dist = adjustSpeed(eRight);
			blockCollisionRect.moveRight(dist);
			otherCollisionRect.moveRight(dist);
			pos.x += dist;
			return eRight;
		}
		return eNoMove;

	//Right Move can be change Up or Down
	case eRight:
		dist = adjustSpeed(eRight);
		blockCollisionRect.moveRight(dist);
		dir = isCanMove(eRight, dir);
	//No need change
		if (dir == eMove) {
			pos.x += dist;
			otherCollisionRect.moveRight(dist);
			return eRight;
		}

	//need change
		blockCollisionRect.moveLeft(dist);
		//Up change
		if (dir == eUp) {
			dist = adjustSpeed(eUp);
			blockCollisionRect.moveUp(dist);
			otherCollisionRect.moveUp(dist);
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if (dir == eDown) {
			dist = adjustSpeed(eDown);
			blockCollisionRect.moveDown(dist);
			otherCollisionRect.moveDown(dist);
			pos.y += dist;
			return eDown;
		}
		return eNoMove;

	//Left Move can be change Up or Down
	case eLeft:
		dist = adjustSpeed(eLeft);
		blockCollisionRect.moveLeft(dist);
		dir = isCanMove(eLeft, dir);
		//no need change
		if (dir == eMove) {
			pos.x -= dist;
			otherCollisionRect.moveLeft(dist);
			return eLeft;
		}

		//need change
		blockCollisionRect.moveRight(dist);
		//Up change
		if (dir == eUp) {
			dist = adjustSpeed(eUp);
			blockCollisionRect.moveUp(dist);
			otherCollisionRect.moveUp(dist);
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if (dir == eDown) {
			dist = adjustSpeed(eDown);
			blockCollisionRect.moveDown(dist);
			otherCollisionRect.moveDown(dist);
			pos.y += dist;
			return eDown;
		}
		return eNoMove;
	}
}
Direction character::isCanMove(Direction dir, Direction originDir)
{
	if (blockCollisionRect.left < MAPOFFSET_X || blockCollisionRect.right > MAPOFFSET_X + NUM_BLOCK_X * BLOCK_WIDTH ||
		blockCollisionRect.top < MAPOFFSET_Y || blockCollisionRect.bottom > MAPOFFSET_Y + NUM_BLOCK_Y * BLOCK_HEIGHT) {
		return eNoMove;
	}

	//check collision bomb
	auto& bombs = GET_SINGLE(BombManager)->GetBombs();
	for (auto it = bombs.begin(); it != bombs.end(); ++it) {
		IRECT temp = (*it)->getCollisionRect();
		if (isRectRectCollision(blockCollisionRect, temp)) {
			//sequence bomb handle
			if (temp == prevDorp_rect && isSequenceDrop) {
				auto temp2 = prevDorp_rect - lastDrop_rect;
				int dx = temp2.first;
				int dy = temp2.second;
				if (dx == 1 && originDir == eRight)
					return eNoMove;
				if (dx == -1 && originDir == eLeft)
					return eNoMove;
				if (dy == -1 && originDir == eUp)
					return eNoMove;
				if (dy == 1 && originDir == eDown)
					return eNoMove;
			}
			//if character in drop area can move any direction
			if (isDropBombArea) {
				continue;
			}
			if (dir == eUp || dir == eDown) {
				if (temp.left < blockCollisionRect.left)
					return eRight;
				if (blockCollisionRect.right < temp.right)
					return eLeft;
			}
			if (dir == eLeft || dir == eRight) {
				if (temp.bottom < blockCollisionRect.bottom)
					return eDown;
				if (blockCollisionRect.top < temp.top)
					return eUp;
			}
			return eNoMove;
		}
	}

	//check collision with block
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			IRECT temp = blocks[i][j].getCollisionRect();
			if (blocks[i][j].getType() != BlockType::BlockNone &&
				isRectRectCollision(temp, blockCollisionRect)) {
				if (dir == eUp || dir == eDown) {
					if (temp.left < blockCollisionRect.left)
						return eRight;
					if (blockCollisionRect.right < temp.right)
						return eLeft;
				}
				if (dir == eLeft || dir == eRight) {
					if (temp.bottom < blockCollisionRect.bottom)
						return eDown;
					if (blockCollisionRect.top < temp.top)
						return eUp;
				}
				return eNoMove;
			}
		}
	}

	return eMove;
}
int character::adjustSpeed(Direction dir)
{
	int ret = speed;
	switch (dir)
	{
	case eUp:
		while ((blockCollisionRect.bottom - MAPOFFSET_Y - ret) % speed != 0)
			--ret;
		break;
	case eDown:
		while ((blockCollisionRect.bottom - MAPOFFSET_Y + ret) % speed != 0)
			--ret;
		break;
	case eRight:
		while ((blockCollisionRect.left - MAPOFFSET_X + ret) % speed != 0)
			--ret;
		break;
	case eLeft:
		while ((blockCollisionRect.right - MAPOFFSET_X - ret) % speed != 0)
			--ret;
		break;
	}
	return ret;
}
void character::stayDropArea()
{
	if (!isRectRectCollision(blockCollisionRect, lastDrop_rect)) {
		prevDorp_rect.reset();
		lastDrop_rect.reset();
		isDropBombArea = false;
	}
}


//state
void character::dropBomb()
{
	if (bombLimit > curBombList.size()) {

		shared_ptr<Bomb> newBomb = make_shared<Bomb>(pos, bombRange);

		prevDorp_rect = lastDrop_rect;
		lastDrop_rect = newBomb->getCollisionRect();
		lastDrop_rect.setBpos();

		if (!(lastDrop_rect == prevDorp_rect)) {
			curBombList.push_back(newBomb);
			GET_SINGLE(BombManager)->GetBombs().push_back(newBomb);
			checkSequenceDrop();
			isDropBombArea = true;
		}		
	}
}
void character::checkSequenceDrop()
{
	auto ret = lastDrop_rect - prevDorp_rect;
	int dx = ret.first;
	int dy = ret.second;
	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	if ((dx + dy) == 1) {
		isSequenceDrop =  true;
		return;
	}
	isSequenceDrop = false;
}
void character::fallDown()
{
	state = CharacterState::CharacterInBalloon;

}
void character::die()
{
	state = CharacterState::CharacterDead;
}
