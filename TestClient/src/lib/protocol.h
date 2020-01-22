#pragma once
#include <memory>

#define MAX_CHAT_LEN	1024

#define MAX_NAME_LEN	30
#define MAX_COMMENT_LEN	40

enum PacketTypes
{
	PKT_NONE = 0,
	PKT_PLAYER = 1,
	PKT_BOMB = 2,
	PKT_MAX = 1024
};

#pragma pack(push, 1)

struct PacketHeader
{
	PacketHeader() : mSize(0), mType(PKT_NONE) {}
	short mSize;
	short mType;
};


struct PlayerPacket : public PacketHeader
{
	PlayerPacket()
	{
		mSize = sizeof(PlayerPacket);
		mType = PKT_PLAYER;
		mPlayerId = -1;
		//memset(mName, 0, MAX_NAME_LEN);
	}

	int	mPlayerId;
	int	mPosX;
	int	mPosY;
	//char	mName[MAX_NAME_LEN]; ÇöÀç·Î½ã µüÈ÷ ÇÊ¿ä¾øÀ½.

};

struct BombPacket : public PacketHeader
{
	BombPacket()
	{
		mSize = sizeof(BombPacket);
		mType = PKT_BOMB;
		mPlayerId = -1;
		explostionTime = 0.f;
		pastTime = 0.f;
		//memset();
	}

	int	mPlayerId;
	int mPosX;
	int mPosY;
	float explostionTime;
	float pastTime;
};


#pragma pack(pop)