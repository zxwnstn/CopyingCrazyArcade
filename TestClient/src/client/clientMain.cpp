#include <time.h>
#include <iostream>
#include <conio.h>
#include "packet.h"

int clientID;

void sendMovePacket(TCPSocketPtr& sock, int direction) {
	MovePacket movePacket;
	movePacket.packetType = (char)PacketTpye::PLAYER;
	movePacket.clientID = clientID;
	movePacket.playerMoveDir = (char)direction;

	OutputMemoryStream out;
	char* Buffer = static_cast<char*>(malloc(PACKET_MAX));
	movePacket.Write(out);

	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());
	sock->Send(Buffer, out.GetLength());
	std::cout << "이동 패킷을 서버로 전송 했습니다.\n";
} 

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

	//Receive ID
	char* Buffer = static_cast<char*>(malloc(PACKET_MAX));
	int size = clientSock->Receive(Buffer, PACKET_MAX);
	InputMemoryStream in(Buffer, size);

	IDpacket idPacket;
	idPacket.Read(in);
	clientID = idPacket.clientID;
	
	//Receive Initiation data
	size = clientSock->Receive(Buffer, PACKET_MAX);
	InputMemoryStream in2(Buffer, size);

	InitiationPacket initPacket;
	initPacket.Read(in2);

	while (true){	
		if (kbhit()) {
			char input = getch();
			switch (input){
			case 'w':
				sendMovePacket(clientSock, 0);
				break;
			case 's':
				sendMovePacket(clientSock, 1);
				break;
			case 'a':
				sendMovePacket(clientSock, 2);
				break;
			case 'd':
				sendMovePacket(clientSock, 3);
				break;
			}
		}
	}

	WSACleanup();

}