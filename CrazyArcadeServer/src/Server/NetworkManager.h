#pragma once
#include "lib/HeaderShared.h"
#include "lib/MemoryStream.h"
#include "packet.h"

#pragma comment(lib, "ws2_32")

//data size =  6 BYTE
struct blockData {
	char posX, posY;
	//Block Position 기준
	char type;			//0, softbloc, 1. hardblock, 2. tree, 3, none 4, bush	
	char tileIndex;		//for tile image render
	char blockIndex;	//for block image render
	char innerItem;		//0, range 1.speed 2, bomb drop limit up

	void Write(OutputMemoryStream& outStream)
	{
		outStream.Write(posX);
		outStream.Write(posY);
		outStream.Write(type);
		outStream.Write(tileIndex);
		outStream.Write(blockIndex);
		outStream.Write(innerItem);
	}

	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(posX);
		inStream.Read(posY);
		inStream.Read(type);
		inStream.Read(tileIndex);
		inStream.Read(blockIndex);
		inStream.Read(innerItem);
	}
};

//data size =  15 * 13 * 6 + 8 = 1178 BYTE
struct InitiationData {
	vector<blockData> block; // 15 * 13개의 블록 데이터를 갖는다.

	//1대 1부터 구현할거기 때문에 2개만 갖는다.
	char clientID[2];
	char clientPosX[2];
	char clientPosY[2];
	char clientCharacter[2];		// 0 bazzi, 1 dao

	void Write(OutputMemoryStream& outStream)
	{
		for (auto _block : block)
		{
			_block.Write(outStream);
		}

		for (int i = 0; i < 2; i++)
			outStream.Write(clientID[i]);
		for (int i = 0; i < 2; i++)
			outStream.Write(clientPosX[i]);
		for (int i = 0; i < 2; i++)
			outStream.Write(clientPosY[i]);
		for (int i = 0; i < 2; i++)
			outStream.Write(clientCharacter[i]);
	}

	void Read(InputMemoryStream& inStream)
	{
		for (auto _block : block)
		{
			_block.Read(inStream);
		}

		for (int i = 0; i < 2; i++)
			inStream.Read(clientID[i]);
		for (int i = 0; i < 2; i++)
			inStream.Read(clientPosX[i]);
		for (int i = 0; i < 2; i++)
			inStream.Read(clientPosY[i]);
		for (int i = 0; i < 2; i++)
			inStream.Read(clientCharacter[i]);
	}
};

//data size = 2 BYTE
struct MoveData {

	char clientID;
	char playerMoveDir;			//0, up 1, down 2, right 3, left;

	void Write(OutputMemoryStream& outStream)
	{
		outStream.Write(clientID);
		outStream.Write(playerMoveDir);
	}
	inline void MoveData::Read(InputMemoryStream & inStream)
	{
		inStream.Read(clientID);
		inStream.Read(playerMoveDir);
	}
	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(clientID);
		inStream.Read(playerMoveDir);
	}
};

class NetworkManager
{
	//Scene단에서 연결할 ip를 넘겨받아 init한다. 
	void init(string _ip);

	//클라 네트워크 메니저에선 
	void sendMoveData(char _clientID, char _playerMoveDir);
	MoveData recvMoveData();
	InitiationData recvInitData();

private:
	string server_ip;
	TCPSocketPtr clientSock;

	const int moveDataSize = 2;
	const int initDataSize = 1178;

private:
	DECLARE_SINGLE(NetworkManager)
};

