#pragma once

//========================================
// ## 18.05.01 ## 매크로 모음 ##
//========================================

//inline을 조사해봅시다
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}


//선 긋는 함수       뿌릴DC영역 시작좌표X 시작좌표Y,    도착좌표X   도착좌표Y
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//렉트 관련 매크로 함수
//렉트생성함수       기준X(left), 기준Y(top), 가로크기, 세로크기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width, y + height };

	return rc;
}

//렉트생성함수  기준점X(center) 기준점Y(center) 가로크기, 세로크기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2) ,y - (height / 2),x + (width / 2), y + (height / 2) };

	return rc;
}

//사각형 관련 매크로 함수

//          사각형 생성함수 DC영역  기준점X(left), 기준점Y(top) , 가로크기, 세로크기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// 사각형 생성함수(중점)        DC영역, 기준점X(중점 X), 기준점Y(중점 Y), 가로크기, 세로크기
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}


inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}