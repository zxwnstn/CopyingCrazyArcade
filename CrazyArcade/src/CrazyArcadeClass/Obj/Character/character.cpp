#include "character.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"

void character::move(Direction dir, float dist)
{
	switch (dir)
	{
	case eUp:
		rect.top -= dist;
		rect.bottom -= dist;
		if (isCanMove())
			pos.y -= dist;
		else {
			rect.top += dist;
			rect.bottom += dist;
		}
		return;
	case eDown:
		rect.top += dist;
		rect.bottom += dist;
		if (isCanMove())
			pos.y += dist;
		else {
			rect.top -= dist;
			rect.bottom -= dist;
		}
		return;
	case eRight:
		rect.left += dist;
		rect.right += dist;
		if (isCanMove())
			pos.x += dist;
		else {
			rect.left -= dist;
			rect.right -= dist;
		}
		return;
	case eLeft:
		rect.left -= dist;
		rect.right -= dist;
		if (isCanMove())
			pos.x -= dist;
		else {
			rect.left += dist;
			rect.right += dist;
		}
		return;
	}
}

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

bool character::isCanMove()
{
	if (rect.left < MAPOFFSET_X || rect.right > MAPOFFSET_X + NUM_BLOCK_X * BLOCK_WIDTH || 
		rect.top < MAPOFFSET_Y || rect.bottom > MAPOFFSET_Y + NUM_BLOCK_Y * BLOCK_HEIGHT) {
		return false;
	}

	auto& bombs = GET_SINGLE(BombManager)->GetBombs();
	for (int i = 0; i < bombs.size(); ++i) {
		if (lastBlockPos == bombs[i]->getPos())
			continue;
		else if (isRectRectCollision(bombs[i]->getRect(), rect))
			return false;
	}

	auto& blocks = GET_SINGLE(BlockManager)->GetBlocks();
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			if(blocks[i][j].getType() != BlockType::BlockNone && 
				isRectRectCollision(blocks[i][j].getRect(), rect))
				return false;
		}
	}

	return true;
}
