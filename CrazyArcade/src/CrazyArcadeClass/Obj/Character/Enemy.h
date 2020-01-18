#pragma once
#include "character.h"

class Enemy :
	public character
{
	void moveAI(float deltaTime);
public:
	Enemy();
	Enemy(int x, int y);
	~Enemy();

	void update (float deltaTime) override;
	bool init() override;
};

