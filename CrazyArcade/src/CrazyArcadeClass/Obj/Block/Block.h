#pragma once
#include "CrazyArcadeClass/Obj/Item/Item.h"

class Block
{
private:
	void softToNoneBlock();

public:
	Block();
	~Block();

	bool init(int x, int y);
	//this is fot map edit
	bool init(BlockType type, int x, int y);
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void triggerDis(float time);
	void resetType(BlockType type);

	FRECT& getRect() { return rect; }
	BlockType getType() { return type; }
	bool isWillDis() { return willDis; }

	void release();

private:
	Image*				curBlockImage = nullptr;
	int					curBlockIdx = 0;
	shared_ptr<Item>	innerItem = nullptr;
	BlockType			type;
	FRECT				rect;
	BlockPosition		pos;

	//soft blcok Destroy를 위한 변수
	bool				willDis = false;
	float				willDisTime;
	float				willDisPastTime = 0.f;

	bool				onDis = false;
	float				onDisPastTime = 0.f;
	float				onDisTime = 0.3f;
};

