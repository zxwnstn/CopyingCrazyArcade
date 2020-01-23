#include "packet.h"

//critical section
int clientNumber;
bool wait = true;
std::mutex mtx;


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
	idPacket.clientID = (char)thisclientnumber;

	OutputMemoryStream out;
	idPacket.Write(out);
	char* idBuffer = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(idBuffer, out.GetBufferPtr(), out.GetLength());
	clientSocket->Send(idBuffer, out.GetLength());
	std::cout << thisclientnumber << "번 클라이언트로 ID패킷을 보냈습니다.\n";

	//Send initPacket
	InitiationPacket initPacket;
	for (int i = 0; i < 2; ++i) {
		initPacket.clientCharacter[i] = i;
		initPacket.clientCharacterPosX[i] = i;
		initPacket.clientCharacterPosY[i] = i;
		initPacket.clientID[i] = i;
	}
	initPacket.blocks = createVillageBlocksData();
	//initPacket.show();

	OutputMemoryStream out2;
	initPacket.Write(out2);
	char* initBuffer = static_cast<char*>(malloc(PACKET_MAX));
	memcpy(initBuffer, out2.GetBufferPtr(), out2.GetLength());
	clientSocket->Send(initBuffer, out2.GetLength());
	std::cout << thisclientnumber << "번 클라이언트로 이닛패킷을 보냈습니다.\n";

	//Receive client Move data
	while (true) {
		MovePacket moveData;

		char* buffer = static_cast<char*>(malloc(1470));
		int size = clientSocket->Receive(buffer, 1470);
		if (moveData.clientID == -1) // 처음 접속할 때 아이디넘버 부여
			moveData.clientID = thisclientnumber;
		if (size < 0) {	// 종료시 조건
			break;
		}
		//InputMemoryStream in(buffer, size);
		//moveData.Read(in);
		//moveData.show();
	}
	std::cout << thisclientnumber << "번 클라이언트 접속 종료" << '\n' << std::endl;
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