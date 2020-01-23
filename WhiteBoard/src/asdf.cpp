#include <vector>
#include <iostream>

using namespace std;

enum ItemType{
	bomb,
	powerUp,
	speedUp,
	ScoreUp
};

class item {
public:
	ItemType getType() {
		return type;
	}
	void init(ItemType _type) {
		type = _type;
	}

private:
	ItemType type;

};



class player {
public:

	void calcPower() {
		curPower = 0;
		for (int i = 0; i < items.size(); ++i) {
			if (items[i].getType() == ItemType::powerUp) {
				curPower += powerUpDegree;
			}
			curPower += basicPower;
		}
	}


private:
	vector<item> items;
	int powerUpDegree = 5;
	int basicPower = 5;
	int curPower = 0;
};


//int main() {
//	vector<int> v;
//
//
//
//}