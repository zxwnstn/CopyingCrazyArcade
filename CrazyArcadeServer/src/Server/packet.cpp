#include "packet.h"

void blockData::Write(OutputMemoryStream & outStream)
{
	outStream.Write(posX);
	outStream.Write(posY);
	outStream.Write(type);
	outStream.Write(tileIndex);
	outStream.Write(blockIndex);
	outStream.Write(innerItem);
}

void blockData::Read(InputMemoryStream & inStream)
{
	inStream.Read(posX);
	inStream.Read(posY);
	inStream.Read(type);
	inStream.Read(tileIndex);
	inStream.Read(blockIndex);
	inStream.Read(innerItem);
}

blockData::blockData()
{
}

inline blockData::blockData(char _type, char _tileIndex, char _blockIndex)
	: type(_type), tileIndex(_tileIndex), blockIndex(_blockIndex)
{
}

blockData::~blockData()
{
}

void blockData::show()
{
	std::cout << " block position x : " << posX << " y : " << posY << "\n";
	
	std::cout << "block type : ";
	switch (type){
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

	if (type == 0) {
		std::cout << "soft block color : ";
		switch (tileIndex) {
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

	if (type == 1) {
		std::cout << "hard block color : ";
		switch (blockIndex){
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

	if (type == 4) {
		std::cout << "tileType : ";
		switch (tileIndex)
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

void InitiationData::Write(OutputMemoryStream & outStream) {
	for (auto _block : block)
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

void InitiationData::Read(InputMemoryStream & inStream) {
	for (auto _block : block)
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

void InitiationData::show()
{
	std::cout << "character info\n";
	for (int i = 0; i < 2; ++i) {
		std::cout << "client Id : " << clientID[i] << "\n";
		std::cout << "select charcter : ";

		switch (clientCharacter[i]){
		case 0:
			std::cout << "bazzi\n";
			break;
		case 1:
			std::cout << "dao\n";
			break;
		}
		std::cout << "character position x : " << clientCharacterPosX << " y " << clientCharacterPosY << "\n";
	}

	std::cout << "block info\n";
	for (auto _block : block) {
		_block.show();
	}
}
