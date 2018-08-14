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

	//int�� ������
	inline int getInt(int num) { return rand() % num; }

	//������ ������ ���ϱ�
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}

	//�����ϰ� float�� �߻���Ű�� �Լ�
	inline float getFloat() { return (float)rand() / (float)RAND_MAX; }
	
	//Ư���������� float�� �߻���Ű�� �Լ�
	inline float getFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }

	//������ float�� ���� �޾ƿ��� �Լ�
	inline float getFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}


};
