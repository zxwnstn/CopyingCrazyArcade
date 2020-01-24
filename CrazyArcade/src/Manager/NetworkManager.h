#include "Network/packet.h"



class NetworkManager
{
public:
	//Scene단에서 연결할 ip를 넘겨받아 init한다. 
	void init(string _ip);

	void sendMoveData(char _clientID, char _playerMoveDir);
	MovePacket recvMoveData();
	IDpacket   recvID();
	InitiationPacket recvInitData();


private:
	string server_ip;
	TCPSocketPtr clientSock;
	int NetID;
	IDpacket idpacket;

private:
	DECLARE_SINGLE(NetworkManager)
};

