#include <time.h>
#include <iostream>
#include "packet.h"


int main() {
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SocketAddressFactory fac;
	string ip = "127.0.0.1:9190";
	SocketAddress clientAddr;
	clientAddr = *fac.CreateIPv4FromString(ip);


	TCPSocketPtr clientSock = SocketUtil::CreateTCPSocket(INET);

	clientSock->Connect(clientAddr);
	std::cout << "클라를 시작합니다!" << std::endl;



	char* initBuffer = static_cast<char*>(malloc(1470));
	int size = clientSock->Receive(initBuffer, 1470);
	InputMemoryStream in(initBuffer, size);
	
	InitiationPacket initPacket;
	initPacket.Read(in);

	initPacket.show();
	
	while (true)
	{
		
	}

	WSACleanup();

}