#include "Etc/stdafx.h"
#include "BlockManager.h"
DEFINITION_SINGLE(BlockManager)


BlockManager::BlockManager()
{
}

BlockManager::~BlockManager()
{
}

bool BlockManager::init()
{
	blocks.resize(NUM_BLOCK_Y);
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		blocks[i].resize(NUM_BLOCK_X);
	}
	for (int i = 0; i < NUM_BLOCK_Y; ++i) {
		for (int j = 0; j < NUM_BLOCK_X; ++j) {
			blocks[i][j].init(i, j);
		}
	}

	blocks[2][2].resetType(BlockType::BlockSoft);
	blocks[4][4].resetType(BlockType::BlockSoft);
	blocks[6][2].resetType(BlockType::BlockSoft);
	blocks[6][4].resetType(BlockType::BlockSoft);
	blocks[5][2].resetType(BlockType::BlockSoft);
	blocks[6][7].resetType(BlockType::BlockSoft);
	blocks[10][10].resetType(BlockType::BlockSoft);
	blocks[6][9].resetType(BlockType::BlockSoft);

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
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			blocks[i][j].render(hdc);
}

void BlockManager::debugRender(HDC hdc)
{
	if(m_showRect)
		for (int i = 0; i < NUM_BLOCK_Y; ++i)
			for (int j = 0; j < NUM_BLOCK_X; ++j)
				blocks[i][j].debugRender(hdc);
}

void BlockManager::release()
{
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			blocks[i][j].release();
}

void BlockManager::collision()
{
}

