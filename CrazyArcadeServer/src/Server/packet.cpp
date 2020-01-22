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
	outStream.Write(posX);
	outStream.Write(posY);
	outStream.Write(blockType);
	outStream.Write(tileIndex);
	outStream.Write(blockIndex);
	outStream.Write(innerItem);
}
void BlockData::Read(InputMemoryStream & inStream)
{
	inStream.Read(posX);
	inStream.Read(posY);
	inStream.Read(blockType);
	inStream.Read(tileIndex);
	inStream.Read(blockIndex);
	inStream.Read(innerItem);
}
void BlockData::show()
{
	std::cout << " block position x : " << posX << " y : " << posY << "\n";
	
	std::cout << "block type : ";
	switch ((int)blockType){
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
		switch (innerItem)
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
		switch ((int)blockIndex){
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
}


void InitiationPacket::Write(OutputMemoryStream & outStream) {
	
	outStream.Write(packetType);

	for (auto _block : blocks)
		_block.Write(outStream);

	for (int i = 0; i < 2; i++)
		outStream.Write(clientID[i]);
	for (int i = 0; i < 2; i++)
		outStream.Write(clientCharacterPosX[i]);
	for (int i = 0; i < 2; i++)
		outStream.Write(clientCharacterPosY[i]);
	for (int i = 0; i < 2; i++)
		outStream.Write(clientCharacter[i]);
}
void InitiationPacket::Read(InputMemoryStream & inStream) {
	
	inStream.Read(packetType);

	blocks.resize(195);
	for (auto _block : blocks)
		_block.Read(inStream);

	for (int i = 0; i < 2; i++)
		inStream.Read(clientID[i]);
	for (int i = 0; i < 2; i++)
		inStream.Read(clientCharacterPosX[i]);
	for (int i = 0; i < 2; i++)
		inStream.Read(clientCharacterPosY[i]);
	for (int i = 0; i < 2; i++)
		inStream.Read(clientCharacter[i]);
}
void InitiationPacket::show()
{
	std::cout << "character info\n";
	for (int i = 0; i < 2; ++i) {
		std::cout << "client Id : " << (int)clientID[i] << "\n";
		std::cout << "select charcter : ";

		switch (clientCharacter[i]){
		case 0:
			std::cout << "bazzi\n";
			break;
		case 1:
			std::cout << "dao\n";
			break;
		}
		std::cout << "character position x : " << (int)clientCharacterPosX << " y " << (int)clientCharacterPosY << "\n";
	}

	std::cout << "block info\n";
	for (auto _block : blocks) {
		_block.show();
	}
}



void MoveData::Write(OutputMemoryStream& outStream) {
	outStream.Write(packetType);
	outStream.Write(clientID);
	outStream.Write(playerMoveDir);
}
void MoveData::Read(InputMemoryStream& inStream) {
	inStream.Read(packetType);
	inStream.Read(clientID);
	inStream.Read(playerMoveDir);
}
void MoveData::show()
{
	std::cout << clientID << "\n";
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
	outStream.Write(clientID);
}

void IDpacket::Read(InputMemoryStream & inStream)
{
	inStream.Read(packetType);
	inStream.Read(clientID);
}

void IDpacket::show()
{
	std::cout << "Granted Client ID : " << (int)clientID << "\n";
}
