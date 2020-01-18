#pragma once
#include "character.h"

class Player : public character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	bool init();
	void update(float deltaTime) override;
};

