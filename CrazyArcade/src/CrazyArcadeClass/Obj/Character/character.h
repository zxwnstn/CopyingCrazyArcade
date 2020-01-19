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
	virtual bool init(CharacterType _type) = 0;

	//init
	void rectSetFromPos();

	//render
	void render(HDC hdc);
	void debugRender(HDC hdc);

	//move
	Direction isCanMove(Direction dir, Direction origindir);
	Direction move(Direction dir, int dist);
	int adjustSpeed(Direction dir);
	void stayDropArea();

	//state
	void checkSequenceDrop();
	void dropBomb();
	void fallDown();
	void die();

public:
	//getter
	auto& getBombs()					{ return curBombList; }
	auto& getBlockCollisionRect()		{ return blockCollisionRect; }
	auto& getOtherCollisionRect()		{ return otherCollisionRect; }
	CharacterState getState()			{ return state; }

public:
	//item get
	void speedUp()						{ if (speed < 6) speed++; } 
	void bombRangeUp()					{ if(bombRange < 8) bombRange++; }
	void bombLimitUp()					{ if(bombLimit < 10) bombLimit++; }
	void getUsableItem(ItemType type)	{ usableItemList[int(type)] = true;}

//member var
protected:
	//theses are character basic info
	int				bombRange = 1;
	int				bombLimit = 1;
	int				speed = 2;
	Image*			moveImage;
	Image*			inBalloonImage;
	Image*			deadImage;
	CharacterType	type;
	

	IRECT			blockCollisionRect;		
	IRECT			otherCollisionRect;
	POINT			pos;
	BlockPosition	bPos;
	CharacterState	state;
	CharacterState	prevState;

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
	float			deadTime = 4.8f;
	float			deadPastTime = 0.f;

	//item
	bool usableItemList[20]{ 0, };
	vector<shared_ptr<Bomb>> curBombList;

	//for frame render var
	int frameIndex = 0;
	float frameCounter = 0.f;
	float frameChageTimer = 0.1f;
	float frameInballoonTimer = 0.3f;
	float deltaTime;

private:
	//this for inertia witch is not consider use
	const int slipperyDist = 3;

};

