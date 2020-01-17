#pragma once

class Boom{
public:
	Boom(BoomState _boomstate, float addedTime, BlockPosition _pos);
	~Boom();

public:
	//interface
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	
public:
	//Logic
	bool isTimeEnd() { return timeEnd; }

public:
	//getter
	const IRECT& getCollisionRect() { return collisionRect; }

private:
	//basic info
	IRECT			collisionRect;
	BoomState		state;
	BlockPosition	bPos;
	Image*			curImage = nullptr;

	//explosion logic var
	bool			timeEnd = false;
	float			pastTime = 0.f;
	float			explosionDuring = 0.2f;
};

