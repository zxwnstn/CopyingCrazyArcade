#pragma once
#include "character.h"

class Player : public character
{
	void rectSetFromPos();
	bool isCollison();
	void dropBomb();

public:
	Player();
	~Player();

	bool init() override;
	void update(float deltaTime) override;
	void render(HDC hdc) override;
	void debugRender(HDC hdc) override;
	
};

