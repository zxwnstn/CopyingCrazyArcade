#pragma once
#include "Etc/stdafx.h"
#include "CrazyArcadeClass/Obj/Item/Item.h"
#include "CrazyArcadeClass/Obj/Bomb/Bomb.h"

class character{
public:
	character();
	character(int x, int y);
	~character();

//member func
public:
	//update
	virtual void update(float deltaTime) = 0;
	virtual bool init() = 0;

	//init
	void rectSetFromPos();

	//render
	void render(HDC hdc);
	void debugRender(HDC hdc);

	//move
	int adjustSpeed(Direction dir);
	Direction move(Direction dir, int dist);
	Direction isCanMove(Direction dir, Direction origindir);
	void stayDropArea();

	//state
	void fallDown();
	void die();
	void dropBomb();
	void checkSequenceDrop();

public:
	//getter
	auto& getBombs() { return curBombList; }
	auto& getBlockCollisionRect() { return blockCollisionRect; }
	auto& getOtherCollisionRect() { return otherCollisionRect; }
	CharacterState getState(){ return state; }

public:
	//item get
	void speedUp() { if (speed < 6) speed++; } 
	void bombRangeUp() { if(bombRange < 8) bombRange++; }
	void bombLimitUp() { if(bombLimit < 10) bombLimit++; }
	void getUsableItem(ItemType type) {usableItemList[int(type)] = true;}

//member var
protected:
	//theses are character basic info
	int				bombRange = 1;
	int				bombLimit = 1;
	int				speed = 2;

	IRECT			blockCollisionRect;		
	IRECT			otherCollisionRect;
	POINT			pos;
	BlockPosition	bPos;
	CharacterState	state;

	//this Margin var is Set warter BombCollision judge loosen
	//this can't be more than half of player width and height (right now is setted 60) 
	const int		xMargin = 20;
	const int		yMargin = 20;

	//this info is not to collision last bomb drop area
	IRECT			lastDrop_rect;
	IRECT			prevDorp_rect;
	bool			isDropBombArea = false;
	bool			isSequenceDrop = false;

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

