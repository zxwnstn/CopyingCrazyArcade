#include "Etc/stdafx.h"
#include "Block.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"

void Block::init()
{
	if (type == BlockType::BlockSoft) {
		innerItem = nullptr;
		innerItem = make_shared<Item>(collisionRect, bPos);
	}

	switch (type)
	{
	case BlockType::BlockHard:
		curBlockImage = IMAGEMANAGER->findImage("하드블록");
		curBlockIdx = 0;
		break;
	case BlockType::BlockSoft:
		curBlockImage = IMAGEMANAGER->findImage("소프트블록");
		curBlockIdx = 0;
		break;
	case BlockType::BlockNone:
		curBlockImage = IMAGEMANAGER->findImage("타일");
		curBlockIdx = 0;
		break;
	}
}
void Block::init(int x, int y) 
{
	if (x % 2 == 1 && y % 2 == 1) type = BlockType::BlockHard;
	else type = BlockType::BlockNone;

	bPos.x = x;
	bPos.y = y;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);
	init();
}

Block::Block()
{
}
Block::Block(int x, int y)
{
	if (x % 2 == 1 && y % 2 == 1) type = BlockType::BlockHard;
	else type = BlockType::BlockNone;

	bPos.x = x;
	bPos.y = y;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);
	init();
}
Block::Block(BlockPosition _bPos)
{
	if (_bPos.x % 2 == 1 && _bPos.y % 2 == 1) type = BlockType::BlockHard;
	else type = BlockType::BlockNone;

	bPos = _bPos;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(_bPos.x, _bPos.y);
	init();
}

Block::Block(BlockType _blockType, int x, int y)
{
	type = _blockType;
	bPos.x = x;
	bPos.y = y;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);
	init();
}
Block::Block(BlockType _blockType, BlockPosition _bPos)
{
	type = _blockType;
	bPos = _bPos;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(_bPos.x, _bPos.x);
	init();
}


Block::~Block()
{
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
		IMAGEMANAGER->render("타일", hdc, collisionRect.left, collisionRect.top, 0, 0, 60, 60);
		if(type == BlockType::BlockHard)
			//TODO : Edit 30 : this is can't be litteral
			curBlockImage->render(hdc, collisionRect.left, collisionRect.top + 20, curBlockIdx * BLOCK_WIDTH, 50, BLOCK_WIDTH, BLOCK_HEIGHT - 20);
		else if(type == BlockType::BlockSoft)
			curBlockImage->render(hdc, collisionRect.left, collisionRect.top + 20, curBlockIdx * BLOCK_WIDTH, 27, BLOCK_WIDTH, BLOCK_HEIGHT - 20);
	}
}
void Block::debugRender(HDC hdc)
{
	switch (type)
	{
	case BlockType::BlockHard:
		DrawColorRect(hdc, collisionRect, RGB(181, 239, 20));
		break;
	case BlockType::BlockSoft:
		DrawColorRect(hdc, collisionRect, RGB(0, 255, 0));
		break;
	case BlockType::BlockNone:
		DrawColorRect(hdc, collisionRect, RGB(255, 255, 255));
		break;
	}
}
void Block::afterRender(HDC hdc)
{
	if (type == BlockType::BlockHard)
		curBlockImage->render(hdc, collisionRect.left, collisionRect.top - 30, curBlockIdx * BLOCK_WIDTH, 0, BLOCK_WIDTH, 50);
	else if (type == BlockType::BlockSoft)
		curBlockImage->render(hdc, collisionRect.left, collisionRect.top - 7, curBlockIdx * BLOCK_WIDTH, 0, BLOCK_WIDTH, 27);
}
void Block::release()
{
}

void Block::resetType(BlockType _type)
{
	type = _type;
	switch (type)
	{
	case BlockType::BlockHard:
		innerItem = nullptr;
		curBlockImage = IMAGEMANAGER->findImage("하드블록");
		break;
	case BlockType::BlockSoft:
		innerItem = make_shared<Item>(collisionRect, bPos);
		curBlockImage = IMAGEMANAGER->findImage("소프트블록");
		break;
	case BlockType::BlockNone:
		innerItem = nullptr;
		curBlockImage = IMAGEMANAGER->findImage("타일");
		break;
	}
}

void Block::triggerDis(float time)
{
	willDis = true;
	willDisTime = time;
}
void Block::softToNoneBlock()
{
	onDis = false;
	type = BlockType::BlockNone;
	curBlockImage = IMAGEMANAGER->findImage("타일");

	//TODO : set innerItem push
	if (innerItem->getType() != ItemType::ItemNone)
		GET_SINGLE(ItemManager)->GetItems().push_back(innerItem);
	innerItem = nullptr;
}
