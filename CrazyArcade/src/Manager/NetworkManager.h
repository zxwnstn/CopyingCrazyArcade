#include "Network/packet.h"



class NetworkManager
{
public:
	//Scene단에서 연결할 ip를 넘겨받아 init한다. 
	void init(string _ip);
	void recvID();
	InitiationPacket recvInitData();
	void sendMovePacket(MovePacket& movePacket);
	void sendReadyPacket();
	WorldState recvWorldData();
	void close();


	//for client
public:
	void pushID(int id) { IDs.push_back(id); }

public:
	int getThisClientNetID();

private:
	string server_ip;
	TCPSocketPtr clientSock;

private:
	int thisClientNetID;
	std::vector<int> IDs;

private:
	DECLARE_SINGLE(NetworkManager)
};

