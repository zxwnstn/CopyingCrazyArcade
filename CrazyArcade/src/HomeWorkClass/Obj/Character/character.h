#pragma once
#include "Etc/stdafx.h"
#include "HomeWorkClass/Obj/Item/Item.h"
#include "HomeWorkClass/Obj/Bomb/Bomb.h"

class character
{
public:
	character() {}
	~character() {}

	virtual bool init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;

	auto& getBombs() { return curBombList; }

protected:
	FPOINT			pos;
	FPOINT			prevPos;
	int				bombRange;
	int				bombLimit;
	int				speed;
	RECT			rect;
	CharacterState	state;
	const int		xMargin = 2;
	const int		yMargin = 2;

	//collsion with bomb
	float deadTime = 5.f;
	float deadPastTime = 0.f;

	vector<shared_ptr<Item>> usableItemList;
	vector<shared_ptr<Bomb>> curBombList;

};

