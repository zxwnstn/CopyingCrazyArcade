#pragma once
#include "character.h"

class Enemy :
	public character
{
	void moveAI(float deltaTime);
public:
	Enemy();
	~Enemy();

	void update (float deltaTime) override;

};

