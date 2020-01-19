#pragma once
#include "CrazyArcadeClass/Obj/Item/Item.h"

class Block {
public:
	Block();
	Block(int x, int y);
	Block(BlockPosition _bPos);
	Block(BlockType _blockType, int x, int y);
	Block(BlockType _blockType, BlockPosition _bPos);
	~Block();

	void init(int x, int y);

private:
	void init();

public:
	//interface
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);
	void triggerDis(float time);
	void resetType(BlockType type);
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
	int					curBlockIdx = 0;
	
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
};

