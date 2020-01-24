#pragma once
#include "character.h"

class NetPlayer
	:public character
{
public:
	NetPlayer(int x, int y, int _netID, bool _isInNetWork = false);
	~NetPlayer();

	void update(float _deltaTime) override;
	bool init(CharacterType _type) override;
	int getID() { return netID; }

private:
	int netID;
};

