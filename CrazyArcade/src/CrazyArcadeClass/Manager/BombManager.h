#pragma once
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"
#include "CrazyArcadeClass/Obj/Bomb/Boom.h"

class BombManager
{
private:
	void generateBoom(const BlockPosition& startPoint, int explosionRange);
	void rangeCheckAndGenBoom(const BlockPosition& startPoint, int dx, int dy, int Range);
	bool inRange(int x, int y);

private:
	void collisionBoom();
	void collisionPlayer();

public:
	bool init();

	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();
	
	auto& GetBombs() { return bombs; }
	auto& GetBooms() { return booms; }
	

private:
	vector<shared_ptr<Bomb>> bombs;
	vector<shared_ptr<Boom>> booms;

private:
	//this time will be delay boomTime! so you can see bomb explosion sequencely.
	const float boomAddedTime = 0.03f;

private:
	DECLARE_SINGLE(BombManager)
};
