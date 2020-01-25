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

	char* Buffer = static_cast<char*>(malloc(PACKET_MAX));
	int size = clientSock->Receive(Buffer, PACKET_MAX);
	//temp
	InputMemoryStream in(Buffer,size);
	idpacket.Read(in);

	std::cout << TEXT("서버에 접속 했습니다.") << NetID << std::endl;
}

void NetworkManager::sendReadyPacket()
{
	OutputMemoryStream out;
	ReadyPacket readyPacket;
	readyPacket.NetID = NetID;

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

int NetworkManager::getNetID()
{
	return NetID;
}

void NetworkManager::recvID()
{
	IDpacket idPacket;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	idPacket.Read(in);

	NetID = idPacket.NetID;

	std::cout << TEXT("아이디를 부여 받았습니다 ID : ") << NetID << std::endl;
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
