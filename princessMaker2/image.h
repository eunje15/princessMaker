#pragma once
//========================================
// ## 18.05.14 ## image Class ## ����սô�
//========================================

#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		//DWORD : �׳� 4Byte 
		//long  : �ü���� ���� �ٲ��
		//int   : �ü���� ���� �ٲ��

		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		
		float	x;				//�̹����� x��ǥ(left)
		float	y;				//�̹����� y��ǥ(top)
		int		width;			//�̹����� ��ü����ũ��
		int		height;			//�̹����� ��ü����ũ��

		int currentFrameX;		//���� �������� ��ȣ(���° ������ X)
		int currentFrameY;		//���� �������� ��ȣ(����� ������ Y)
		int maxFrameX;			//�������̹����� �ִ� ������ ��ȣ
		int maxFrameY;			//�������̹����� �ִ� ������ ��ȣ
		int frameWidth;			//�� ������ �� ����ũ��
		int frameHeight;		//�� ������ �� ����ũ��

		BYTE	loadType;
		RECT	boundingBox;	//�� �浹�� ��Ʈ

		tagImageInfo()
		{
			resID			= 0;
			hMemDC			= NULL;
			hBit			= NULL;
			hOBit			= NULL;
			x				= NULL;
			y				= NULL;
			width			= NULL;
			height			= NULL;
			currentFrameX	= NULL;
			currentFrameY	= NULL;
			maxFrameX		= NULL;
			maxFrameY		= NULL;
			frameWidth		= NULL;
			frameHeight		= NULL;
			loadType		= LOAD_RESOURCE;
			boundingBox		= RectMake(0, 0, 0, 0);
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	CHAR*			_fileName;		//�����̸�
	BOOL			_trans;			//Ư�� Į�� ����������
	COLORREF		_transColor;	//������ Į�� ��

	BOOL			_blend;

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ���� �Լ��� ����Ҽ�����.
	LPIMAGE_INFO	_blendImage;	//���ĺ��� ���� �̹���

public:
	image();
	~image();

	//����۸� �Űܿ;߰ڴ� + �̹��� �ʱ�ȭ
	HRESULT init(int width, int height, BOOL alpha = FALSE);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0), BOOL alpha = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0), BOOL alpha = FALSE);

	//������ �̹��� �ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0), BOOL alpha = FALSE);

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	void release(void);

	//Ư������ �ٽ� �ٲ�����Ҷ� ����� �Լ�
	void setTransColor(BOOL trans, COLORREF transColor);

	//�ѷ��� DC�� �ٷ� ������
	void render(HDC hdc);

	//�����Լ� �ѷ���DC , X��ǥ(left), Y��ǥ(top)
	void render(HDC hdc, int destX, int destY);

	//�����Լ� �ѷ���DC, �ѷ���X,(left) �ѷ���Y(top)   �����ؿ�X(left),�����ؿ�Y(top) ����ũ��, ����ũ��
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void alphaLoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	void transRender(HDC hdc, int destX, int destY, bool isTrans);
	void transRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, bool isTrans);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//================================================
	// ## �̹����� �� �� ����ϱ� ���� ��, �� ##
	//================================================

	//�̹��� X��ǥ 
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	//�̹��� Y��ǥ
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	//�̹��� ������ǥ
	inline void setCenter(float x, float y)
	{
		//�̹���, ������ �̹���
		if (_imageInfo->maxFrameX <= 0)
		{
			_imageInfo->x = x - (_imageInfo->width / 2);
			_imageInfo->y = y - (_imageInfo->height / 2);
		}
		else
		{
			_imageInfo->x = x - (_imageInfo->frameWidth / 2);
			_imageInfo->y = y - (_imageInfo->frameHeight / 2);
		}
		
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}
	
	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	inline RECT boundingBox()
	{
		RECT rc = { _imageInfo->x,
					_imageInfo->y,
					_imageInfo->x + _imageInfo->width,
					_imageInfo->y + _imageInfo->height };

		return rc;
	}

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

};

