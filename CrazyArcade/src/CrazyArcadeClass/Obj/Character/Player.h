#pragma once
#include "character.h"

class Player : public character
{
public:
	Player(int x, int y, bool _isInNetWork = false);
	~Player();

	bool init(CharacterType _type) override;
	void update(float deltaTime) override;
};

