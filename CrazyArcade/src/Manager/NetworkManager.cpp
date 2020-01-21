#include "NetworkManager.h"
#include "Network/HeaderShared.h"
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
	server_ip = _ip;
	SocketAddress clientAddr;
	clientAddr = *fac.CreateIPv4FromString(server_ip);

	clientSock = SocketUtil::CreateTCPSocket(INET);

	clientSock->Connect(clientAddr);

	//temp
	std::cout << "클라를 시작합니다!" << std::endl;	
}

void NetworkManager::sendMoveData(char _clientID, char _playerMoveDir)
{
	//write
	OutputMemoryStream out;
	MoveData md;

	md.Write(out);
	char* Buffer = static_cast<char*>(malloc(1470));

	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());

	clientSock->Send(Buffer, out.GetLength());
}

MoveData NetworkManager::recvMoveData()
{
	MoveData moveData;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	moveData.Read(in);

	return moveData;
}

InitiationData NetworkManager::recvInitData()
{
	InitiationData initData;

	char* Buffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(Buffer, 1470);
	InputMemoryStream in(Buffer, size);
	initData.Read(in);

	return initData;
}
