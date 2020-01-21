#pragma once
#include "character.h"

class NetPlayer
	:public character
{
public:
	NetPlayer();
	~NetPlayer();

	void update(float _deltaTime) override;
	bool init(CharacterType _type) override;

	int clientId;
};

