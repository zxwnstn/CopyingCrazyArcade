#include "Common/gameNode.h"
#include "CrazyArcadeClass/Manager/BlockManager.h"
#include "CrazyArcadeClass/Manager/BombManager.h"
#include "CrazyArcadeClass/Manager/CharacterManager.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"

class NetWorkScene
	: public gameNode
{
public:
	NetWorkScene();
	~NetWorkScene();

	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();
	void afterRender();
	void debugRender();

private:
	void uiUpdate(float deltaTime);

private:
	//for debug 
	TCHAR str[100];
	TCHAR rtt[100];

	float m_roundTripTime = 0.0f;

	int len;
	int rttlen;
	int bgmSelector;

	//for character all die and game End
	bool gameEnd = false;
	bool gameDraw = false;
	bool gameStart = true;
	float gameStartEnd = 1.5f;
	float pastStart = 0.f;

	bool mouseDis = false;
	float mouseDisApearDelay = 1.0f;
	float mousePastTime = 0.f;
	POINT lastMousePos;

	//for exit button
	RECT exitButtonRect = { 975, 844, 1175, 887 };
	bool exitMouseSetted;

	bool SceneFinal = false;
	Image* loadingImage;

};