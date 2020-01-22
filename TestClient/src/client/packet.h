#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <time.h>
#include "lib/HeaderShared.h"
#include "lib/MemoryStream.h"
#pragma comment(lib, "ws2_32")

//packet interface
class CrazyPacket {
public:
	virtual void Write(OutputMemoryStream& outStream) = 0;
	virtual void Read(InputMemoryStream& outStream) = 0;
	virtual void show() = 0;
};


//contain specific each block data
class BlockData	
	: public CrazyPacket
{
public:
	int posX, posY;    //Block Position
	int type;			//0, softbloc, 1. hardblock, 2. tree, 3, none 4, bush	
	int tileIndex;		//for tile image render
	int blockIndex;	//for block image render
	int innerItem;		//0, range 1.speed 2, bomb drop limit up 3, no Item

public:
	BlockData();
	BlockData(int _type, int _tileIndex, int _blockIndex);
	~BlockData();

	void Write(OutputMemoryStream& outStream) override;
	void Read(InputMemoryStream& inStream) override;
	void show() override;
};//data size =  6 BYTE


//player will recieve this data when start the game
//and initiate GameScene on their pc with this data
//contain clients basic info and whole blocks data
class InitiationPacket
	: public CrazyPacket
{
public:
	int clientID[2];
	int clientCharacterPosX[2];
	int clientCharacterPosY[2];
	int clientCharacter[2];		// 0 bazzi, 1 dao

public:
	vector<BlockData> blocks;		// 15 * 13 size

public:
	void Write(OutputMemoryStream& outStream) override;
	void Read(InputMemoryStream& inStream) override;
	void show() override;
};//data size = 1178 BYTE



//
class MoveData 
	: public CrazyPacket
{
public:
	int clientID;
	int playerMoveDir;			//0, up 1, down 2, right 3, left 4, noMove;

public:
	void Write(OutputMemoryStream& outStream) override;
	void Read(InputMemoryStream& inStream) override;
	void show() override;
};//data size = 2 BYTE