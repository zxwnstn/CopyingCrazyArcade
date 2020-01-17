#include "character.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include <iostream>

//init
character::character()
{
	resetDropPos();
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
Direction character::move(Direction dir, int dist)
{
	switch (dir)
	{
	//UP move can be change Right or Left
	case eUp:
		blockCollisionRect.moveUp(dist);
		dir = isCanMove(eDown);

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
			if (needSpeedAdjust) {
				dist = adjustSpeed(eLeft);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveLeft(dist);
			otherCollisionRect.moveLeft(dist);
			pos.x -= dist;
			return eLeft;
		}
		//Right change
		if (dir == eRight) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eRight);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveRight(dist);
			otherCollisionRect.moveRight(dist);
			pos.x += dist;
			return eRight;
		}	
		return eNoMove;
	
	//Down Move can be change Right or Left
	case eDown:
		blockCollisionRect.moveDown(dist);
		dir = isCanMove(eDown);

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
			if (needSpeedAdjust) {
				dist = adjustSpeed(eLeft);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveLeft(dist);
			otherCollisionRect.moveLeft(dist);
			pos.x -= dist;
			return eLeft;
		}
		//Left
		if (dir == eRight) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eRight);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveRight(dist);
			otherCollisionRect.moveRight(dist);
			pos.x += dist;
			return eRight;
		}		
		return eNoMove;

	//Right Move can be change Up or Down
	case eRight:
		blockCollisionRect.moveRight(dist);
		dir = isCanMove(eRight);
		
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
			if (needSpeedAdjust) {
				dist = adjustSpeed(eUp);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveUp(dist);
			otherCollisionRect.moveUp(dist);
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if (dir == eDown) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eDown);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveDown(dist);
			otherCollisionRect.moveDown(dist);
			pos.y += dist;
			return eDown;
		}
		return eNoMove;

	//Left Move can be change Up or Down
	case eLeft:
		blockCollisionRect.moveLeft(dist);
		dir = isCanMove(eLeft);

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
			if (needSpeedAdjust) {
				dist = adjustSpeed(eUp);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveUp(dist);
			otherCollisionRect.moveUp(dist);
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if(dir == eDown){
			if (needSpeedAdjust) {
				dist = adjustSpeed(eDown);
				needSpeedAdjust = false;
			}
			blockCollisionRect.moveDown(dist);
			otherCollisionRect.moveDown(dist);
			pos.y += dist;
			return eDown;
		}		
		return eNoMove;
	}
}
Direction character::isCanMove(Direction dir)
{
	if (blockCollisionRect.left < MAPOFFSET_X || blockCollisionRect.right > MAPOFFSET_X + NUM_BLOCK_X * BLOCK_WIDTH ||
		blockCollisionRect.top < MAPOFFSET_Y || blockCollisionRect.bottom > MAPOFFSET_Y + NUM_BLOCK_Y * BLOCK_HEIGHT) {
		return eNoMove;
	}

	auto& bombs = GET_SINGLE(BombManager)->GetBombs();
	for (auto it = bombs.begin(); it != bombs.end(); ++it) {
		IRECT temp = (*it)->getCollisionRect();
		auto bombPos = (*it)->getPos();
		if (isDropBombArea) {
			continue;
		}

		if (isRectRectCollision(temp, blockCollisionRect)) {
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


//state
void character::dropBomb()
{
	if (bombLimit > curBombList.size()) {

		shared_ptr<Bomb> newBomb = make_shared<Bomb>(pos, bombRange);

		prevDrop_bPos = lastDrop_bPos;
		lastDrop_bPos = newBomb->getPos();
		lastDrop_rect = GET_SINGLE(BlockManager)->getIRectFromIdx(lastDrop_bPos.x, lastDrop_bPos.y);


		curBombList.push_back(newBomb);
		GET_SINGLE(BombManager)->GetBombs().push_back(newBomb);

		isDropBombArea = true;
	}


}
void character::updateBlcokPosition()
{

	int x = (pos.x - MAPOFFSET_X) / BLOCK_WIDTH;
	int y = (pos.y - MAPOFFSET_Y) / BLOCK_HEIGHT;
	if ((bPos.x != x || bPos.y != y)) {
		bPos.x = x;
		bPos.y = y;
		//cout << "get Log" << endl;
		//cout << bPos.x << " " << bPos.y << endl;
		//cout << lastDrop_bPos.x << " " << lastDrop_bPos.y << endl;
		//cout << prevDrop_bPos.x << " " << prevDrop_bPos.y << endl;
		
		if (!isRectRectCollision(blockCollisionRect, lastDrop_rect)) {
	 		isDropBombArea = false;
		}
	}
}
void character::resetDropPos()
{ 
  	lastDrop_bPos = { -1, -1 };
	prevDrop_bPos = { -1, -1 };
}
void character::fallDown()
{
	state = CharacterState::CharacterInBalloon;

}