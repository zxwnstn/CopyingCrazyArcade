#pragma once
#include "Etc/stdafx.h"
#include "CrazyArcadeClass/Obj/Item/Item.h"
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"

class character{
public:
	character();
	~character();

//member func
public:
	//update
	virtual void update(float deltaTime) = 0;

	//init
	bool init() {};
	void rectSetFromPos();

	//render
	void render(HDC hdc);
	void debugRender(HDC hdc);

	//move
	int adjustSpeed(Direction dir);
	Direction move(Direction dir, int dist);
	Direction isCanMove(Direction dir);

	//state
	void fallDown();
	void dropBomb();

public:
	//getter
	auto& getBombs() { return curBombList; }
	auto& getBlockCollisionRect() { return blockCollisionRect; }
	auto& getOtherCollisionRect() { return otherCollisionRect; }
	CharacterState getState(){ return state; }

public:
	void speedUp() { speed++; needSpeedAdjust = true; }
	void rangeUp() { bombRange++; }
	void bombLimitUp() { bombLimit++; }
	void getUsableItem(ItemType type) {
		usableItemList[int(type)] = true;
	}

//member var
protected:
	//theses are character basic info
	int				bombRange = 1;
	int				bombLimit = 1;
	int				speed = 2;
	bool			needSpeedAdjust = false;

	IRECT			blockCollisionRect;		
	IRECT			otherCollisionRect;
	POINT			pos;
	BlockPosition	bPos;
	CharacterState	state;

	//this Margin var is Set warter BombCollision judge loosen
	//this can't be more than player width and height (right now in on 60) 
	const int		xMargin = 20;
	const int		yMargin = 20;

	//this info is not to collision last bomb drop area
	IRECT			dropAndMoveRect;
	BlockPosition	lastBlockPos;
	BlockPosition	prevLastBlcokPos;

	//collsion with bomb
	float deadTime = 5.f;
	float deadPastTime = 0.f;

	//item
	bool usableItemList[20]{ 0, };
	vector<shared_ptr<Bomb>> curBombList;

private:
	//this for inertia witch is not consider use
	const int slipperyDist = 3;

};

