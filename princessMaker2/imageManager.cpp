#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{

}

HRESULT imageManager::init(void)
{

	return S_OK;
}

void imageManager::release(void)
{
	deleteAll();
}


image* imageManager::addImage(string strKey, int width, int height, BOOL alpha)																			
{
	//해당 키 값을 찾아보고
	image* img = findImage(strKey);

	//그 키값을 가진 이미지가 있으면 그 이미지를 쓴다
	if (img) return img;

	//여기까지 왔다면 그 키 값은 없는 것!

	img = new image;

	//이미지를 초기화 한다, (만약 실패시 널 값 반환)
	if (FAILED(img->init(width, height, alpha)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//초기화 한 이미지를 키 값 붙여서 맵컨테이너에 추가한다
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, BOOL alpha)
{
	//해당 키 값을 찾아보고
	image* img = findImage(strKey);

	//그 키값을 가진 이미지가 있으면 그 이미지를 쓴다
	if (img) return img;

	//여기까지 왔다면 그 키 값은 없는 것!

	img = new image;

	//이미지를 초기화 한다, (만약 실패시 널 값 반환)
	if (FAILED(img->init(fileName, width, height, trans, transColor, alpha)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//초기화 한 이미지를 키 값 붙여서 맵컨테이너에 추가한다
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, BOOL alpha)
{
	//해당 키 값을 찾아보고
	image* img = findImage(strKey);

	//그 키값을 가진 이미지가 있으면 그 이미지를 쓴다
	if (img) return img;

	//여기까지 왔다면 그 키 값은 없는 것!

	img = new image;

	//이미지를 초기화 한다, (만약 실패시 널 값 반환)
	if (FAILED(img->init(fileName, x, y, width, height, trans, transColor, alpha)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//초기화 한 이미지를 키 값 붙여서 맵컨테이너에 추가한다
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


image* imageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alpha)
{
	//해당 키 값을 찾아보고
	image* img = findImage(strKey);

	//그 키값을 가진 이미지가 있으면 그 이미지를 쓴다
	if (img) return img;

	//여기까지 왔다면 그 키 값은 없는 것!

	img = new image;

	//이미지를 초기화 한다, (만약 실패시 널 값 반환)
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor, alpha)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//초기화 한 이미지를 키 값 붙여서 맵컨테이너에 추가한다
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alpha)
{
	//해당 키 값을 찾아보고
	image* img = findImage(strKey);

	//그 키값을 가진 이미지가 있으면 그 이미지를 쓴다
	if (img) return img;

	//여기까지 왔다면 그 키 값은 없는 것!

	img = new image;
	
	//이미지를 초기화 한다, (만약 실패시 널 값 반환)
	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor, alpha)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//초기화 한 이미지를 키 값 붙여서 맵컨테이너에 추가한다
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//키 값 찾는 함수
image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//찾았다
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


//싱글톤화 되어있는 이미지 지워주는 함수
BOOL imageManager::deleteImage(string strKey)
{
	//지우려는 이미지의 키 값으로 검색
	mapImageIter key = _mImageList.find(strKey);

	//지우려는 이미지를 찾았으면
	if (key != _mImageList.end())
	{
		//이미지 클래스의 릴리즈로 해당 이미지 DC및 이미지정보 릴리즈
		key->second->release();
		SAFE_DELETE(key->second);	//동적할당 제거
		_mImageList.erase(key);		//맵 컨테이너 안에서도 제거

		return true;
	}

	return false;
}


//모든 이미지 제거 함수
BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		//이미지 클래스가 있다
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return TRUE;
}


void imageManager::render(string strKey, HDC hdc)																			
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)														
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);

	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	image* img = findImage(strKey);

	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

