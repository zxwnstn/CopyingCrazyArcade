#pragma once

class Bomb
{
public:
	Bomb();
	~Bomb();

	bool init(const FPOINT& _pos, int _explosionRange);
	bool isTimeEnd() { return timeEnd; }
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();
	void explosionNow();

public:
	RECT& getRect(){ return rect; }
	int getExplosionRange() { return explosionRange; }
	BlockPosition getPos() { return pos; }

private:
	const float explosionTime = 2.5f;
	bool timeEnd = false;
	float pastTime = 0.f;
	int explosionRange;
	BlockPosition pos;
	RECT rect;
};

