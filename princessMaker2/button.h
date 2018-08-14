#pragma once
#include "gameNode.h"

//콜백함수 == 함수포인터
typedef void(*CALLBACK_FUNCTION)(void);

//공부를 하면 참 좋은게 있어서 알려드리러 왔습니다
//<functional> 이란 라이브러리가 있는데
//여기에 std::Function, std::bind, std::move 등등
//명령어가 존재하는데
//지금 콜백함수가 함수포인터인데 전역화 되어있기 때문에
//일반적인 방법으론 매개변수를 넣을수가 없다
//하지만 펑셔널 라이브러리를 사용하게되면 매개변수를 사용할수있다
//도전해볼 사람은 도전해보길 바람~

//함정1 아리송한게 함정
//함정2 의외로 또 간단하게 되는게 함정

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;	//버튼 상태의 이넘문

	const char* _imageName;		//이미지 이름
	image* _image;				//이미지
	RECT _rc;					//렉트

	float _x, _y;				//설정 위치

	POINT _btnDownFramePoint;	//버튼 이미지 프레임위치
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;	//콜백함수
public:
	button();
	~button();

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);

	void release();
	void update();
	void render();
};

