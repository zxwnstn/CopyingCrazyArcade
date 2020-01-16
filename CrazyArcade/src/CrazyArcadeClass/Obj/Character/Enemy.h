#pragma once
#include "character.h"

class Enemy :
	public character
{
	void moveAI(float deltaTime);
public:
	Enemy();
	~Enemy();


	bool init() override;
	void update (float deltaTime) override;
	void render (HDC hdc) override;
	void debugRender(HDC hdc) override;
};

