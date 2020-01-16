#pragma once
#include "Common/singletonBase.h"

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction(){}

	//지정한 숫자범위내에서 난수를 받아온다.0~지정한 숫자
	inline int getInt(int num)
	{
		return rand() % num;
	}
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};
