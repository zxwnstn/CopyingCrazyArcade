#include "character.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"


void character::checkGetItem()
{
	auto& items = GET_SINGLE(ItemManager)->GetItems();
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
				usableItemList[(int)ItemType::ItemKick] = true;
				break;
			case ItemType::ItemDart:
				usableItemList[(int)ItemType::ItemDart] = true;
				break;
			case ItemType::ItemNone:
				break;
			}
			it = items.erase(it);
		}
		else ++it;
	}
}

void character::fallDown()
{
	state = CharacterState::CharacterInBalloon;
}

Direction character::move(Direction dir, int dist)
{
	switch (dir)
	{
	case eUp:
		rect.top -= dist;
		rect.bottom -= dist;
		dir = isCanMove(eDown);

		if (dir == eMove) {
			pos.y -= dist;
			return eUp;
		}

		rect.top += dist;
		rect.bottom += dist;
		if (dir == eLeft) {
			rect.left -= dist;
			rect.right -= dist;
			pos.x -= dist;
			return eLeft;
		}
		else if (dir == eRight) {
			rect.left += dist;
			rect.right += dist;
			pos.x += dist;
			return eLeft;
		}	
		return eNoMove;



	case eDown:
		rect.top += dist;
		rect.bottom += dist;
		dir = isCanMove(eDown);

		if (dir == eMove) {
			pos.y += dist;
			return eDown;
		}

		rect.top -= dist;
		rect.bottom -= dist;
		if (dir == eLeft) {
			rect.left -= dist;
			rect.right -= dist;
			pos.x -= dist;
			return eLeft;
		}
		else if (dir == eRight) {
			rect.left += dist;
			rect.right += dist;
			pos.x += dist;
			return eRight;
		}		
		return eNoMove;
	case eRight:
		rect.left += dist;
		rect.right += dist;
		dir = isCanMove(eRight);

		if (dir == eMove) {
			pos.x += dist;
			return eRight;
		}

		rect.left -= dist;
		rect.right -= dist;
		if (dir == eUp) {
			rect.top -= dist;
			rect.bottom -= dist;
			pos.y -= dist;
			return eUp;
		}
		else if (dir == eDown) {
			rect.top += dist;
			rect.bottom += dist;
			pos.y += dist;
			return eDown;
		}
		return eNoMove;
	case eLeft:
		rect.left -= dist;
		rect.right -= dist;
		dir = isCanMove(eLeft);

		if (dir == eMove) {
			pos.x -= dist;
			return eLeft;
		}

		rect.left += dist;
		rect.right += dist;
		if (dir == eUp) {
			rect.top -= dist;
			rect.bottom -= dist;
			pos.y -= dist;
			return eSlipUp;
		}
		else if(dir == eDown){
			rect.top += dist;
			rect.bottom += dist;
			pos.y += dist;
			return eSlipDown;
		}		
		return eNoMove;
	}
}

Direction character::isCanMove(Direction dir)
{
	if (rect.left < MAPOFFSET_X || rect.right > MAPOFFSET_X + NUM_BLOCK_X * BLOCK_WIDTH || 
		rect.top < MAPOFFSET_Y || rect.bottom > MAPOFFSET_Y + NUM_BLOCK_Y * BLOCK_HEIGHT) {
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
			RECT temp = blocks[i][j].getRect();
			if (blocks[i][j].getType() != BlockType::BlockNone &&
				isRectRectCollision(temp, rect)) {
				if (dir == eUp || dir == eDown) {
					if (temp.left < rect.left)
						return eRight;
					if (rect.right < temp.right)
						return eLeft;
				}
				if (dir == eLeft || dir == eRight) {
					if (temp.bottom < rect.bottom)
						return eDown;
					if (rect.top < temp.top)
						return eUp;
				}
				return eNoMove;
			}
		}
	}

	return eMove;
}
