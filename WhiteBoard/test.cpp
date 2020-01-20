#include <memory>
#include <iostream>
#include <vector>
using namespace std;
 

//싱글톤 : 전연 클래스이자, 단 하나의 인스턴스만 갖는 클래스
//디자인 패턴중 하나.
class singleTonEX {

//싱글톤 정의 영역
private:
	//싱글톤은 절대 하나의 인스턴스만 가지기 때문에,
	//생성자 소멸자의 접근지정자를 private로 둔다.
	singleTonEX() {};
	~singleTonEX() {};

public:
	//싱글톤이 되기위해 반드시 필요한 함수
	//getter함수, 싱글톤 인스턴스를 가져온다.
	static singleTonEX* getSingle() {
		if (singleTonInst == nullptr)
			singleTonInst = new singleTonEX;
		return singleTonInst; 
	}
	//싱글톤 파괴 함수, 소멸자역시 자동으로 불려지지 않기 때문에
	//싱글톤을 사용하고 난후에는 꼭 수동으로 메모리 해제를 해줘야 한다.
	static void destroy() {
		if (singleTonInst != nullptr)
			delete singleTonInst;
	}

private:
	//싱글톤 인스턴스는 내부에 스태틱으로 갖게 된다.
	static singleTonEX* singleTonInst;



//유저 정의 영역
public:

	//
	// 원하는 함수를 추가하세요!
	//


private:
	//
	//원하는 자료들을 추가하세요!!

};

//스태틱 멤버변수는 반드시 어떤 값을 지니고 있어야 한다.
//따라서 아무런 의미없는 nullptr을 넣어준다.
singleTonEX* singleTonEX::singleTonInst = nullptr;


class foo {

private:
	foo() {

	}
	~foo() {
		cout << "destruct" << endl;
	}


public:
	void something() {
		cout << "ㅗㅑ" << endl;
	}

public:
	static foo* inst;

	static foo* getSingle() {
		if (inst == nullptr)
			inst = new foo;
		return inst;
	}

	static void destroy() {
		delete inst;
	}
	

public:
	void add(int a) {
		v.push_back(a);
	}
	
	void show() {
		for (int i = 0; i < v.size(); ++i)
			cout << v[i] << endl;
	}
	void deleteVectorInt(int a) {
		for (auto it = v.begin(); it != v.end(); )
		{
			if (*it == a) 
			{
				it = v.erase(it);
			}
			else ++it;
		}
	}


public:
	vector<int>& getVector() 
	{
		return v;
	}


	int a;
	int b;
	vector<int> v;
};

foo* foo::inst = nullptr;

#define FOOMANAGER foo::getSingle()

class goo {

public:
	goo() {
		cout << "goo's constructor" << endl;
	}
	~goo() {
		cout << "goo's destructor" << endl;
	}

public:

	void something() 
	{
		vector<int>& gooVector = FOOMANAGER->getVector();

		for (int i = 0; i < gooVector.size(); ++i) 
		{
			cout << gooVector[i] << endl;
		}

		for (auto it = gooVector.begin(); it != gooVector.end(); ) {
			if (*it == 4) {
				it = gooVector.erase(it);
			}
			else ++it;
		}

		//FOOMANAGER->deleteVectorInt(4);

		for (int i = 0; i < gooVector.size(); ++i) {
			cout << gooVector[i] << endl;
		}

	}


	int a;
	int b;

};


class zoo {

public:
	zoo() {
		cout << "goo's constructor" << endl;
	}
	~zoo() {
		cout << "goo's destructor" << endl;
	}

public:

	void something() {
		vector<int> v = FOOMANAGER->getVector();
	}

	int a;
	int b;

};


int main() {

	FOOMANAGER->add(3);
	FOOMANAGER->add(4);
	FOOMANAGER->add(5);
	FOOMANAGER->add(6);
	FOOMANAGER->add(7);
	FOOMANAGER->show();

	goo g;
	g.something();

	FOOMANAGER->show();
}