#pragma once
#include"Common/singletonBase.h"
#include"timer.h"

class timeManager :  public singletonBase<timeManager>
{
private:

	timer * _timer;
public:
	timeManager();
	~timeManager();


	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	float getElapsedTime()const { return _timer->getElapsedTime(); }
	float getWorldTime()const { return _timer->getWorldTime(); }



};

