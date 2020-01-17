#pragma once
#include "character.h"

class Player : public character
{
public:
	Player();
	~Player();

	bool init(BlockPosition _blockPos);
	void update(float deltaTime) override;

};

