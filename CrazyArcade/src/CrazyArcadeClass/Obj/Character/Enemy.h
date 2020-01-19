#pragma once
#include "character.h"

class Enemy :
	public character
{
private:
	void moveAI(float deltaTime);

public:
	Enemy();
	Enemy(int x, int y);
	~Enemy();

	void update (float deltaTime) override;
	bool init(CharacterType _type) override;
};

