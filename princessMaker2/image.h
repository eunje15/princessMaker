#pragma once
//========================================
// ## 18.05.14 ## image Class ## 취업합시다
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
		//DWORD : 그냥 4Byte 
		//long  : 운영체제에 따라 바뀐다
		//int   : 운영체제에 따라 바뀐다

		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		
		float	x;				//이미지의 x좌표(left)
		float	y;				//이미지의 y좌표(top)
		int		width;			//이미지의 전체가로크기
		int		height;			//이미지의 전체세로크기

		int currentFrameX;		//현재 프레임의 번호(몇번째 프레임 X)
		int currentFrameY;		//현재 프레임의 번호(몇번쨰 프레임 Y)
		int maxFrameX;			//프레임이미지의 최대 프레임 번호
		int maxFrameY;			//프레임이미지의 최대 프레임 번호
		int frameWidth;			//한 프레임 당 가로크기
		int frameHeight;		//한 프레임 당 세로크기

		BYTE	loadType;
		RECT	boundingBox;	//급 충돌용 렉트

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
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//파일이름
	BOOL			_trans;			//특정 칼라 지울지여부
	COLORREF		_transColor;	//제외할 칼라 값

	BOOL			_blend;

	BLENDFUNCTION	_blendFunc;		//알파블렌드 관련 함수를 사용할수있음.
	LPIMAGE_INFO	_blendImage;	//알파블렌드 먹일 이미지

public:
	image();
	~image();

	//백버퍼를 옮겨와야겠다 + 이미지 초기화
	HRESULT init(int width, int height, BOOL alpha = FALSE);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0), BOOL alpha = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0), BOOL alpha = FALSE);

	//프레임 이미지 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0), BOOL alpha = FALSE);

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, BOOL alpha = FALSE);

	void release(void);

	//특정색을 다시 바꿔줘야할때 사용할 함수
	void setTransColor(BOOL trans, COLORREF transColor);

	//뿌려줄 DC에 바로 렌더링
	void render(HDC hdc);

	//렌더함수 뿌려줄DC , X좌표(left), Y좌표(top)
	void render(HDC hdc, int destX, int destY);

	//렌더함수 뿌려줄DC, 뿌려줄X,(left) 뿌려줄Y(top)   복사해올X(left),복사해올Y(top) 가로크기, 세로크기
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
	// ## 이미지를 좀 더 사용하기 위한 겟, 셋 ##
	//================================================

	//이미지 X좌표 
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	//이미지 Y좌표
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	//이미지 중점좌표
	inline void setCenter(float x, float y)
	{
		//이미지, 프레임 이미지
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

