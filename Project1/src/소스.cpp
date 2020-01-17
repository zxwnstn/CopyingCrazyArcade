#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

enum ObsType {
	ObsWall,
	ObsFloor,
	ObsRope
};


class Image {

public:
	void render() {
		//do Something
		cout << "Iam image" << endl;
	}
};


class Obs {
private:
	ObsType type;
	RECT	collisionRect;
	Image*	img;

public:
	void update() {}
	void render() { img->render(); }
	void release() {}

	RECT getRect() 
	{
		return collisionRect;
	}
	ObsType getType() { return type; }
	
	void init(ObsType _type, const RECT& _rect) 
	{
		type = _type;
		collisionRect = _rect;

		switch (_type)
		{
		case ObsWall:
			img = new Image;
			break;
		case ObsFloor:
			img = new Image;
			break;
		case ObsRope:
			img = new Image;
			break;
		}
	}

};


class ObsManager {


	vector<Obs> obss;

public:

	void init() 
	{
		//푸쉬할 장애물을 만든다!
		Obs obs;

		//장애물을 설정한다!!
		RECT temp;
		temp.left = 10;
		temp.top = 10;
		temp.right = 100;
		temp.bottom = 100;
		obs.init(ObsWall, temp);
		//obss에 추가한다.!!
		obss.push_back(obs);

		//장애물을 설정한다!
		temp.left = 100;
		temp.top = 500;
		temp.right = 1000;
		temp.bottom = 600;
		obs.init(ObsFloor, temp);

		//추가한다!
		obss.push_back(obs);


	}
	void update() 
	{
		for (int i = 0; i < obss.size(); ++i)
			obss[i].update();
	}
	void render() 
	{
		for (int i = 0; i < obss.size(); ++i)
			obss[i].render();
	}

	vector<Obs> getObss() { return obss; }
	
};

ObsManager mg;

class PlayerManager 
{

	RECT playerRect;

public:
	
	void collisionCheck() 
	{
		vector<Obs> obss = mg.getObss();
		for (int i = 0; i < obss.size(); ++i) 
		{
			RECT temp;
			
			if (IntersectRect(&temp, &obss[i].getRect(), &playerRect)) {
				
				switch (obss[i].getType())
				{
				case ObsWall:
					cout << "충돌!" << endl;
					break;
				case ObsFloor:
					cout << "충돌!" << endl;
					break;
				case ObsRope:
					cout << "올라가기!" << endl;
					break;
				}	
			}

		}

	}

};



int main() {

	mg.init();
	
	while (1) {
		
		mg.update();
		mg.render();
	}

	return 0;
}