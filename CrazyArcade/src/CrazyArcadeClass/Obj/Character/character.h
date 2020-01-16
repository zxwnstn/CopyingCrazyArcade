#pragma once
#include "Etc/stdafx.h"
#include "CrazyArcadeClass/Obj/Item/Item.h"
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"

class character
{
public:
	character() {}
	~character() {}

	virtual bool init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;

	Direction move(Direction dir, int dist);
	void checkGetItem();
	void fallDown();
	Direction isCanMove(Direction dir);

	auto& getBombs() { return curBombList; }
	auto& getRect() { return rect; }
	CharacterState getState(){ return state; }

protected:
	FPOINT			pos;
	FPOINT			prevPos;
	int				bombRange;
	int				bombLimit;
	int				speed = 2;
	RECT			rect;
	CharacterState	state;
	const int		xMargin = 0;
	const int		yMargin = 0;

	//this info is not to collision last bomb drop area
	BlockPosition	lastBlockPos;

	//collsion with bomb
	float deadTime = 5.f;
	float deadPastTime = 0.f;

	bool usableItemList[20]{ 0, };
	vector<shared_ptr<Bomb>> curBombList;

private:
	const int slipperyDist = 30;

};

