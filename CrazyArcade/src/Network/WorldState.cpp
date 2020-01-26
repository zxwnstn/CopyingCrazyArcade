#include "WorldState.h"

void WorldState::Write(OutputMemoryStream & out)
{
	out.Write(WorldData.size());
	for (auto Datas = WorldData.begin(); Datas != WorldData.end(); Datas++)
	{
		out.Write(Datas->second.netid);
		out.Write(Datas->second.dir);
		out.Write(Datas->second.bomb);
		out.Write(Datas->second.x);
		out.Write(Datas->second.y);
	}
}

void WorldState::Read(InputMemoryStream & in)
{
	int range = 0;
	int NetID = 0;
	int playerMoveDir = 0;
	int isBomb = 0;
	int x, y;
	in.Read(range);
	for (int i = 0; i < range; i++)
	{
		in.Read(NetID);
		in.Read(playerMoveDir);
		in.Read(isBomb);
		WorldData[NetID].netid = NetID;
		WorldData[NetID].dir = playerMoveDir;
		WorldData[NetID].bomb = isBomb;
		WorldData[NetID].x = x;
		WorldData[NetID].y = y;
	}
}

void WorldState::PacketClassify(CrazyPacket * packet) 
{
	if (packet->GetPacketTpye() == PacketTpye::PLAYER)
	{
		WorldData[packet->GetNetID()].netid = packet->GetNetID();
		WorldData[packet->GetNetID()].dir = packet->GetDir();
		WorldData[packet->GetNetID()].bomb = packet->GetBomb();
		WorldData[packet->GetNetID()].x = packet->GetX();
		WorldData[packet->GetNetID()].y = packet->GetY();
	}
}
