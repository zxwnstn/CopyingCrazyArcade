#include "Etc/stdafx.h"
#include "Block.h"
#include "HomeWorkClass/Manager/ItemManager.h"
void Block::softToNoneBlock()
{
	onDis = false;
	type = BlockType::BlockNone;
	curBlockImage = nullptr;

	//TODO : set innerItem push
	if(innerItem->getType() != ItemType::ItemNone)
		GET_SINGLE(ItemManager)->push_Item(innerItem);
}


Block::Block()
{
}


Block::~Block()
{
}

bool Block::init(int x, int y)
{
	//temporary
	if (x % 2 == 1 && y % 2 == 1) type = BlockType::BlockHard;
	else type = BlockType::BlockNone;

	pos.x = x * BLOCK_WIDTH;
	pos.y = y * BLOCK_HEIGHT;
	rect = RectMake(x * BLOCK_WIDTH, y * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);

	if(type == BlockType::BlockSoft)
		innerItem = make_shared<Item>(rect, pos);


	return true;
}

void Block::update(float deltaTime)
{
	if (willDis) {
		willDisPastTime += deltaTime;
		if (willDisPastTime > willDisTime) {
			onDis = true;
			willDis = false;
		}
	}
	if (onDis) {		
		onDisPastTime += deltaTime;
		if (onDisPastTime > onDisTime) {
			softToNoneBlock();
		}
	}
}

void Block::render(HDC hdc)
{
	if (curBlockImage) {
		switch (type)
		{
		case BlockType::BlockHard:
			break;
		case BlockType::BlockSoft:
			break;
		case BlockType::BlockNone:
			break;
		}
	}
}

void Block::debugRender(HDC hdc)
{
	switch (type)
	{
	case BlockType::BlockHard:
		DrawColorRect(hdc, rect, RGB(181, 239, 20));
		break;
	case BlockType::BlockSoft:
		DrawColorRect(hdc, rect, RGB(0, 255, 0));
		break;
	case BlockType::BlockNone:
		DrawColorRect(hdc, rect, RGB(255, 255, 255));
		break;
	}
}

void Block::triggerDis(float time)
{
	willDis = true;
	willDisTime = time;
}

void Block::resetType(BlockType _type)
{
	type = _type;
	//TODO : image
	switch (type)
	{
	case BlockType::BlockHard:
		break;
	case BlockType::BlockSoft:
		innerItem = make_shared<Item>(rect, pos);
		//break;
	case BlockType::BlockNone:
		break;
	}
}

void Block::release()
{
}
