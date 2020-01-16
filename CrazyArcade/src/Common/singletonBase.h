#pragma once
//=======================================
//singletonBase(이녀석으로 싱글톤을 만든다.)
//=======================================
/*
	싱글톤 패턴은 static member로 하나의 인스턴스만
	생성된다. 프로그램 안에서 전역적으로 접근이 가능하다.

	전역변수를 선언해도 하나의 인스턴스를 유지할수 있긴 하지만
	싱글톤패턴을 사용하면 클래스 자신이 자기의 유일한 인스턴스로
	접근하는 방법을 캡슐화 하여 관리 할수 있다.
	또한 상속, 객체생성 및 소멸, 인스턴스 개수 제어 등등등..
	활용에 유리하다.

	자기 스스로가 자기의 유일한 인스턴스로 접근하는
	방법을 자체적으로 관리하는 것이 좋다.
	이녀석은 다른 인스턴스가 생성되지 않도록 처리할수 있고
	접근 방법 또한 제한을 둘수 있다.
*/
template <typename T>
class singletonBase
{
protected:
	//싱글톤 인스턴스 선언하기
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	static T* getSingleton();
	void releaseSingleton();

};

//싱글톤 인스턴스 선언
template <typename T>
T* singletonBase<T>::singleton = nullptr;

//싱글톤 객체를 가져오자
template<typename T>
T* singletonBase<T>::getSingleton()
{
	//싱글톤 객체가 없으면 새로 만들자ㅏ.
	if (!singleton)singleton = new T;

	return singleton;
}
template<typename T>
void singletonBase<T>::releaseSingleton()
{
	//싱글톤 있으면 해제
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}


