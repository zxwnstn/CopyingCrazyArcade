#pragma once
#include "CrazyArcadeClass/Obj/character/character.h"


class CharacterManager{
public:
	//interface
	bool init();
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();
	void collision();

private:
	void collisionItem();
	void collisionCharacter();
	
public:
	//getter
	auto& getCharacters() { return characters; }

private:
	vector<shared_ptr<character>> characters;

private:
	DECLARE_SINGLE(CharacterManager)
};

