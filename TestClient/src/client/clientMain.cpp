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
	std::cout << "서버에 연결되었습니다!" << std::endl;


	//receive IDPacket
	char* idBuffer = static_cast<char*>(malloc(PACKET_MAX));
	int size = clientSock->Receive(idBuffer, PACKET_MAX);
	InputMemoryStream in(idBuffer, size);
	
	IDpacket idPacket;
	idPacket.Read(in);
	idPacket.show();
	
	//receive InitPacket
	char* InitBuffer = static_cast<char*>(malloc(PACKET_MAX));
	size = clientSock->Receive(InitBuffer, PACKET_MAX);
	InputMemoryStream in2(InitBuffer, size);

	InitiationPacket initPacket;
	initPacket.Read(in2);
	initPacket.show();

	while (true)
	{
		
	}

	WSACleanup();

}