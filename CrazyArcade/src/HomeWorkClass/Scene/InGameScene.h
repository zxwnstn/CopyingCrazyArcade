#pragma once
#include "Common/gameNode.h"
#include "HomeWorkClass/Manager/BlockManager.h"
#include "HomeWorkClass/Manager/BombManager.h"
#include "HomeWorkClass/Manager/CharacterManager.h"
#include "HomeWorkClass/Manager/ItemManager.h"

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
	void debugRender();
};

