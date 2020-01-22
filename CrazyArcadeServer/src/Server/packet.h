#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <time.h>
#include "lib/HeaderShared.h"
#include "lib/MemoryStream.h"
#include "CrazyArcadeData.h"
#include "CrazyUtil.h"
#pragma comment(lib, "ws2_32")
#define PACKET_MAX 1470

enum class PacketTpye
{
	WorldState,
	PLAYER,
	BOMB,
};

//packet interface
class CrazyPacket {
public:
	virtual void Write(OutputMemoryStream& outStream) = 0;
	virtual void Read(InputMemoryStream& inStream) = 0;
	virtual void show() = 0;
};


//contain granted client ID
class IDpacket
	: public CrazyPacket
{
public:
	char packetType = (char)PacketTpye::PLAYER;
	char clientID;

public:
	void Write(OutputMemoryStream& outStream) override;
	void Read(InputMemoryStream& inStream) override;
	void show() override;
};

//contain specific each block data
class BlockData	
	: public CrazyPacket
{
public:
	char posX, posY;    //Block Position
	char blockType;		//0, softbloc, 1. hardblock, 2. tree, 3, none 4, bush	
	char blockIndex;	//for block image render
	char tileIndex;		//for tile image render
	char innerItem;		//0, range 1.speed 2, bomb drop limit up 3, no Item

public:
	BlockData();
	BlockData(char _blockType, char _tileIndex, char _blockIndex);
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
	char packetType = (char)PacketTpye::PLAYER;
	char clientID[2];
	char clientCharacterPosX[2];
	char clientCharacterPosY[2];
	char clientCharacter[2];		// 0 bazzi, 1 dao

public:
	vector<BlockData> blocks;		// 15 * 13 size

public:
	void Write(OutputMemoryStream& outStream) override;
	void Read(InputMemoryStream& inStream) override;
	void show() override;
};//data size = 1178 BYTE


class MoveData 
	: public CrazyPacket
{
public:
	char packetType = (char)PacketTpye::PLAYER;
	char clientID;
	char playerMoveDir;			//0, up 1, down 2, right 3, left 4, noMove;

public:
	void Write(OutputMemoryStream& outStream) override;
	void Read(InputMemoryStream& inStream) override;
	void show() override;
};//data size = 2 BYTE

