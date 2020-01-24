#pragma once
#include "CrazyArcadeClass/Obj/character/character.h"

class CharacterManager{
public:
	//interface
	bool init();
	bool init(std::vector<netCharacterInitData> _initData);
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);
	void release();
	void collision();

private:
	void collisionItem();
	void collisionCharacter();
	
public:
	//getter
	auto& getCharacters() { return characters; }

public:
	bool charactersAllDead = false;
	bool draw = false;
	bool isInNetWork = false;

private:
	vector<shared_ptr<character>> characters;

private:
	DECLARE_SINGLE(CharacterManager)
};

