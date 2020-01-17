#pragma once
#include "CrazyArcadeClass/Obj/Block/Block.h"

class BlockManager{
public:
	//interface
	bool init();
	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);
	void release();
	void collision();
	//this is for mapEddit
	bool init(vector<vector<BlockType>>& _blocks);

public:
	//getter
	auto& GetBlocks() { return blocks; }

public:
	static IRECT getIRectFromIdx(int _x, int _y);

private:
	std::vector<vector<Block>> blocks;

private:
	DECLARE_SINGLE(BlockManager)
};

