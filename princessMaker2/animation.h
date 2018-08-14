#pragma once
#include <vector>

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* 어떤 형태든 다 가르킬 수 있다
//뭐든지 다 포함할 수 있는 형태
//void* -> 내가 뭘 가르켰는지에 대한 캐스팅(형선언)


class animation
{
public:
	typedef vector<POINT>	vFrameList;
	typedef vector<int>		vPlayList;

private:
	
	int				_frameNum;		//애니메이션 프레임 갯수
	vFrameList		_frameList;		//프레임 리스트
	vPlayList		_playList;		//플레이 리스트

	int				_frameWidth;	//프레임 가로크기
	int				_frameHeight;	//프레임 세로크기

	BOOL			_loop;			//애니메이션 루프여부

	float			_frameUpdateSec;//한 프레임 
	float			_elapsedSec;	//경과시간

	DWORD			_nowPlayIndex;	//현재 플레이 인덱스
	BOOL			_play;			//플레이 여부

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//디폴트 애니메이션 재생
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
	
	//배열 애니메이션 재생
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);
	
	//구간 애니메이션 재생
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//애니메이션 프레임 재생속도 셋팅
	void setFPS(int framePerSec);

	//렌더링
	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

};

