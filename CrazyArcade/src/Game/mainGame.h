#pragma once
#include "Common/gameNode.h"

class mainGame :  public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	HRESULT init();	//초기화
	void release();//해제
	void update();//연산하는곳
	void render();//그리는곳
};

