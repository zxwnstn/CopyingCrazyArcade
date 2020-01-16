#pragma once
#include "Common/gameNode.h"

class Scene :
	public gameNode
{
public:

	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();

	Scene();
	~Scene();
};

