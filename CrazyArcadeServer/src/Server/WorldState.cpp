#include "WorldState.h"

void WorldState::Write(OutputMemoryStream & out)
{
	//out.Write(PacketTpye::WorldState);
	// WorldDate를 순차대로 Write하자(iterator로 돌면될듯)
}

void WorldState::Read(InputMemoryStream & in)
{
	//in.Read(PacketTpye::WorldState);
	//Write와 마찬가지..
}

void WorldState::PacketClassify(CrazyPacket * packet) 
{
	//Header부터 확인한다.
	//if (Header == PacketTpye::PLAYER)
	//{
	//	//Player라면 NetID를 체크
	//	WorldData[NetID].x = 1.0f; //값갱신;
	//	WorldData[NetId].y = 2.0f;
	//}
}
