#pragma once
class timer
{
private:
	float _timeScale;
	float _timeElapsed;	//��ȣ�� �Դٰ��� -> �� �ֱ� 0.001

	__int64 _curTime;			// ���� �ֱ�
	__int64 _lastTime;			// ������ ����Ÿ��
	__int64 _periodFrequency;	

	unsigned long _frameRate;
	unsigned long _FPSframeCount;

	float _FPSTimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }
};

