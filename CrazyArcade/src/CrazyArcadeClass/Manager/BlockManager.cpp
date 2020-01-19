#include "Etc/stdafx.h"
#include "BlockManager.h"
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"
DEFINITION_SINGLE(BlockManager)

BlockManager::BlockManager()
{
}
BlockManager::~BlockManager()
{
	release();
}

bool BlockManager::init()
{
	blocks.resize(NUM_BLOCK_Y);
	for (int i = 0; i < NUM_BLOCK_Y; ++i) 
		blocks[i].resize(NUM_BLOCK_X);
	for (int i = 0; i < NUM_BLOCK_Y; ++i) 
		for (int j = 0; j < NUM_BLOCK_X; ++j) 
			blocks[i][j].init(j, i);

	//TODO : make basic map with resetType
	blocks[2][2].resetType(BlockType::BlockSoft);
	blocks[4][4].resetType(BlockType::BlockSoft);
	blocks[6][2].resetType(BlockType::BlockSoft);
	blocks[6][4].resetType(BlockType::BlockSoft);
	blocks[5][2].resetType(BlockType::BlockSoft);
	blocks[6][7].resetType(BlockType::BlockSoft);
	blocks[10][10].resetType(BlockType::BlockSoft);
	blocks[6][9].resetType(BlockType::BlockSoft);
	blocks[6][9].resetType(BlockType::BlockSoft);
	blocks[5][5].resetType(BlockType::BlockNone);
	blocks[7][7].resetType(BlockType::BlockNone);
	blocks[5][7].resetType(BlockType::BlockNone);
	blocks[7][5].resetType(BlockType::BlockNone);

	return true;
}
bool BlockManager::init(vector<vector<BlockType>>& _blocks)
{
	return true;
}

void BlockManager::update(float deltaTime)
{
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			blocks[i][j].update(deltaTime);
}
void BlockManager::render(HDC hdc)
{
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			if (blocks[i][j].getType() == BlockType::BlockNone)
				blocks[i][j].render(hdc);
		}
	}
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			if (blocks[i][j].getType() == BlockType::BlockHard)
				blocks[i][j].render(hdc);
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			if (blocks[i][j].getType() == BlockType::BlockSoft)
				blocks[i][j].render(hdc);
		}
	}
}
void BlockManager::afterRender(HDC hdc)
{
	//The hard block must be render last!
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			if (blocks[i][j].getType() != BlockType::BlockNone)
				blocks[i][j].afterRender(hdc);
}
void BlockManager::debugRender(HDC hdc)
{
	if(m_showRect)
		for (int i = 0; i < NUM_BLOCK_Y; ++i)
			for (int j = 0; j < NUM_BLOCK_X; ++j)
				blocks[i][j].debugRender(hdc);
}
void BlockManager::collision()
{
	//TODO : First implement block move then nee to implement this.
	//It's for erase Item causes player's push block
}
void BlockManager::release()
{
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			blocks[i][j].release();
	blocks.clear();
}


IRECT BlockManager::getIRectFromIdx(int _x, int _y)
{
	IRECT ret = IRectMake(_x * BLOCK_WIDTH + MAPOFFSET_X, _y * BLOCK_HEIGHT + MAPOFFSET_Y, BLOCK_WIDTH, BLOCK_HEIGHT);
	return ret;
}
