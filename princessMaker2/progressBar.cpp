#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarBottom = new image;
	_progressBarBottom->init("image/main/progressBack(110x20).bmp", width, height, false, RGB(255, 0, 255));

	_progressBarTop = new image;
	_progressBarTop->init("image/main/progressFront(98x10).bmp", width, 10, false, RGB(255, 0, 255));


	//_progressBarTop = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	//_progressBarBottom = IMAGEMANAGER->addImage("backBar", "hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	
	//가로크기는 이미지의 가로크기로!
	_width = width;

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(), _progressBarTop->getHeight());
}

void progressBar::render()
{
	_progressBarBottom->render(DC,_x, _y, 0, 0, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
	_progressBarTop->render(DC, _x, _y + 5, 0, 0, _width, _progressBarTop->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}