#include "packet.h"
#include "WorldState.h"

//critical section
int clientNumber;
bool wait = true;
std::mutex mtx;

WorldState ws;
int readyNumber = 0;
int startNumber = 2;

void echo(TCPSocketPtr servsock, TCPSocketPtr clientSocket)
{
	//critical section
	mtx.lock();
	++clientNumber;
	mtx.unlock();

	int thisclientnumber = clientNumber;
	std::cout << thisclientnumber << "번 클라이언트가 접속하였습니다!!" << std::endl;

	//Send IDpacket
	IDpacket idPacket;
	idPacket.packetType = (char)PacketTpye::PLAYER;
	idPacket.NetID = (char)thisclientnumber;

	OutputMemoryStream out;
	idPacket.Write(out);
	char* Buffer = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(Buffer, out.GetBufferPtr(), out.GetLength());
	clientSocket->Send(Buffer, out.GetLength());
	std::cout << thisclientnumber << "번 클라이언트로 ID패킷을 보냈습니다.\n";

	//Send initPacket
	InitiationPacket initPacket;
	for (int i = 0; i < 2; ++i) {
		initPacket.clientCharacter[i] = i;
		initPacket.NetID[i] = 1 + i;
	}
	initPacket.clientCharacterPosX[0] = 0;
	initPacket.clientCharacterPosY[0] = 0;
	initPacket.clientCharacterPosX[1] = 13;
	initPacket.clientCharacterPosY[1] = 0;

	initPacket.blocks = createVillageBlocksData();
	initPacket.show();

	OutputMemoryStream out2;
	initPacket.Write(out2);
	char* Buffer2 = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(Buffer2, out2.GetBufferPtr(), out2.GetLength());
	clientSocket->Send(Buffer2, out2.GetLength());
	std::cout << thisclientnumber << "번 클라이언트로 이닛패킷을 보냈습니다.\n";

	//맵초기화 완료 패킷 수신
	ReadyPacket readyData;
	char* Buf = static_cast<char*>(malloc(PACKET_MAX));
	int size = clientSocket->Receive(Buf, 1470);
	InputMemoryStream in(Buf, size);
	readyData.Read(in);
	readyNumber++;

	ws.WorldData[clientNumber].netid = clientNumber;
	ws.WorldData[clientNumber].dir = 0;
	ws.WorldData[clientNumber].bomb = 0;

	while (readyNumber != startNumber) //4명되면 시작
	{
	}
	OutputMemoryStream start;
	ws.Write(start);
	char* startbuf = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(startbuf, start.GetBufferPtr(), start.GetLength());
	clientSocket->Send(startbuf, start.GetLength());


	//Receive client Move data
	while (true) {
		MovePacket moveData;
		char* Buffer3 = static_cast<char*>(malloc(PACKET_MAX));
		int size = clientSocket->Receive(Buffer3, 1470);
		if (size < 0) {	// 종료시 조건
			break;
		}
		InputMemoryStream in(Buffer3, size);
		moveData.Read(in);
		std::cout <<"클라ID : "<< moveData.NetID << "  " << moveData.x << "  " << moveData.y << std::endl;
		//moveData.show();

		ws.PacketClassify(&moveData);

		OutputMemoryStream WorldPacket;
		ws.Write(WorldPacket);
		char* Buffer = static_cast<char*>(malloc(PACKET_MAX));
		memcpy(Buffer, WorldPacket.GetBufferPtr(), WorldPacket.GetLength());
		clientSocket->Send(Buffer, WorldPacket.GetLength());
	}
	readyNumber--;
	std::cout << thisclientnumber << "번 클라이언트 접속 종료" << '\n' << std::endl;
	for (auto it = ws.WorldData.begin(); it != ws.WorldData.end(); ++it) 
	{
		if (it->first == thisclientnumber) 
		{
			ws.WorldData.erase(thisclientnumber);
			break;
		}
	}
	clientNumber = 0;
}

int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SocketAddressFactory fac;
	SocketAddress servAddr(INADDR_ANY, 9190);
	SocketAddress clientAddr;

	TCPSocketPtr ServSock = SocketUtil::CreateTCPSocket(INET);

	ServSock->Bind(servAddr);
	std::cout << "서버를 시작합니다!" << std::endl;
	std::cout << "클라이언트 접속 대기중..." << std::endl;

	srand(time(NULL));

	ServSock->Listen(5);

	while (true)
	{
		TCPSocketPtr ClientSocket;
		ClientSocket = ServSock->Accept(clientAddr);

		std::thread t1(echo, ServSock, ClientSocket);
		t1.detach();
	}

	WSACleanup();
}