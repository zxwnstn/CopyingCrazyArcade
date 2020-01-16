#pragma once
#include "HomeWorkClass/Obj/character/Enemy.h"
#include "HomeWorkClass/Obj/character/Player.h"


class CharacterManager
{

public:
	bool init();
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();
	auto& getCharacters() { return characters; }

	void collision();

private:
	vector<shared_ptr<class character>> characters;

private:
	DECLARE_SINGLE(CharacterManager)
};

