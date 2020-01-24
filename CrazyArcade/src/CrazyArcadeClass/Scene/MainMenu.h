#pragma once
#include "Common/gameNode.h"


class MainMenu
	: public gameNode
{
public:
	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();

public:
	bool mouseSettedStart = false;
	bool mouseSettedExit = false;
	bool mouseSettedTcp = false;

	RECT startButtonRect;
	RECT exitButtonRect;
	RECT tcpButtonRect;

	Image* startButtonImage;
	Image* exitButtonImage;
	Image* tcpButtonImage;

};