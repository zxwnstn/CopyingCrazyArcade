#include "NetPlayer.h"



NetPlayer::NetPlayer(int x, int y, int _netID)
	: character(x, y)
{
	netID = _netID;
}


NetPlayer::~NetPlayer()
{
}

void NetPlayer::update(float _deltaTime)
{

}

bool NetPlayer::init(CharacterType _type)
{

	return false;
}
