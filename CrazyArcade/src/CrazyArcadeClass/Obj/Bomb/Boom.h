#pragma once
class Boom
{

public:
	Boom(BoomState _boomstate, float addedTime, BlockPosition _pos);
	~Boom();

	bool isTimeEnd() { return timeEnd; }
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	RECT& getRect() { return rect; }

private:
	bool timeEnd = false;
	float pastTime = 0.f;
	float explosionDuring = 0.2f;
	RECT rect;
	BlockPosition pos;
	BoomState boomState;
};

