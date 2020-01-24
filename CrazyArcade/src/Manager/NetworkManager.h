#include "Network/packet.h"



class NetworkManager
{
public:
	//Scene단에서 연결할 ip를 넘겨받아 init한다. 
	void init(string _ip);
	void recvID();
	InitiationPacket recvInitData();
	void sendMoveData(char _clientID, char _playerMoveDir);
	MovePacket recvMoveData();

public:
	int getNetID();

private:
	string server_ip;
	TCPSocketPtr clientSock;
	int netID;

private:
	DECLARE_SINGLE(NetworkManager)
};

