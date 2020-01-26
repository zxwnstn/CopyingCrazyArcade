#pragma once
#include "character.h"

class NetPlayer
	:public character
{
public:
	NetPlayer(int x, int y, int _netID, bool _isInNetWork = false);
	~NetPlayer();

	void update(float _deltaTime) override;
	void update(float _deltaTime, int _dir, int _isBomb, int x, int y) override;
	void sendMovePacket() override;
	bool init(CharacterType _type) override;
};

