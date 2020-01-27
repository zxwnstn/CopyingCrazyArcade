#include "Etc/stdafx.h"
#include "Block.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "Manager/SoundManager.h"

void Block::init(int _innerItem)
{
	if (type == BlockType::BlockSoft) {
		innerItem = nullptr;
		if (_innerItem != 3) {
			innerItem = make_shared<Item>(collisionRect, bPos, (ItemType)_innerItem);
		}
		
	}

	shawdowImage = IMAGEMANAGER->findImage("그림자");

	switch (type)
	{
	case BlockType::BlockHard:
		curBlockImage = IMAGEMANAGER->findImage("하드블록");
		break;
	case BlockType::BlockSoft:
		curBlockImage = IMAGEMANAGER->findImage("소프트블록");
		break;
	case BlockType::BlockTree:
		curBlockImage = IMAGEMANAGER->findImage("나무");
		break;
	case BlockType::BlockNone:
		curBlockImage = IMAGEMANAGER->findImage("타일");
		break;
	case BlockType::BlockBush:
		curBlockImage =	IMAGEMANAGER->findImage("부쉬");
		shawdowImage = IMAGEMANAGER->findImage("부쉬그림자");
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

void Block::init(BlockType _blockType, int x, int y, int _tileIdex, int _blockIndex) {
	
	type = _blockType;
	bPos.x = x;
	bPos.y = y;

	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);

	init();
}

void Block::init(BlockType _blockType, int x, int y, int _tileIdex, int _blockIndex, int _innerItem) {

	type = _blockType;
	bPos.x = x;
	bPos.y = y;

	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);

	init(_innerItem);
}

Block::Block()
{
}
Block::Block(int x, int y, int _tileIdex, int _blockIndex)
{
	if (x % 2 == 1 && y % 2 == 1) type = BlockType::BlockHard;
	else type = BlockType::BlockNone;

	bPos.x = x;
	bPos.y = y;

	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);

	init();
}
Block::Block(BlockPosition _bPos, int _tileIdex, int _blockIndex)
{
	if (_bPos.x % 2 == 1 && _bPos.y % 2 == 1) type = BlockType::BlockHard;
	else type = BlockType::BlockNone;

	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;

	bPos = _bPos;
	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(_bPos.x, _bPos.y);
	init();
}

Block::Block(BlockType _blockType, int x, int y, int _tileIdex, int _blockIndex)
{
	type = _blockType;
	bPos.x = x;
	bPos.y = y;
	
	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;

	collisionRect = GET_SINGLE(BlockManager)->getIRectFromIdx(x, y);
	init();
}
Block::Block(BlockType _blockType, BlockPosition _bPos, int _tileIdex, int _blockIndex)
{
	type = _blockType;
	bPos = _bPos;

	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;

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
		alpha -= 10;
		if (onDisPastTime > onDisTime) {
			softToNoneBlock();
		}
	}
}
void Block::render(HDC hdc)
{
	if (curBlockImage) {
		IMAGEMANAGER->render("타일", hdc, collisionRect.left, collisionRect.top, tileIdx * BLOCK_WIDTH, 0, 60, 60);
		
		if (type != BlockType::BlockNone && type != BlockType::BlockTree && type != BlockType::BlockBush)
			shawdowImage->alphaRender(hdc, collisionRect.left - 5, collisionRect.top + 4, 75);
		else if (type == BlockType::BlockBush)
			shawdowImage->alphaRender(hdc, collisionRect.left - 5, collisionRect.top - 19, 75);

		if (type == BlockType::BlockHard)
			curBlockImage->render(hdc, collisionRect.left, collisionRect.top + 20, curBlockIdx * BLOCK_WIDTH, 50, BLOCK_WIDTH, BLOCK_HEIGHT - 20);
		else if (type == BlockType::BlockSoft)
			curBlockImage->render(hdc, collisionRect.left, collisionRect.top + 20, curBlockIdx * BLOCK_WIDTH, 27, BLOCK_WIDTH, BLOCK_HEIGHT - 20);
		else if (type == BlockType::BlockTree)
			curBlockImage->render(hdc, collisionRect.left, collisionRect.top + 20, 0, 55, BLOCK_WIDTH, BLOCK_HEIGHT - 20);
		else if (type == BlockType::BlockBush)
			curBlockImage->render(hdc, collisionRect.left, collisionRect.top + 20, 0, 44, BLOCK_WIDTH, BLOCK_HEIGHT - 20);
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
	case BlockType::BlockBush:
		DrawColorRect(hdc, collisionRect, RGB(0, 64, 0));
		break;
	case BlockType::BlockTree:
		DrawColorRect(hdc, collisionRect, RGB(133, 125, 200));
		break;
	}
}
void Block::afterRender(HDC hdc)
{
	if (type == BlockType::BlockHard)
		curBlockImage->render(hdc, collisionRect.left, collisionRect.top - 30, curBlockIdx * BLOCK_WIDTH, 0, BLOCK_WIDTH, 50);
	else if (type == BlockType::BlockSoft)
		curBlockImage->render(hdc, collisionRect.left, collisionRect.top - 7, curBlockIdx * BLOCK_WIDTH, 0, BLOCK_WIDTH, 27);
	else if(type == BlockType::BlockTree)
		curBlockImage->render(hdc, collisionRect.left, collisionRect.top - 35, 0, 0, BLOCK_WIDTH, 55);
	else if (type == BlockType::BlockBush)
		curBlockImage->render(hdc, collisionRect.left, collisionRect.top - 24, 0, 0, BLOCK_WIDTH, 44);
}

void Block::release()
{
}

void Block::resetType(BlockType _type, int _tileIdex, int _blockIndex)
{
	type = _type;

	tileIdx = _tileIdex;
	curBlockIdx = _blockIndex;

	ItemType innerItemType = (ItemType)RND->getInt(3);
	switch (type)
	{
	case BlockType::BlockHard:
		innerItem = nullptr;
		curBlockImage = IMAGEMANAGER->findImage("하드블록");
		break;
	case BlockType::BlockSoft:
		innerItem = make_shared<Item>(collisionRect, bPos, innerItemType);
		curBlockImage = IMAGEMANAGER->findImage("소프트블록");
		break;
	case BlockType::BlockTree:
		innerItem = nullptr;
		curBlockImage = IMAGEMANAGER->findImage("나무");
		break;
	case BlockType::BlockNone:
		innerItem = nullptr;
		curBlockImage = IMAGEMANAGER->findImage("타일");
		break;
	case BlockType::BlockBush:
		innerItem = nullptr;
		curBlockImage = IMAGEMANAGER->findImage("부쉬");
	}
}

void Block::triggerDis(float time)
{
	willDis = true;
	willDisTime = time;
	if (type == BlockType::BlockBush) {
		willDisTime = 0.f;
		onDisTime = 0.f;
	}
}
void Block::softToNoneBlock()
{
	onDis = false;

	if (type == BlockType::BlockSoft) {
		if (innerItem != nullptr) {
			GET_SINGLE(ItemManager)->GetItems().push_back(innerItem);
			GET_SINGLE(SoundManager)->playSound("아이템생성", 3);
		}
	}

	type = BlockType::BlockNone;
	curBlockImage = IMAGEMANAGER->findImage("타일");

	//TODO : set innerItem push
	innerItem = nullptr;
}
