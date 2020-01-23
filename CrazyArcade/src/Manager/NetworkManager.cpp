#include "Etc/stdafx.h"
#include "NetworkManager.h"

DEFINITION_SINGLE(NetworkManager)

NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
	WSACleanup();
}

void NetworkManager::init(string _ip)
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SocketAddressFactory fac;
	SocketAddress clientAddr;
	server_ip = _ip;
	clientAddr = *fac.CreateIPv4FromString(server_ip);

	clientSock = SocketUtil::CreateTCPSocket(INET);
	clientSock->Connect(clientAddr);

	//temp
	std::cout << "서버에 접속 했습니다." << std::endl;	
}

void NetworkManager::sendMoveData(char _clientID, char _playerMoveDir)
{
	//write
	OutputMemoryStream out;
	MovePacket md;

	md.Write(out);
	char* Buffer = static_cast<char*>(malloc(1470));
	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());

	clientSock->Send(Buffer, out.GetLength());
}

MovePacket NetworkManager::recvMoveData()
{
	MovePacket moveData;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	moveData.Read(in);

	return moveData;
}

IDpacket NetworkManager::recvID()
{
	return IDpacket();
}

InitiationPacket NetworkManager::recvInitData()
{
	InitiationPacket initData;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	initData.Read(in);

	return initData;
}
