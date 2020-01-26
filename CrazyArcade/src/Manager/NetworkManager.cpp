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

	std::cout << TEXT("서버에 접속 했습니다.") << std::endl;
}

void NetworkManager::sendReadyPacket()
{
	OutputMemoryStream out;
	ReadyPacket readyPacket;
	readyPacket.NetID = thisClientNetID;

	readyPacket.Write(out);
	char* Buffer = static_cast<char*>(malloc(1470));
	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());

	clientSock->Send(Buffer, out.GetLength());
}

WorldState NetworkManager::recvWorldData()
{
	WorldState worldState;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	worldState.Read(in);

	return worldState;
}

void NetworkManager::close()
{
	clientSock->~TCPSocket();
	clientSock = nullptr;
}

int NetworkManager::getThisClientNetID()
{
	return thisClientNetID;
}

void NetworkManager::recvID()
{
	IDpacket idPacket;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	idPacket.Read(in);

	thisClientNetID = idPacket.NetID;

	std::cout << "아이디를 부여 받았습니다 ID : " << thisClientNetID << std::endl;
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

void NetworkManager::sendMovePacket(MovePacket & movePacket)
{
	//write
	OutputMemoryStream out;

	movePacket.Write(out);
	char* Buffer = static_cast<char*>(malloc(1470));
	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());

	clientSock->Send(Buffer, out.GetLength());
}
