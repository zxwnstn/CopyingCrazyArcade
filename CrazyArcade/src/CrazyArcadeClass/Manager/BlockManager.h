#pragma once

#include "CrazyArcadeClass/Obj/Block/Block.h"
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"

class BlockManager
{
public:
	bool init();
	//this is for mapEddit
	bool init(vector<vector<BlockType>>& _blocks);
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();

	void collision();
	auto& GetBlocks() { return blocks; }

private:
	std::vector<vector<Block>> blocks;

private:
	DECLARE_SINGLE(BlockManager)
	
};

