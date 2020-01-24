#pragma once
#include "character.h"

class Player2 :
	public character
{

public:
	Player2(int x, int y);
	~Player2();

	void update (float deltaTime) override;
	bool init(CharacterType _type) override;
};

