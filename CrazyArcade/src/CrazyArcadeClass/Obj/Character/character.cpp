#include "character.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "Manager/SoundManager.h"
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

	state = CharacterState::CharacterOnDownMove;
	state |= CharacterState::CharacterNoMove;
	prevState = state;
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
void character::render(HDC hdc) 
{
	if (!inBush) {
		if (state & CharacterState::CharacterOnMove) {
			if (state == prevState) {
				if (state & CharacterState::CharacterOnDownMove) {
					frameCounter += deltaTime;
					if (frameCounter > frameChageTimer) {
						frameIndex++;
						frameCounter = 0.f;
						if (frameIndex > moveImage->getMaxFrameX())
							frameIndex = 0;
					}
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 0);
				}
				if (state & CharacterState::CharacterOnUpMove) {
					frameCounter += deltaTime;
					if (frameCounter > frameChageTimer) {
						frameIndex++;
						frameCounter = 0.f;
						if (frameIndex > moveImage->getMaxFrameX())
							frameIndex = 0;
					}
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 1);
				}
				if (state & CharacterState::CharacterOnLeftMove) {
					frameCounter += deltaTime;
					if (frameCounter > frameChageTimer) {
						frameIndex++;
						frameCounter = 0.f;
						if (frameIndex > moveImage->getMaxFrameX())
							frameIndex = 0;
					}
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 2);
				}
				if (state & CharacterState::CharacterOnRightMove) {
					frameCounter += deltaTime;
					if (frameCounter > frameChageTimer) {
						frameIndex++;
						frameCounter = 0.f;
						if (frameIndex > moveImage->getMaxFrameX())
							frameIndex = 0;
					}
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 3);
				}
			}
			else {
				if (state & CharacterState::CharacterOnDownMove) {
					frameIndex = 0;
					frameCounter = 0.f;
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 0);
				}
				if (state & CharacterState::CharacterOnUpMove) {
					frameIndex = 0;
					frameCounter = 0.f;
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 1);
				}
				if (state & CharacterState::CharacterOnLeftMove) {
					frameIndex = 0;
					frameCounter = 0.f;
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 2);
				}
				if (state & CharacterState::CharacterOnRightMove) {
					frameIndex = 0;
					frameCounter = 0.f;
					moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 3);
				}
			}
		}
		if (state & CharacterState::CharacterNoMove) {
			if (state & CharacterState::CharacterOnDownMove) {
				moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 0);
			}
			if (state & CharacterState::CharacterOnUpMove) {
				moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 1);
			}
			if (state & CharacterState::CharacterOnLeftMove) {
				moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 2);
			}
			if (state & CharacterState::CharacterOnRightMove) {
				moveImage->frameRender(hdc, blockCollisionRect.left - 10, blockCollisionRect.top - 10, frameIndex, 3);
			}
		}

		if (state & CharacterInBalloon) {
			frameCounter += deltaTime;
			if (frameCounter > frameInballoonTimer) {
				frameCounter = 0;
				frameIndex++;
				if (frameIndex > inBalloonImage->getMaxFrameX())
					frameIndex = inBalloonImage->getMaxFrameX();
			}
			inBalloonImage->frameRender(hdc, blockCollisionRect.left, blockCollisionRect.top, frameIndex, 0);
		}

		if (state & CharacterDead && !playerDead) {
			frameCounter += deltaTime;
			if (frameCounter > frameDyingTimer) {
				frameCounter = 0;
				frameIndex++;
				if (frameIndex > deadImage->getMaxFrameX()) {
					playerDead = true;
					frameIndex = deadImage->getMaxFrameX();
				}
			}
			deadImage->frameRender(hdc, blockCollisionRect.left - 3, blockCollisionRect.top - BLOCK_HEIGHT, frameIndex, 0);
		}
		else if (playerDead) {
			deadImage->frameRender(hdc, blockCollisionRect.left - 3, blockCollisionRect.top - BLOCK_HEIGHT, frameIndex, 0);
		}
	}

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

void character::afterRender(HDC hdc)
{
	/*if (!inBush) {
		if(characterPointer)
			characterPointer->render(hdc, blockCollisionRect.left + 20, blockCollisionRect.top - 55);
	}*/
}

//move
Direction character::move(Direction dir, int dist)
{
	switch (dir)
	{
	//UP move can be change Right or Left
	case eUp:


		if(!adjustSpeedVertical)
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
			if (!adjustSpeedHorizen)
				dist = adjustSpeed(eLeft);
			blockCollisionRect.moveLeft(dist);
			otherCollisionRect.moveLeft(dist);
			pos.x -= dist;
			return eLeft;
		}
		//Right change
		if (dir == eRight) {
			if (!adjustSpeedHorizen)
				dist = adjustSpeed(eRight);
			blockCollisionRect.moveRight(dist);
			otherCollisionRect.moveRight(dist);
			pos.x += dist;
			return eRight;
		}
		return eNoMove;

	//Down Move can be change Right or Left
	case eDown:
		if (!adjustSpeedVertical)
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
			if (!adjustSpeedHorizen)
				dist = adjustSpeed(eLeft);
			blockCollisionRect.moveLeft(dist);
			otherCollisionRect.moveLeft(dist);
			pos.x -= dist;
			return eLeft;
		}
		//Left
		if (dir == eRight) {
			if (!adjustSpeedHorizen)
				dist = adjustSpeed(eRight);
			blockCollisionRect.moveRight(dist);
			otherCollisionRect.moveRight(dist);
			pos.x += dist;
			return eRight;
		}
		return eNoMove;

	//Right Move can be change Up or Down
	case eRight:
		if (!adjustSpeedHorizen)
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
			if (!adjustSpeedVertical)
				dist = adjustSpeed(eUp);
			blockCollisionRect.moveUp(dist);
			otherCollisionRect.moveUp(dist);
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if (dir == eDown) {
			if (!adjustSpeedVertical)
				dist = adjustSpeed(eDown);
			blockCollisionRect.moveDown(dist);
			otherCollisionRect.moveDown(dist);
			pos.y += dist;
			return eDown;
		}
		return eNoMove;

	//Left Move can be change Up or Down
	case eLeft:
		if (!adjustSpeedHorizen)
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
			if (!adjustSpeedVertical)
				dist = adjustSpeed(eUp);
			blockCollisionRect.moveUp(dist);
			otherCollisionRect.moveUp(dist);
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if (dir == eDown) {
			if (!adjustSpeedVertical)
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
			if ((blocks[i][j].getType() != BlockType::BlockNone && blocks[i][j].getType() != BlockType::BlockBush) &&
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
		adjustSpeedVertical = true;
		break;
	case eDown:
		while ((blockCollisionRect.bottom - MAPOFFSET_Y + ret) % speed != 0)
			--ret;
		adjustSpeedVertical = true;
		break;
	case eRight:
		while ((blockCollisionRect.left - MAPOFFSET_X + ret) % speed != 0)
			--ret;
		adjustSpeedHorizen = true;
		break;
	case eLeft:
		while ((blockCollisionRect.right - MAPOFFSET_X - ret) % speed != 0)
			--ret;
		adjustSpeedHorizen = true;
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
			bool isInBomb = false;
			auto& bombs = GET_SINGLE(BombManager)->GetBombs();
			for (auto it = bombs.begin(); it != bombs.end(); ++it) {
				if (lastDrop_rect == (*it)->getCollisionRect()) {
					isInBomb = true;
					break;
				}
			}
			if (isInBomb) return;

			auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
			if (blocks[lastDrop_rect.bPos_y][lastDrop_rect.bPos_x].getType() == BlockType::BlockBush)
				newBomb->setInBush();

			auto& characters = GET_SINGLE(CharacterManager)->getCharacters();
			for (auto character = characters.begin(); character != characters.end(); ++ character) {
				if ((*character).get() == this)
					continue;
				if (isRectRectCollision(lastDrop_rect, (*character)->getBlockCollisionRect()))
					(*character)->setDropArea(lastDrop_rect);
			}

			GET_SINGLE(SoundManager)->playSound("폭탄놓기", 4);
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
	GET_SINGLE(SoundManager)->playSound("풍선갖히기", 5);
	state = CharacterState::CharacterInBalloon;
	frameIndex = 0;
	frameCounter = 0;
}
void character::die()
{
	GET_SINGLE(SoundManager)->playSound("풍선폭발", 1);
	state = CharacterState::CharacterDead;
	frameIndex = 0;
	frameCounter = 0;
}

bool character::isInBush()
{
	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			if (blocks[i][j].getType() == BlockType::BlockBush &&
				isRectRectCollision(blocks[i][j].getCollisionRect(), otherCollisionRect)) {
				if (inBush == false)
					GET_SINGLE(SoundManager)->playSound("부쉬들어가기", 6);
				return true;
			}
	return false;
}

void character::setDropArea(IRECT oppentsBombRect)
{
	prevDorp_rect = lastDrop_rect;
	lastDrop_rect = oppentsBombRect;
	isDropBombArea = true;
}


//item get

void character::speedUp() 
{ 
	if (speed < 6) {
		adjustSpeedHorizen = false;
		adjustSpeedVertical = false;
		speed++; 
	}
}

