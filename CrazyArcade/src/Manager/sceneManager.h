#pragma once
#include "Common/singletonBase.h"


class gameNode;
class sceneManager :  public singletonBase<sceneManager>
{
private:

	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	//현재씬
	static gameNode* _currentScene;
	//목록
	mSceneList _mSceneList;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update(float deltaTime);
	void render();
	void resetCurScenen();
	void afterRender();
	void debugRender();
	
	//씬추가하기
	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);
};

