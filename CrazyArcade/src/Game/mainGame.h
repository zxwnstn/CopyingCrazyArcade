#pragma once
#include "Common/gameNode.h"

class mainGame :  public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	HRESULT init();	
	void release();
	void update();
	void render();
};

