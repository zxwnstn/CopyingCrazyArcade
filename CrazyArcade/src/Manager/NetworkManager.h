#include "Network/packet.h"



class NetworkManager
{
public:
	//Scene�ܿ��� ������ ip�� �Ѱܹ޾� init�Ѵ�. 
	void init(string _ip);

	void sendMoveData(char _clientID, char _playerMoveDir);
	MovePacket recvMoveData();
	IDpacket   recvID();
	InitiationPacket recvInitData();


private:
	string server_ip;
	TCPSocketPtr clientSock;
	int grantedID;

private:
	DECLARE_SINGLE(NetworkManager)
};
