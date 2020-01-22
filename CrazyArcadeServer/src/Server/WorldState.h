#pragma once
#include "packet.h"
#include <map>
#include <vector>

class WorldState
{


public:
	// 클라이언트는 WorldPacket을 보내는것이아니라 Packet만 보낸다. 
	void Write(OutputMemoryStream& out);
	void Read(InputMemoryStream& in);

private:
	void PacketClassify(CrazyPacket* packet);

private:
	size_t Header;
	std::map<int, std::vector<float>> WorldData; 
	// 여기에 플레이어들의 정보와 물풍선정보를 넣음
	// 플레이어의 키값은 1부터(NetID)로 할당
	// 물풍선은 1000번대부터 생성(최대 21억개 생성가능)
	// value는 각 키값의 x y좌표가 들어감. 
	// 이거만 Write해서 패킷으로보내면됨.
	// 플레이어의 경우 value는 NetID, x, y 가 들어감. (수정해야할듯)
};