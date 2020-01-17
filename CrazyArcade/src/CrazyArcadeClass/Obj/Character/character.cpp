#include "character.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"

//init
character::character()
{
	lastBlockPos = { -1, -1 };
	prevLastBlcokPos = { -1,  -1 };
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
		blockCollisionRect.top -= dist;
		blockCollisionRect.bottom -= dist;
		dir = isCanMove(eDown);

		//no need change
		if (dir == eMove) {
			pos.y -= dist;
			otherCollisionRect.bottom -= dist;
			otherCollisionRect.top -= dist;
			return eUp;
		}

		//need change
		blockCollisionRect.top += dist;
		blockCollisionRect.bottom += dist;
		//Left change
		if (dir == eLeft) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eLeft);
				needSpeedAdjust = false;
			}
			blockCollisionRect.left -= dist;
			blockCollisionRect.right -= dist;
			otherCollisionRect.left -= dist;
			otherCollisionRect.right -= dist;
			pos.x -= dist;
			return eLeft;
		}
		//Right change
		if (dir == eRight) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eRight);
				needSpeedAdjust = false;
			}
			blockCollisionRect.left += dist;
			blockCollisionRect.right += dist;
			otherCollisionRect.left += dist;
			otherCollisionRect.right += dist;
			pos.x += dist;
			return eRight;
		}	
		return eNoMove;
	
	//Down Move can be change Right or Left
	case eDown:
		blockCollisionRect.top += dist;
		blockCollisionRect.bottom += dist;
		dir = isCanMove(eDown);

		//No need change
		if (dir == eMove) {
			pos.y += dist;
			otherCollisionRect.top += dist;
			otherCollisionRect.bottom += dist;
			return eDown;
		}

		//need Change
		blockCollisionRect.top -= dist;
		blockCollisionRect.bottom -= dist;
		//Right
		if (dir == eLeft) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eLeft);
				needSpeedAdjust = false;
			}
			blockCollisionRect.left -= dist;
			blockCollisionRect.right -= dist;
			otherCollisionRect.left -= dist;
			otherCollisionRect.right -= dist;
			pos.x -= dist;
			return eLeft;
		}
		//Left
		if (dir == eRight) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eRight);
				needSpeedAdjust = false;
			}
			blockCollisionRect.left += dist;
			blockCollisionRect.right += dist;
			otherCollisionRect.left += dist;
			otherCollisionRect.right += dist;
			pos.x += dist;
			return eRight;
		}		
		return eNoMove;

	//Right Move can be change Up or Down
	case eRight:

		blockCollisionRect.left += dist;
		blockCollisionRect.right += dist;
		dir = isCanMove(eRight);
		
		//No need change
		if (dir == eMove) {
			pos.x += dist;
			otherCollisionRect.left += dist;
			otherCollisionRect.right += dist;
			return eRight;
		}

		//need change
		blockCollisionRect.left -= dist;
		blockCollisionRect.right -= dist;
		//Up change
		if (dir == eUp) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eUp);
				needSpeedAdjust = false;
			}
			blockCollisionRect.top -= dist;
			blockCollisionRect.bottom -= dist;
			otherCollisionRect.top -= dist;
			otherCollisionRect.bottom -= dist;
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if (dir == eDown) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eDown);
				needSpeedAdjust = false;
			}
			blockCollisionRect.top += dist;
			blockCollisionRect.bottom += dist;
			otherCollisionRect.top += dist;
			otherCollisionRect.bottom += dist;
			pos.y += dist;
			return eDown;
		}
		return eNoMove;

	//Left Move can be change Up or Down
	case eLeft:
		blockCollisionRect.left -= dist;
		blockCollisionRect.right -= dist;
		dir = isCanMove(eLeft);

		//no need change
		if (dir == eMove) {
			pos.x -= dist;
			otherCollisionRect.left -= dist;
			otherCollisionRect.right -= dist;
			return eLeft;
		}

		//need change
		blockCollisionRect.left += dist;
		blockCollisionRect.right += dist;
		//Up change
		if (dir == eUp) {
			if (needSpeedAdjust) {
				dist = adjustSpeed(eUp);
				needSpeedAdjust = false;
			}
			blockCollisionRect.top -= dist;
			blockCollisionRect.bottom -= dist;
			otherCollisionRect.top -= dist;
			otherCollisionRect.bottom -= dist;
			pos.y -= dist;
			return eUp;
		}
		//Down change
		if(dir == eDown){
			if (needSpeedAdjust) {
				dist = adjustSpeed(eDown);
				needSpeedAdjust = false;
			}
			blockCollisionRect.top += dist;
			blockCollisionRect.bottom += dist;
			otherCollisionRect.top += dist;
			otherCollisionRect.bottom += dist;
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

	/*auto& bombs = GET_SINGLE(BombManager)->GetBombs();
	for (int i = 0; i < bombs.size(); ++i) {
		if (lastBlockPos == bombs[i]->getPos())
			continue;
		else if (isRectRectCollision(bombs[i]->getRect(), rect))
			return false;
	}*/

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

		lastBlockPos = newBomb->getPos();
		dropAndMoveRect = IRectMake(
			lastBlockPos.x * BLOCK_WIDTH + MAPOFFSET_X,
			lastBlockPos.y * BLOCK_HEIGHT + MAPOFFSET_Y,
			BLOCK_WIDTH, BLOCK_HEIGHT
		);

		curBombList.push_back(newBomb);
		GET_SINGLE(BombManager)->GetBombs().push_back(newBomb);
	}


}
void character::fallDown()
{
	state = CharacterState::CharacterInBalloon;

}