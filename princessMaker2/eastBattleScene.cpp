#include "stdafx.h"
#include "eastBattleScene.h"


eastBattleScene::eastBattleScene()
{
}


eastBattleScene::~eastBattleScene()
{
}

HRESULT eastBattleScene::init()
{
	return S_OK;
}

void eastBattleScene::update()
{
}

void eastBattleScene::render()
{
	IMAGEMANAGER->findImage("fieldMap")->frameRender(DC, 0, 0, 0, 0);
	IMAGEMANAGER->findImage("�����������")->render(DC,WINSIZEX - IMAGEMANAGER->findImage("�����������")->getWidth(), 0);
}

void eastBattleScene::release()
{
}
