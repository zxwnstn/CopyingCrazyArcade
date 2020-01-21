//#include "PCH.h"
//#include <iostream>
//#include <thread>
//#include <mutex>
//#include "MemoryStream.h"
//#include "protocol.h"
//
//#pragma comment(lib, "ws2_32")
//
//class Player
//{
//public:
//	int	mPlayerId = -1;
//	int	mPosX;
//	int	mPosY;
//
//	void Write(OutputMemoryStream& inStream) const;
//	void Read(InputMemoryStream& inStream)
//	{
//		inStream.Read(mPlayerId);
//		inStream.Read(mPosX);
//		inStream.Read(mPosY);
//		
//	}
//};
//void Player::Write(OutputMemoryStream& inStream) const
//{
//	inStream.Write(mPlayerId);
//	inStream.Write(mPosX);
//	inStream.Write(mPosY);
//}
//
//int clientNumber = 0; //critical section 처리필요함.
//Player c1{ };
//
//
//void print(const Player& remsg, const int thisclientNumber)
//{
//	std::cout << thisclientNumber << "번 클라이언트 정보" << std::endl;
//	std::cout << "이름 : " << remsg.mPlayerId << std::endl;
//	std::cout << "현재위치 : " << remsg.mPosX<< ", " << remsg.mPosY << '\n' << std::endl;
//}
//
//bool wait = true;
//std::mutex mtx;
//
//
//void echo(TCPSocketPtr ServSock, TCPSocketPtr ClientSocket)
//{
//	clientNumber++; // critical section
//	std::cout << clientNumber << "번 클라이언트가 접속하였습니다!!" << std::endl;
//	int thisclientNumber = clientNumber;
//	while (true) {
//		Player user;
//
//		char* Buffer = static_cast<char*>(malloc(1470));
//
//		int size = ClientSocket->Receive(Buffer, 1470);
//		if (user.mPlayerId == -1) // 처음 접속할 때 아이디넘버 부여
//			user.mPlayerId = thisclientNumber;
//		if (size < 0) {
//			break;
//		}
//		InputMemoryStream in(Buffer, size);
//		user.Read(in);
//		print(user, thisclientNumber);
//		ClientSocket->Send(Buffer, size);
//
//		size = ClientSocket->Receive(Buffer, 1470);
//		if (size < 0) {
//			break;
//		}
//	}
//	std::cout << thisclientNumber << "번 클라이언트 접속 종료" << '\n' << std::endl;
//}
//
//int main()
//{
//	WSADATA wsaData;
//	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//	SocketAddressFactory fac;
//	SocketAddress servAddr(INADDR_ANY, 9190);//중요!
//	SocketAddress clientAddr;
//
//	TCPSocketPtr ServSock = SocketUtil::CreateTCPSocket(INET);
//
//	ServSock->Bind(servAddr);
//	std::cout << "서버를 시작합니다!" << std::endl;
//	std::cout << "클라이언트 접속 대기중..." << std::endl;
//
//	ServSock->Listen(5);
//
//	while (true)
//	{
//		TCPSocketPtr ClientSocket;
//		ClientSocket = ServSock->Accept(clientAddr);
//
//		std::thread t1(echo, ServSock, ClientSocket);
//		t1.detach();
//	}
//
//	WSACleanup();
//}