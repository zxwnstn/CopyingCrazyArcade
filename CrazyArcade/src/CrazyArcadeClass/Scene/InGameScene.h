#pragma once
#include "Common/gameNode.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"

class InGameScene :
	public gameNode
{
public:
	InGameScene();
	~InGameScene();

	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();
	void afterRender();
	void debugRender();

	//for debug 
	char str[100];
	int len;

	//for gameEnd
	bool gameEnd = false;
	bool gameStart = true;
	float gameStartEnd = 1.5f;
	float pastStart = 0.f;

	bool mouseDis = false;
	float mouseDisApearDelay = 1.0f;
	float mousePastTime = 0.f;
	POINT lastMousePos;

};

