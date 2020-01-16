#pragma once

#include "HomeWorkClass/Obj/Block/Block.h"
#include "HomeWorkClass/Obj/Bomb/Bomb.h"

class BlockManager
{
public:
	bool init();
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

