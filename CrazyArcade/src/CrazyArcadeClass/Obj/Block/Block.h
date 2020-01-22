#pragma once
#include "CrazyArcadeClass/Obj/Item/Item.h"

class Block {
public:
	Block();
	Block(int x, int y, int _tileIdex = 0, int _blockIndex = 0);
	Block(BlockPosition _bPos, int _tileIdex = 0, int _blockIndex = 0);
	Block(BlockType _blockType, int x, int y, int _tileIdex = 0, int _blockIndex = 0);
	Block(BlockType _blockType, BlockPosition _bPos, int _tileIdex = 0, int _blockIndex = 0);
	~Block();

	void init(int x, int y);
	void init(BlockType _blockType, int x, int y, int _tileIdex = 0, int _blockIndex = 0);

private:
	void init();

public:
	//interface
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);
	void triggerDis(float time);
	void resetType(BlockType type, int _tileIdex = 0, int _blockIndex = 0);
	void release();

public:
	//getter
	IRECT& getCollisionRect() { return collisionRect; }
	BlockType getType() { return type; }
	bool isWillDis() { return willDis; }

private:
	void softToNoneBlock();

private:
	//image
	Image*				curBlockImage = nullptr;
	Image*				shawdowImage = nullptr;
	int					curBlockIdx = 0;
	int					tileIdx = 0;
	const int			innerItemCreatePer = 40;

	//inneritem
	shared_ptr<Item>	innerItem;

	//basic info
	IRECT				collisionRect;
	BlockPosition		bPos;
	BlockType			type;

	//for soft blcok destroy
	bool				willDis = false;
	float				willDisTime;
	float				willDisPastTime = 0.f;

	bool				onDis = false;
	float				onDisPastTime = 0.f;
	float				onDisTime = 0.3f;
	int					alpha = 255;

};

