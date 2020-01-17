#pragma once
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"
#include "CrazyArcadeClass/Obj/Bomb/Boom.h"

class BombManager{
private:
	//GenerateBoom
	bool inRange(int x, int y);
	void generateBoom(const BlockPosition& startPoint, int explosionRange);
	void rangeCheckAndGenBoom(const BlockPosition& startPoint, int dx, int dy, int Range);

private:
	void collisionBoom();
	void collisionPlayer();
	void collisionItem();

public:
	//interface
	bool init();
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();
	
public:
	//getter
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

