#pragma once

class Bomb{
public:
	Bomb();
	Bomb(const POINT & _pos, int _explosionRange);
	~Bomb();

public:
	//basic
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);

public:
	//logic
	bool isTimeEnd() { return timeEnd; }
	void explosionNow();

public:
	//getter
	IRECT& getCollisionRect() { return collisionRect; }
	int getExplosionRange() { return explosionRange; }
	BlockPosition getPos() { return bPos; }

private:
	//for explosion time
	const float		explosionTime = 2.f;
	bool			timeEnd = false;
	float			pastTime = 0.f;
	
	//basic info
	int				explosionRange;
	IRECT			collisionRect;
	Image*			curImage = nullptr;
	BlockPosition	bPos;

	//for frame render var
	int frameIndex = 0;
	float frameCounter = 0.f;
	float frameChageTimer = 0.3f;
	float deltaTime = 0.f;
};

