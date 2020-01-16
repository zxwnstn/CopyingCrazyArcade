#pragma once
#include "HomeWorkClass/Obj/Item/Item.h"

class Block
{
private:
	void softToNoneBlock();

public:
	Block();
	~Block();

	bool init(int x, int y);
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void triggerDis(float time);
	void resetType(BlockType type);
	RECT& getRect() { return rect; }
	BlockType getType() { return type; }

	void release();

private:
	Image*				curBlockImage = nullptr;
	shared_ptr<Item>	innerItem = nullptr;
	BlockType			type;
	RECT				rect;
	BlockPosition		pos;

	//soft blcok ªË¡¶
	bool				willDis = false;
	float				willDisTime;
	float				willDisPastTime = 0.f;

	bool				onDis = false;
	float				onDisPastTime = 0.f;
	float				onDisTime = 0.3f;
};

