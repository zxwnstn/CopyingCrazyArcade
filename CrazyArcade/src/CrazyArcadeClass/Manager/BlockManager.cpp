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

	if (1) {
		blocks[0][0].init(BlockType::BlockNone, 0, 0, tileGreenBlock);
		blocks[0][1].init(BlockType::BlockSoft, 1, 0, tileGreenBlock, sbOrange);
		blocks[0][2].init(BlockType::BlockSoft, 2, 0, tileGreenBlock, sbRed);
		blocks[0][3].init(BlockType::BlockSoft, 3, 0, tileGreenBlock, sbOrange);
		blocks[0][4].init(BlockType::BlockSoft, 4, 0, tileGreenBlock);
		blocks[0][5].init(BlockType::BlockBush, 5, 0, tileGreenBlock);

		blocks[0][6].init(BlockType::BlockNone, 6, 0, tileGray);
		blocks[0][7].init(BlockType::BlockNone, 7, 0, tileCenterLine);
		blocks[0][8].init(BlockType::BlockNone, 8, 0, tileGray);

		blocks[0][9].init(BlockType::BlockBush, 9, 0, tileGreenBlock);
		blocks[0][10].init(BlockType::BlockHard, 10, 0, tileGreenBlock, hbYellow);
		blocks[0][11].init(BlockType::BlockSoft, 11, 0, tileGreenBlock, sbRed);
		blocks[0][12].init(BlockType::BlockHard, 12, 0, tileGreenBlock, hbYellow);
		blocks[0][13].init(BlockType::BlockNone, 13, 0, tileGreenBlock);
		blocks[0][14].init(BlockType::BlockHard, 14, 0, tileGreenBlock, hbYellow);
	}

	if (2) {
		blocks[1][0].init(BlockType::BlockNone, 0, 1, tileGreenBlock);
		blocks[1][1].init(BlockType::BlockHard, 1, 1, tileGreenBlock, hbOrange);
		blocks[1][2].init(BlockType::BlockSoft, 2, 1, tileGreenBlock, sbBox);
		blocks[1][3].init(BlockType::BlockHard, 3, 1, tileGreenBlock, hbOrange);
		blocks[1][4].init(BlockType::BlockSoft, 4, 1, tileGreenBlock, sbBox);
		blocks[1][5].init(BlockType::BlockTree, 5, 1, tileGreenBlock);

		blocks[1][6].init(BlockType::BlockNone, 6, 1, tileGray);
		blocks[1][7].init(BlockType::BlockNone, 7, 1, tileCenterLine);
		blocks[1][8].init(BlockType::BlockNone, 8, 1, tileGray);

		blocks[1][9].init(BlockType::BlockTree, 9, 1, tileGreenBlock);
		blocks[1][10].init(BlockType::BlockSoft, 10, 1, tileGreenBlock, sbRed);
		blocks[1][11].init(BlockType::BlockSoft, 11, 1, tileGreenBlock, sbOrange);
		blocks[1][12].init(BlockType::BlockNone, 12, 1, tileGreenBlock);
		blocks[1][13].init(BlockType::BlockNone, 13, 1, tileGreenBlock);
		blocks[1][14].init(BlockType::BlockNone, 14, 1, tileGreenBlock);
	}

	if (2) {
		blocks[2][0].init(BlockType::BlockNone, 0, 2, tileGreenBlock);
		blocks[2][1].init(BlockType::BlockNone, 1, 2, tileGreenBlock);
		blocks[2][2].init(BlockType::BlockSoft, 2, 2, tileGreenBlock, sbOrange);
		blocks[2][3].init(BlockType::BlockSoft, 3, 2, tileGreenBlock, sbRed);
		blocks[2][4].init(BlockType::BlockSoft, 4, 2, tileGreenBlock, sbOrange);
		blocks[2][5].init(BlockType::BlockNone, 5, 2, tileGreenBlock);

		blocks[2][6].init(BlockType::BlockNone, 6, 2, tileAcrossWalk);
		blocks[2][7].init(BlockType::BlockNone, 7, 2, tileAcrossWalk);
		blocks[2][8].init(BlockType::BlockNone, 8, 2, tileAcrossWalk);

		blocks[2][9].init(BlockType::BlockNone, 9, 2, tileGreenBlock);
		blocks[2][10].init(BlockType::BlockHard, 10, 2, tileGreenBlock);
		blocks[2][11].init(BlockType::BlockSoft, 11, 2, tileGreenBlock, sbBox);
		blocks[2][12].init(BlockType::BlockHard, 12, 2, tileGreenBlock);
		blocks[2][13].init(BlockType::BlockSoft, 13, 2, tileGreenBlock, sbBox);
		blocks[2][14].init(BlockType::BlockHard, 14, 2, tileGreenBlock);
	}

	if (3) {
		blocks[3][0].init(BlockType::BlockSoft, 0, 3, tileGreenBlock, sbBox);
		blocks[3][1].init(BlockType::BlockHard, 1, 3, tileGreenBlock, hbOrange);
		blocks[3][2].init(BlockType::BlockSoft, 2, 3, tileGreenBlock, sbBox);
		blocks[3][3].init(BlockType::BlockHard, 3, 3, tileGreenBlock, hbOrange);
		blocks[3][4].init(BlockType::BlockSoft, 4, 3, tileGreenBlock, sbBox);
		blocks[3][5].init(BlockType::BlockTree, 5, 3, tileGreenBlock);

		blocks[3][6].init(BlockType::BlockNone, 6, 3, tileGray);
		blocks[3][7].init(BlockType::BlockNone, 7, 3, tileCenterLine);
		blocks[3][8].init(BlockType::BlockNone, 8, 3, tileGray);

		blocks[3][9].init(BlockType::BlockTree, 9, 3, tileGreenBlock);
		blocks[3][10].init(BlockType::BlockSoft, 10, 3, tileGreenBlock, sbOrange);
		blocks[3][11].init(BlockType::BlockSoft, 11, 3, tileGreenBlock, sbRed);
		blocks[3][12].init(BlockType::BlockSoft, 12, 3, tileGreenBlock, sbOrange);
		blocks[3][13].init(BlockType::BlockSoft, 13, 3, tileGreenBlock, sbRed);
		blocks[3][14].init(BlockType::BlockSoft, 14, 3, tileGreenBlock, sbOrange);
	}

	if (5) {
		blocks[4][0].init(BlockType::BlockSoft, 0, 4, tileGreenBlock, sbRed);
		blocks[4][1].init(BlockType::BlockSoft, 1, 4, tileGreenBlock, sbOrange);
		blocks[4][2].init(BlockType::BlockSoft, 2, 4, tileGreenBlock, sbRed);
		blocks[4][3].init(BlockType::BlockSoft, 3, 4, tileGreenBlock, sbOrange);
		blocks[4][4].init(BlockType::BlockNone, 4, 4, tileGreenBlock);
		blocks[4][5].init(BlockType::BlockNone, 5, 4, tileGreenBlock);

		blocks[4][6].init(BlockType::BlockNone, 6, 4, tileGray);
		blocks[4][7].init(BlockType::BlockNone, 7, 4, tileCenterLine);
		blocks[4][8].init(BlockType::BlockNone, 8, 4, tileGray);

		blocks[4][9].init(BlockType::BlockNone, 9, 4, tileGreenBlock);
		blocks[4][10].init(BlockType::BlockHard, 10, 4, tileGreenBlock, hbYellow);
		blocks[4][11].init(BlockType::BlockSoft, 11, 4, tileGreenBlock, sbBox);
		blocks[4][12].init(BlockType::BlockHard, 12, 4, tileGreenBlock, hbYellow);
		blocks[4][13].init(BlockType::BlockSoft, 13, 4, tileGreenBlock, sbBox);
		blocks[4][14].init(BlockType::BlockHard, 14, 4,  tileGreenBlock, hbYellow);
	}

	if (6) {
		blocks[5][0].init(BlockType::BlockSoft, 0, 5, tileGreenBlock, sbOrange);
		blocks[5][1].init(BlockType::BlockHard, 1, 5, tileGreenBlock, hbOrange);
		blocks[5][2].init(BlockType::BlockSoft, 2, 5, tileGreenBlock, sbOrange);
		blocks[5][3].init(BlockType::BlockHard, 3, 5, tileGreenBlock, hbOrange);
		blocks[5][4].init(BlockType::BlockSoft, 4, 5, tileGreenBlock, sbOrange);
		blocks[5][5].init(BlockType::BlockTree, 5, 5, tileGreenBlock);

		blocks[5][6].init(BlockType::BlockNone, 6, 5, tileGray);
		blocks[5][7].init(BlockType::BlockNone, 7, 5, tileCenterLine);
		blocks[5][8].init(BlockType::BlockNone, 8, 5, tileGray);

		blocks[5][9].init(BlockType::BlockNone, 9, 5, tileGreenBlock);
		blocks[5][10].init(BlockType::BlockSoft, 10, 5, tileGreenBlock, sbRed);
		blocks[5][11].init(BlockType::BlockSoft, 11, 5, tileGreenBlock, sbOrange);
		blocks[5][12].init(BlockType::BlockSoft, 12, 5, tileGreenBlock, sbRed);
		blocks[5][13].init(BlockType::BlockSoft, 13, 5, tileGreenBlock, sbOrange);
		blocks[5][14].init(BlockType::BlockSoft, 14, 5, tileGreenBlock, sbRed);
	}

	if (7) {
		blocks[6][0].init(BlockType::BlockTree, 0, 6, tileGreenBlock);
		blocks[6][1].init(BlockType::BlockNone, 1, 6, tileGreenBlock);
		blocks[6][2].init(BlockType::BlockTree, 2, 6, tileGreenBlock);
		blocks[6][3].init(BlockType::BlockNone, 3, 6, tileGreenBlock);
		blocks[6][4].init(BlockType::BlockTree, 4, 6, tileGreenBlock);
		blocks[6][5].init(BlockType::BlockNone, 5, 6, tileGreenBlock);

		blocks[6][6].init(BlockType::BlockNone, 6, 6, tileGray);
		blocks[6][7].init(BlockType::BlockNone, 7, 6, tileCenterLine);
		blocks[6][8].init(BlockType::BlockNone, 8, 6, tileGray, sbBox);

		blocks[6][9].init(BlockType::BlockNone, 9, 6, tileGreenBlock);
		blocks[6][10].init(BlockType::BlockTree, 10, 6, tileGreenBlock);
		blocks[6][11].init(BlockType::BlockNone, 11, 6, tileGreenBlock);
		blocks[6][12].init(BlockType::BlockTree, 12, 6, tileGreenBlock);
		blocks[6][13].init(BlockType::BlockNone, 13, 6, tileGreenBlock);
		blocks[6][14].init(BlockType::BlockTree, 14, 6, tileGreenBlock);
	}

	if (8) {
		blocks[7][0].init(BlockType::BlockSoft, 0, 7, tileGreenBlock, sbRed);
		blocks[7][1].init(BlockType::BlockSoft, 1, 7, tileGreenBlock, sbOrange);
		blocks[7][2].init(BlockType::BlockSoft, 2, 7, tileGreenBlock, sbRed);
		blocks[7][3].init(BlockType::BlockSoft, 3, 7, tileGreenBlock, sbOrange);
		blocks[7][4].init(BlockType::BlockNone, 4, 7, tileGreenBlock);
		blocks[7][5].init(BlockType::BlockNone, 5, 7, tileGreenBlock);

		blocks[7][6].init(BlockType::BlockNone, 6, 7, tileGray);
		blocks[7][7].init(BlockType::BlockNone, 7, 7, tileCenterLine);
		blocks[7][8].init(BlockType::BlockNone, 8, 7, tileGray);

		blocks[7][9].init(BlockType::BlockTree, 9, 7, tileGreenBlock);
		blocks[7][10].init(BlockType::BlockSoft, 10, 7, tileGreenBlock, sbRed);
		blocks[7][11].init(BlockType::BlockHard, 11, 7, tileGreenBlock, hbOrange);
		blocks[7][12].init(BlockType::BlockSoft, 12, 7, tileGreenBlock, sbRed);
		blocks[7][13].init(BlockType::BlockHard, 13, 7, tileGreenBlock, hbOrange);
		blocks[7][14].init(BlockType::BlockSoft, 14, 7, tileGreenBlock, sbRed);
	}

	if (9) {
		blocks[8][0].init(BlockType::BlockHard, 0, 8, tileGreenBlock, hbBlue);
		blocks[8][1].init(BlockType::BlockSoft, 1, 8, tileGreenBlock, sbBox);
		blocks[8][2].init(BlockType::BlockHard, 2, 8, tileGreenBlock, hbBlue);
		blocks[8][3].init(BlockType::BlockSoft, 3, 8, tileGreenBlock, sbBox);
		blocks[8][4].init(BlockType::BlockHard, 4, 8, tileGreenBlock, hbBlue);
		blocks[8][5].init(BlockType::BlockNone, 5, 8, tileGreenBlock);

		blocks[8][6].init(BlockType::BlockNone, 6, 8, tileGray);
		blocks[8][7].init(BlockType::BlockNone, 7, 8, tileCenterLine);
		blocks[8][8].init(BlockType::BlockNone, 8, 8, tileGray);

		blocks[8][9].init(BlockType::BlockNone, 9, 8, tileGreenBlock);
		blocks[8][10].init(BlockType::BlockNone, 10, 8, tileGreenBlock);
		blocks[8][11].init(BlockType::BlockSoft, 11, 8, tileGreenBlock, sbRed);
		blocks[8][12].init(BlockType::BlockSoft, 12, 8, tileGreenBlock, sbOrange);
		blocks[8][13].init(BlockType::BlockSoft, 13, 8, tileGreenBlock, sbRed);
		blocks[8][14].init(BlockType::BlockSoft, 14, 8, tileGreenBlock, sbOrange);
	}

	if (10) {
		blocks[9][0].init(BlockType::BlockNone, 0, 9, tileGreenBlock);
		blocks[9][1].init(BlockType::BlockSoft, 1, 9, tileGreenBlock, sbOrange);
		blocks[9][2].init(BlockType::BlockSoft, 2, 9, tileGreenBlock, sbRed);
		blocks[9][3].init(BlockType::BlockSoft, 3, 9, tileGreenBlock, sbOrange);
		blocks[9][4].init(BlockType::BlockSoft, 4, 9, tileGreenBlock);
		blocks[9][5].init(BlockType::BlockTree, 5, 9, tileGreenBlock);

		blocks[9][6].init(BlockType::BlockNone, 6, 9, tileGray);
		blocks[9][7].init(BlockType::BlockNone, 7, 9, tileCenterLine);
		blocks[9][8].init(BlockType::BlockNone, 8, 9, tileGray);

		blocks[9][9].init(BlockType::BlockTree, 9, 9, tileGreenBlock);
		blocks[9][10].init(BlockType::BlockSoft, 10, 9, tileGreenBlock, sbBox);
		blocks[9][11].init(BlockType::BlockHard, 11, 9, tileGreenBlock, hbOrange);
		blocks[9][12].init(BlockType::BlockSoft, 12, 9, tileGreenBlock, sbBox);
		blocks[9][13].init(BlockType::BlockHard, 13, 9, tileGreenBlock, hbOrange);
		blocks[9][14].init(BlockType::BlockSoft, 14, 9, tileGreenBlock, sbBox);
	}

	if (11) {
		blocks[10][0].init(BlockType::BlockHard, 0, 10, tileGreenBlock, hbBlue);
		blocks[10][1].init(BlockType::BlockNone, 1, 10, tileGreenBlock);
		blocks[10][2].init(BlockType::BlockHard, 2, 10, tileGreenBlock, hbBlue);
		blocks[10][3].init(BlockType::BlockSoft, 3, 10, tileGreenBlock, sbBox);
		blocks[10][4].init(BlockType::BlockHard, 4, 10, tileGreenBlock, hbBlue);
		blocks[10][5].init(BlockType::BlockNone, 5, 10, tileGreenBlock);

		blocks[10][6].init(BlockType::BlockNone, 6, 10, tileAcrossWalk);
		blocks[10][7].init(BlockType::BlockNone, 7, 10, tileAcrossWalk);
		blocks[10][8].init(BlockType::BlockNone, 8, 10, tileAcrossWalk);

		blocks[10][9].init(BlockType::BlockNone, 9, 10, tileGreenBlock);
		blocks[10][10].init(BlockType::BlockNone, 10, 10, tileGreenBlock);
		blocks[10][11].init(BlockType::BlockNone, 11, 10, tileGreenBlock);
		blocks[10][12].init(BlockType::BlockSoft, 12, 10, tileGreenBlock, sbRed);
		blocks[10][13].init(BlockType::BlockSoft, 13, 10, tileGreenBlock, sbOrange);
		blocks[10][14].init(BlockType::BlockSoft, 14, 10, tileGreenBlock, sbRed);
	}

	if (12) {
		blocks[11][0].init(BlockType::BlockNone, 0, 11, tileGreenBlock);
		blocks[11][1].init(BlockType::BlockNone, 1, 11, tileGreenBlock);
		blocks[11][2].init(BlockType::BlockSoft, 2, 11, tileGreenBlock, sbRed);
		blocks[11][3].init(BlockType::BlockSoft, 3, 11, tileGreenBlock, sbOrange);
		blocks[11][4].init(BlockType::BlockSoft, 4, 11, tileGreenBlock, sbRed);
		blocks[11][5].init(BlockType::BlockTree, 5, 11, tileGreenBlock);

		blocks[11][6].init(BlockType::BlockNone, 6, 11, tileGray);
		blocks[11][7].init(BlockType::BlockNone, 7, 11, tileCenterLine);
		blocks[11][8].init(BlockType::BlockNone, 8, 11, tileGray);

		blocks[11][9].init(BlockType::BlockTree , 9, 11, tileGreenBlock);
		blocks[11][10].init(BlockType::BlockSoft, 10, 11, tileGreenBlock, sbBox);
		blocks[11][11].init(BlockType::BlockHard , 11, 11, tileGreenBlock, hbOrange);
		blocks[11][12].init(BlockType::BlockSoft, 12, 11, tileGreenBlock, sbBox);
		blocks[11][13].init(BlockType::BlockHard, 13, 11, tileGreenBlock, hbOrange);
		blocks[11][14].init(BlockType::BlockNone, 14, 11, tileGreenBlock);
	}

	if (13) {
		blocks[12][0].init(BlockType::BlockHard, 0, 12, tileGreenBlock, hbBlue);
		blocks[12][1].init(BlockType::BlockNone, 1, 12, tileGreenBlock);
		blocks[12][2].init(BlockType::BlockHard, 2, 12, tileGreenBlock, hbBlue);
		blocks[12][3].init(BlockType::BlockSoft, 3, 12, tileGreenBlock, sbRed);
		blocks[12][4].init(BlockType::BlockHard, 4, 12, tileGreenBlock, hbBlue);
		blocks[12][5].init(BlockType::BlockNone, 5, 12, tileGreenBlock);

		blocks[12][6].init(BlockType::BlockNone, 6, 12, tileGray);
		blocks[12][7].init(BlockType::BlockNone, 7, 12, tileCenterLine);
		blocks[12][8].init(BlockType::BlockNone, 8, 12, tileGray);

		blocks[12][9].init(BlockType::BlockNone, 9, 12, tileGreenBlock);
		blocks[12][10].init(BlockType::BlockSoft, 10, 12, tileGreenBlock, sbOrange);
		blocks[12][11].init(BlockType::BlockSoft, 11, 12, tileGreenBlock, sbRed);
		blocks[12][12].init(BlockType::BlockSoft, 12, 12, tileGreenBlock, sbOrange);
		blocks[12][13].init(BlockType::BlockNone, 13, 12, tileGreenBlock);
		blocks[12][14].init(BlockType::BlockNone, 14, 12, tileGreenBlock);
	}

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
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			if (blocks[i][j].getType() == BlockType::BlockTree)
				blocks[i][j].render(hdc);
	for (int i = 0; i < NUM_BLOCK_Y; ++i)
		for (int j = 0; j < NUM_BLOCK_X; ++j)
			if (blocks[i][j].getType() == BlockType::BlockBush)
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
