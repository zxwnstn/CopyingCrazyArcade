#pragma once
#include "packet.h"
#include <map>
#include <vector>

class CrazyPacket;

struct Data
{
	int netid;
	int dir;
	int bomb;
};


class WorldState
{
public:
	void Write(OutputMemoryStream& out); //WorlData RW임.
	void Read(InputMemoryStream& in);
	void PacketClassify(CrazyPacket* packet);
	size_t Header;
	std::map<int, Data> WorldData; 
};