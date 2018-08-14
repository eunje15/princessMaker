#pragma once

//========================================
// ## 18.05.01 ## ��ũ�� ���� ##
//========================================

//inline�� �����غ��ô�
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}


//�� �ߴ� �Լ�       �Ѹ�DC���� ������ǥX ������ǥY,    ������ǥX   ������ǥY
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//��Ʈ ���� ��ũ�� �Լ�
//��Ʈ�����Լ�       ����X(left), ����Y(top), ����ũ��, ����ũ��
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width, y + height };

	return rc;
}

//��Ʈ�����Լ�  ������X(center) ������Y(center) ����ũ��, ����ũ��
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2) ,y - (height / 2),x + (width / 2), y + (height / 2) };

	return rc;
}

//�簢�� ���� ��ũ�� �Լ�

//          �簢�� �����Լ� DC����  ������X(left), ������Y(top) , ����ũ��, ����ũ��
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// �簢�� �����Լ�(����)        DC����, ������X(���� X), ������Y(���� Y), ����ũ��, ����ũ��
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