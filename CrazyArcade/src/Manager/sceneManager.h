#pragma once
#include "Common/singletonBase.h"


class gameNode;
class sceneManager :  public singletonBase<sceneManager>
{
private:

	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//ÇöÀç¾À
	static gameNode* _currentScene;
	//¸ñ·Ï
	mSceneList _mSceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();
	void debugRender();
	
	//¾ÀÃß°¡ÇÏ±â
	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);
};

