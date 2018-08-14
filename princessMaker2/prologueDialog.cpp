#include "stdafx.h"
#include "prologueDialog.h"

prologueDialog::prologueDialog()
{
}


prologueDialog::~prologueDialog()
{
}

HRESULT prologueDialog::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();
	_scene = SCENE_WAR;
	_frameY = 0;
	_whoDialog = PRO_DIALOG_NONE;
	_progress = PRO_FRAME_START;
	setGodPhoto();
	setWar();
	return S_OK;
}

void prologueDialog::update()
{
	switch (_scene)
	{
		case SCENE_PROLOGUE:
			if (_loop < 1300)
				_loop += 0.8;
			else
				changeMode();
			break;
		case SCENE_WAR:
			switch (_progress)
			{
			case PRO_DIALOG_START:
				if (_whoDialog != PRO_DIALOG_NONE) break;
				if (_frameY == 2 || _frameY == 4 || _frameY == 8 || _frameY == 10)
				{
					_progress = PRO_DIALOG_FIN;
					break;
				}
				changePrintDialog();
				if (_frameY == 9) _strCount++;
				_progress = PRO_DIALOG_ING;
				/*switch (_frameY)
				{
				case 0:
					break;
				case 1:
					warUpdate();
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				}*/
			break;
			case PRO_DIALOG_ING:
				_count++;
				if (!(_count % 120)) //120이 기본
				{
					_count = 0;
					if (_isRender) _progress = PRO_DIALOG_FIN;
					else _isRender = true;
				}
			break;
			case PRO_DIALOG_FIN:
				_isRender = false;
				switch (_frameY)
				{
				case 0:
					_strCount++;
					if (_strCount < 3)
					{
						_progress = PRO_DIALOG_START;
					}
					else
						_progress = PRO_FRAME_FIN;
					break;
				case 1:
					_strCount++;
					if (_strCount == 6)
					{
						_whoDialog = PRO_DIALOG_DEVIL;
						setDialog();
						_progress = PRO_DIALOG_START;
					}
					else if (_strCount == 11)
						_progress = PRO_FRAME_FIN;
					else
						_progress = PRO_DIALOG_START;
					break;
				case 2:
					_whoDialog = PRO_DIALOG_KING;
					setDialog();
					_progress = PRO_DIALOG_START;
					break;
				case 3:
					_progress = PRO_FRAME_FIN;
					break;
				case 4:
					Sleep(2000);
					_strCount++;
					_progress = PRO_FRAME_FIN;
					break;
				case 5:
					_strCount++;
					if (_strCount < 23)
					{
						_progress = PRO_DIALOG_START;
					}
					else
						_progress = PRO_FRAME_FIN;
					break;
				case 6:
					_strCount++;
					if (_strCount < 24)
					{
						_progress = PRO_DIALOG_START;
					}
					else
						_progress = PRO_FRAME_FIN;
					break;
				case 7:
					_strCount++;
					if (_strCount < 26)
					{
						_progress = PRO_DIALOG_START;
					}
					else
						_progress = PRO_FRAME_FIN;
					break;
				case 8:
					_whoDialog = PRO_DIALOG_GOD;
					setDialog();
					_progress = PRO_DIALOG_START;
					break;
				case 9:
					_strCount++;
					if (_strCount < 37)
					{
						_strCount--;
						_progress = PRO_DIALOG_START;
					}
					else
						_progress = PRO_FRAME_FIN;
					break;
				case 10:
					_alpha2 += 2;
					if (_alpha2 >= 255)
					{
						_alpha2 = 255;
						Sleep(1000);
						_scene = SCENE_PRINCESS;
					}
					break;
				}
				break;
			case PRO_FRAME_START:
				_alpha += 3;
				if (_alpha >= 255)
				{
					_alpha = 255;
					_progress = PRO_DIALOG_START;
				}
				break;
			case PRO_FRAME_FIN:
				_alpha -= 3;
				if (_alpha <= 0)
				{
					_alpha = 0;
					_progress = PRO_FRAME_START;
					_frameY++;
					if (_frameY == 9) _alpha2 = 0;
				}
				break;
			}
			break;
		case SCENE_PRINCESS:
			SCENEMANAGER->changeScene("공주씬");
			break;
	}
}

void prologueDialog::render()
{
	switch (_scene)
	{
		case SCENE_PROLOGUE:
			prologueRender();
			break;
		case SCENE_WAR:
			warRender();
			if(_whoDialog != PRO_DIALOG_NONE)
				dialogRender();
			break;
		case SCENE_PRINCESS:
			break;
	}
}

void prologueDialog::release()
{
}


void prologueDialog::changeMode()
{
	switch (_scene)
	{
		case SCENE_PROLOGUE:
			_scene = SCENE_WAR;
			setWar();
			break;
		case SCENE_WAR:
			_frameY = 0;
		break;
		case SCENE_PRINCESS:
			break;
	}
}

void prologueDialog::setGodPhoto()
{
	_godName = _princess->getStatus().god.name;
	_godPlanet = _princess->getStatus().god.planet;
	if (_godName == "새턴")
		_godIndex = 0;
	else if (_godName == "우라누스")
		_godIndex = 1;
	else if (_godName == "넵튠")
		_godIndex = 2;
	else if (_godName == "마스")
		_godIndex = 3;
	else if (_godName == "비너스")
		_godIndex = 4;
	else if (_godName == "머큐리")
		_godIndex = 5;
	else if (_godName == "더 문")
		_godIndex = 6;
	else if (_godName == "솔")
		_godIndex = 7;
	else if (_godName == "하데스")
		_godIndex = 8;
	else if (_godName == "주피터")
		_godIndex = 9;
}

void prologueDialog::prologueRender()
{
	IMAGEMANAGER->findImage("prologue")->loopRender(DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loop);

	SetTextColor(DC, RGB(255, 255, 255));
	char str[128];
	sprintf_s(str, "루프 %f", _loop);
	TextOut(DC, 50, 100, str, strlen(str));

}

void prologueDialog::warRender()
{
	IMAGEMANAGER->findImage("war")->alphaFrameRender(DC, 0, 0, 0, _frameY, _alpha);
	if (_frameY == 10) IMAGEMANAGER->findImage("princessMaker")->alphaRender(DC, 0, 0, _alpha2);

	if ((_whoDialog == PRO_DIALOG_NONE))
	{
		if (!_isRender) return;

		HFONT font, oldFont;
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("Castellar"));
		oldFont = (HFONT)SelectObject(DC, font);
		if(_frameY >= 7 && _frameY < 9) SetTextColor(DC, RGB(0, 0, 0));
		else SetTextColor(DC, RGB(255, 255, 255));
		for (int i = 0; i < 2; i++)
		{
			if (_printDialog[i].size())
				TextOut(DC, WINSIZEX / 2 - _printDialog[i].size() * 5, WINSIZEY - 150 + i * 30, _printDialog[i].c_str(), strlen(_printDialog[i].c_str()));
		}
		SelectObject(DC, oldFont);
		DeleteObject(font);
	}
	else
		dialogRender();
}

void prologueDialog::setWar()
{
	_vDialog = TXTDATA->txtLoad("dialog/dialog.txt");
	_count = _frameY = _isAlpha = 0;
	_isRender = 1;
	_strCount = 0;
	_alpha = 0;

	//임시로 아빠이름~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	_dadName = _princess->getDadName();
	
	string temp = "(아빠성)";
	for (int i = 0; i < _vDialog.size(); i++)
	{
		size_t pos = 0;
		if ((pos = _vDialog[i].find(temp, pos)) != std::string::npos)
		{
			_vDialog[i].replace(pos, temp.length(), _dadName);
			pos += _dadName.length();
		}
	}
	temp = "(신 신이름)";
	string change = _godPlanet + " " + _godName;
	size_t pos = 0;
	if ((pos = _vDialog[26].find(temp, pos)) != std::string::npos)
	{
		_vDialog[26].replace(pos, temp.length(), change);
		pos += change.length();
	}
}


void prologueDialog::changePrintDialog()
{
	if (_strCount >= _vDialog.size()) return;

	_printDialog[0].clear();
	_printDialog[1].clear();

	bool isSlash = false;
	for (int i = 0; i < _vDialog[_strCount].size(); i++)
	{
		if (_vDialog[_strCount][i] == '/')
		{
			isSlash = true;
			_printDialog[0] = _vDialog[_strCount].substr(0, i - 1);
			_printDialog[1] = _vDialog[_strCount].substr(i + 1, _vDialog[_strCount].size());
			break;
		}
	}
	if (!isSlash) _printDialog[0] = _vDialog[_strCount];
}

void prologueDialog::setDialog()
{
	if (_whoDialog == PRO_DIALOG_NONE) return;

	if(_whoDialog == PRO_DIALOG_DEVIL)
		DIALOG->setDialog(_vDialog[_strCount], 10);
	else if (_whoDialog == PRO_DIALOG_KING)
		DIALOG->setDialog(_vDialog[_strCount], 5);
	else if(_whoDialog == PRO_DIALOG_GOD)
		DIALOG->setDialog(_vDialog[_strCount], 10);
}

void prologueDialog::dialogRender()
{
	if (_whoDialog == PRO_DIALOG_NONE) return;

	IMAGEMANAGER->findImage("war")->alphaFrameRender(DC, 0, 0, 0, _frameY, _alpha);

	IMAGEMANAGER->findImage("frame")->render(DC, WINSIZEX / 2 - 200, WINSIZEY / 2 - 100);
	IMAGEMANAGER->findImage("dialogFrame")->render(DC, WINSIZEX / 2 - 58, WINSIZEY / 2 - 100);
	if (_whoDialog == PRO_DIALOG_DEVIL)
		IMAGEMANAGER->findImage("monFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 8, 1);
	else if (_whoDialog == PRO_DIALOG_KING)
	{
		if(_strCount == 14)
			IMAGEMANAGER->findImage("peopleFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 0, 2);
		else
			IMAGEMANAGER->findImage("peopleFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 1, 2);
	}
	else if(_whoDialog == PRO_DIALOG_GOD)
		IMAGEMANAGER->findImage("godFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, _godIndex, 0);

	string str = DIALOG->getCurrentDialog();
	if (str == "end")
	{
		_strCount++;
		if (_whoDialog == PRO_DIALOG_DEVIL)
		{
			if (_strCount < 9) setDialog();
			else
			{
				_progress = PRO_DIALOG_START;
				_whoDialog = PRO_DIALOG_NONE;
			}
		}
		else if (_whoDialog == PRO_DIALOG_KING)
		{
			if (_strCount < 16) setDialog();
			else
			{
				_progress = PRO_FRAME_FIN;
				_whoDialog = PRO_DIALOG_NONE;
			}
		}
		else if (_whoDialog == PRO_DIALOG_GOD)
		{
			if (_strCount < 36) setDialog();
			else
			{
				_progress = PRO_FRAME_FIN;
				_whoDialog = PRO_DIALOG_NONE;
			}
		}
	}
	else
	{
		SetTextColor(DC, RGB(255, 255, 255));
		if(str.size() <= 30)
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, str.c_str(), strlen(str.c_str()));
		else if (str.size() <= 60)
		{
			string temp = str.substr(0, 31);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(31, str.size() - 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 60, temp.c_str(), strlen(temp.c_str()));
		}
		else if (str.size() <= 90)
		{
			string temp = str.substr(0, 31);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(31, 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 60, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(61, str.size() - 61);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 30, temp.c_str(), strlen(temp.c_str()));
		}
		else if (str.size() <= 120)
		{
			string temp = str.substr(0, 31);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(31, 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 60, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(61, 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 30, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(91, str.size() - 91);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2, temp.c_str(), strlen(temp.c_str()));
		}
	}
}
