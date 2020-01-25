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
	virtual void update(float deltaTime, int speed, int isBomb) {}

	//init
	void rectSetFromPos();

	//render
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);

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
	bool isInBush();
	void setDropArea(IRECT oppentsBombRect);
	bool isPlayerDead() { return playerDead; }

public:
	//getter
	auto& getBombs()					{ return curBombList; }
	auto& getBlockCollisionRect()		{ return blockCollisionRect; }
	auto& getOtherCollisionRect()		{ return otherCollisionRect; }
	CharacterState getState()			{ return state; }

public:
	//item get
	void speedUp();
	void bombRangeUp()					{ if(bombRange < 8) bombRange++; }
	void bombLimitUp()					{ if(bombLimit < 10) bombLimit++; }
	void getUsableItem(ItemType type)	{ usableItemList[int(type)] = true;}

public:
	int getID()							{ return netID; }

//member var
protected:
	//theses are character basic info
	int				bombRange = 1;
	int				bombLimit = 1;
	int				speed = 3;
	Image*			moveImage;
	Image*			inBalloonImage;
	Image*			deadImage;
	Image*			characterPointer;
	CharacterType	type;
	bool			adjustSpeedHorizen = true;
	bool			adjustSpeedVertical = true;

	IRECT			blockCollisionRect;		
	IRECT			otherCollisionRect;
	POINT			pos;
	BlockPosition	bPos;
	CharacterState	state;
	CharacterState	prevState;

	//this Margin var is Set warter BombCollision judge loosen
	//this can't be more than half of player width and height (right now is setted 60) 
	const int		xMargin = 21;
	const int		yMargin = 21;

	//this info is not to collision last bomb drop area
	IRECT			lastDrop_rect;
	IRECT			prevDorp_rect;
	bool			isDropBombArea = false;
	bool			isSequenceDrop = false;


	//collsion with bomb
	float			deadTime = 6.5f;
	float			deadPastTime = 0.f;
	bool			playerDead = false;

	//item
	bool usableItemList[20]{ 0, };
	vector<shared_ptr<Bomb>> curBombList;

	//for frame render var
	bool			inBush = false;
	int				frameIndex = 0;
	float			frameCounter = 0.f;
	float			frameChageTimer = 0.1f;
	float			frameInballoonTimer = 0.4f;
	float			frameDyingTimer = 0.1f;
	float			deltaTime;

protected:
	//this for inertia witch is not consider use
	const int slipperyDist = 3;
	//this is for network play
	bool isInNetWork = false;
	int netID;
};

struct netCharacterInitData {
	int netID;
	CharacterType	type;
	int posX;
	int posY;
};