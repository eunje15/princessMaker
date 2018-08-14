#pragma once
#include "singletonBase.h" 
#include <time.h>

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{

	}

	//int형 랜덤값
	inline int getInt(int num) { return rand() % num; }

	//범위로 랜덤값 정하기
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}

	//랜덤하게 float값 발생시키는 함수
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	
	//특정범위까지 float값 발생시키는 함수
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }

	//범위로 float형 난수 받아오는 함수
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}


};
