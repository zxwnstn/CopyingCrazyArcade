#include "packet.h"

BlockData::BlockData()
{
}
BlockData::BlockData(char _blockType, char _tileIndex, char _blockIndex)
	: blockType(_blockType), tileIndex(_tileIndex), blockIndex(_blockIndex)
{
}
BlockData::~BlockData()
{
}
void BlockData::Write(OutputMemoryStream & outStream)
{
	outStream.Write(&posX, sizeof(posX));
	outStream.Write(&posY, sizeof(posY));
	outStream.Write(&blockType, sizeof(blockType));
	outStream.Write(&blockIndex, sizeof(blockIndex));
	outStream.Write(&tileIndex, sizeof(tileIndex));
	outStream.Write(&innerItem, sizeof(innerItem));
}
void BlockData::Read(InputMemoryStream & inStream)
{
	inStream.Read(&posX, sizeof(posX));
	inStream.Read(&posY, sizeof(posY));
	inStream.Read(&blockType, sizeof(blockType));
	inStream.Read(&blockIndex, sizeof(blockIndex));
	inStream.Read(&tileIndex, sizeof(tileIndex));
	inStream.Read(&innerItem, sizeof(innerItem));
}
PacketTpye BlockData::GetPacketTpye()
{
	return PacketTpye();
}
int BlockData::GetNetID()
{
	return 0;
}
int BlockData::GetData()
{
	return 0;
}
int BlockData::GetDir()
{
	return 0;
}
int BlockData::GetBomb()
{
	return 0;
}
int BlockData::GetX()
{
	return 0;
}
int BlockData::GetY()
{
	return 0;
}
void BlockData::show()
{
	std::cout << "block position x : " << (int)posX << " y : " << (int)posY << "\n";

	std::cout << "block type : ";
	switch ((int)blockType) {
	case 0:
		std::cout << "soft block\n";
		break;
	case 1:
		std::cout << "hard block\n";
		break;
	case 2:
		std::cout << "tree\n";
		break;
	case 3:
		std::cout << "just tile\n";
		break;
	case 4:
		std::cout << "bush\n";
		break;
	}

	if ((int)blockType == 0) {
		std::cout << "soft block color : ";
		switch ((int)tileIndex) {
		case 0:
			std::cout << "yellow\n";
			break;
		case 1:
			std::cout << "blue\n";
			break;
		case 2:
			std::cout << "orange\n";
			break;
		}

		std::cout << "inner item : ";
		switch ((int)innerItem)
		{
		case 0:
			std::cout << "range up\n";
			break;
		case 1:
			std::cout << "speed up\n";
			break;
		case 2:
			std::cout << "bomb drop limit up\n";
			break;
		case 3:
			std::cout << "no item\n";
		}
	}

	if ((int)blockType == 1) {
		std::cout << "hard block color : ";
		switch ((int)blockIndex) {
		case 0:
			std::cout << "red\n";
			break;
		case 1:
			std::cout << "orange\n";
			break;
		case 2:
			std::cout << "yellow(box)\n";
			break;
		}
	}

	if ((int)blockType == 4) {
		std::cout << "tileType : ";
		switch ((int)tileIndex)
		{
		case 0:
			std::cout << "normal green block\n";
			break;
		case 1:
			std::cout << "heavy green block\n";
			break;
		case 2:
			std::cout << "general road\n";
			break;
		case 3:
			std::cout << "road with center line\n";
			break;
		case 4:
			std::cout << "road with across walk\n";
			break;
		}
	}
	std::cout << "\n";
}


void InitiationPacket::Write(OutputMemoryStream & outStream) {

	outStream.Write(packetType);

	for (int i = 0; i < 2; i++)
		outStream.Write(NetID[i]);
	for (int i = 0; i < 2; i++)
		outStream.Write(clientCharacterPosX[i]);
	for (int i = 0; i < 2; i++)
		outStream.Write(clientCharacterPosY[i]);
	for (int i = 0; i < 2; i++)
		outStream.Write(clientCharacter[i]);

	outStream.WriteVector(blocks);
}
void InitiationPacket::Read(InputMemoryStream & inStream) {

	inStream.Read(packetType);

	for (int i = 0; i < 2; i++)
		inStream.Read(NetID[i]);
	for (int i = 0; i < 2; i++)
		inStream.Read(clientCharacterPosX[i]);
	for (int i = 0; i < 2; i++)
		inStream.Read(clientCharacterPosY[i]);
	for (int i = 0; i < 2; i++)
		inStream.Read(clientCharacter[i]);

	inStream.ReadVector(blocks, 195);
}
PacketTpye InitiationPacket::GetPacketTpye()
{
	return PacketTpye();
}
int InitiationPacket::GetNetID()
{
	return 0;
}
int InitiationPacket::GetData()
{
	return 0;
}
int InitiationPacket::GetDir()
{
	return 0;
}
int InitiationPacket::GetBomb()
{
	return 0;
}
int InitiationPacket::GetX()
{
	return 0;
}
int InitiationPacket::GetY()
{
	return 0;
}
void InitiationPacket::show()
{
	std::cout << "character info\n";
	for (int i = 0; i < 2; ++i) {
		std::cout << "client Id : " << (int)NetID[i] << "\n";
		std::cout << "select charcter : ";

		switch (clientCharacter[i]) {
		case 0:
			std::cout << "bazzi\n";
			break;
		case 1:
			std::cout << "dao\n";
			break;
		}
		std::cout << "character position x : " << (int)clientCharacterPosX[i] << " y " << (int)clientCharacterPosY[i] << "\n";
	}

	std::cout << "block info\n";
	for (auto _block : blocks) {
		_block.show();
	}
}



void MovePacket::Write(OutputMemoryStream& outStream) {
	outStream.Write(packetType);
	outStream.Write(NetID);
	outStream.Write(playerMoveDir);
	outStream.Write(isBomb);
	outStream.Write(x);
	outStream.Write(y);
}
void MovePacket::Read(InputMemoryStream& inStream) {
	inStream.Read(packetType);
	inStream.Read(NetID);
	inStream.Read(playerMoveDir);
	inStream.Read(isBomb);
	inStream.Read(x);
	inStream.Read(y);
}
PacketTpye MovePacket::GetPacketTpye()
{
	return PacketTpye::PLAYER;
}
int MovePacket::GetNetID()
{
	return NetID;
}
int MovePacket::GetData()
{
	return playerMoveDir;
}
int MovePacket::GetDir()
{
	return playerMoveDir;
}
int MovePacket::GetBomb()
{
	return isBomb;
}
int MovePacket::GetX()
{
	return x;
}
int MovePacket::GetY()
{
	return y;
}
void MovePacket::show()
{
	std::cout << NetID << "\n";
	switch (playerMoveDir) {
	case 0:
		std::cout << "player Moved! : up\n";
		break;
	case 1:
		std::cout << "player Moved! : down\n";
		break;
	case 2:
		std::cout << "player Moved! : right\n";
		break;
	case 3:
		std::cout << "player Moved! : left\n";
		break;
	case 4:
		std::cout << "player no moved\n";
		break;
	}

}



void IDpacket::Write(OutputMemoryStream & outStream)
{
	outStream.Write(packetType);
	outStream.Write(NetID);
}

void IDpacket::Read(InputMemoryStream & inStream)
{
	inStream.Read(packetType);
	inStream.Read(NetID);
}

PacketTpye IDpacket::GetPacketTpye()
{
	return PacketTpye::READY;
}

int IDpacket::GetNetID()
{
	return 0;
}

int IDpacket::GetData()
{
	return 0;
}

int IDpacket::GetDir()
{
	return 0;
}

int IDpacket::GetBomb()
{
	return 0;
}

int IDpacket::GetX()
{
	return 0;
}

int IDpacket::GetY()
{
	return 0;
}

void IDpacket::show()
{
	std::cout << "Granted Client ID : " << (int)NetID << "\n";
}


void ReadyPacket::Write(OutputMemoryStream & outStream)
{
	outStream.Write(packetType);
	outStream.Write(NetID);
}

void ReadyPacket::Read(InputMemoryStream & inStream)
{
	inStream.Read(packetType);
	inStream.Read(NetID);
}

PacketTpye ReadyPacket::GetPacketTpye()
{
	return PacketTpye();
}

int ReadyPacket::GetNetID()
{
	return NetID;
}

int ReadyPacket::GetData()
{
	return 0;
}

int ReadyPacket::GetDir()
{
	return 0;
}

int ReadyPacket::GetBomb()
{
	return 0;
}

int ReadyPacket::GetX()
{
	return 0;
}

int ReadyPacket::GetY()
{
	return 0;
}

void ReadyPacket::show()
{
}
