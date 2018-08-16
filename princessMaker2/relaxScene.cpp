#include "stdafx.h"
#include "relaxScene.h"
#include "princess.h"

relaxScene::relaxScene()
{
}


relaxScene::~relaxScene()
{
}

HRESULT relaxScene::init(relaxStatus * relax, int dayCount, int idx)
{
	_princess = SCENEMANAGER->getPrincessAddress();

	if (_princess->getStatus().stress <= 0)
		_princessFrameX = 1;
	else
		_princessFrameX = 0;

	_relax = relax;
	_status = RELAX_NONE;
	if (idx == 0)
		_type = RELAX_FREE;
	else
		_type = RELAX_VACATION;
	_dayCount = dayCount;

	_yearImg.img = IMAGEMANAGER->findImage("year");
	_yearImg.frameY = _princess->getDate().year - 1200;
	_monImg.img = IMAGEMANAGER->findImage("month");
	_monImg.frameY = _princess->getDate().mon - 1;
	_dayImg.img = IMAGEMANAGER->findImage("day");
	_day = _princess->getDate().day;
	_dayImg.frameY = _day - 1;
	_dayOfWeekImg.img = IMAGEMANAGER->findImage("dayOfWeek");
	_dayOfWeekImg.frameY = _dayOfWeek;

	for (int i = 0; i < 2; i++)
	{
		_selectBox[i].rc = RectMake(600, 330 + i * 28, 120, 28);
		_selectBox[i].isChoose = _selectBox[i].isSelected = false;
	}
	if (_type == RELAX_FREE)
	{
		setDialog("용돈을 주시겠습니까?");
		_selectBox[0].str = "준다";
		_selectBox[1].str = "주지않는다";
	}
	else
	{
		setDialog("어디로 가시겠습니까?");
		_selectBox[0].str = "산";
		_selectBox[1].str = "바다";
	}
	
	_dialogType = DIALOG_FIN;

	_fin = _moneyOk = false;
	_princessAnswer = -1;
	return S_OK;
}

void relaxScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_status)
	{
	case RELAX_NONE:
		_status = RELAX_SELECT;
		_dialogX = 20, _dialogY = 440;
		_dialogIdx = _dayIdx = 0;
		_dialogType = DIALOG_ING;
		break;
	case RELAX_SELECT:
		for (int i = 0; i < 2; i++)
		{
			_selectBox[i].isSelected = false;
			if (PtInRect(&_selectBox[i].rc, _ptMouse))
			{
				_selectBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					setRelax(i);
					if (i == 1 && _type == RELAX_FREE)
					{
						_princessAnswer = 0;
						setDialog("다녀오겠습니다");
						_dialogX = 360, _dialogY = 410;
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
						_status = RELAX_OK;
					}
				}
			}
		}
		break;
	case RELAX_OK:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_type == RELAX_FREE)
			{
				if (_princessAnswer == -1 && _type == RELAX_FREE)
				{
					setDialog("다녀오겠습니다.");
					_dialogX = 360, _dialogY = 410;
					_dialogIdx = 0;
					_dialogType = DIALOG_ING;
					_princessAnswer = 0;
				}
				else if (_princessAnswer == 0)
				{
					string str = "";
					if (_moneyOk)
						str = _princess->getInfo().name + "은 거리로 놀러나갔습니다.";
					else
						str = _princess->getInfo().name + "은 용돈없이 거리로 놀러나갔습니다.";
					setDialog(str);
					_dialogX = 20, _dialogY = 440;
					_princessAnswer = 1;
					_dialogIdx = 0;
					_dialogType = DIALOG_ING;
				}
				else
				{
					_status = RELAX_ING;
					_curSound = "free";
					SOUNDMANAGER->play(_curSound);
				}
			}
			else
			{
				_status = RELAX_ING;
				_curSound = "beach";
				SOUNDMANAGER->play(_curSound);
			}
		}
		break;
	case RELAX_FAIL:
		break;
	case RELAX_ING:
		_count++;
		if (!(_count % 30))
		{
			changeDay();
		}
		break;
	case RELAX_FIN:
		if (_type == RELAX_FREE)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _princessAnswer >= 2)
			{
				_fin = true;
				if(SOUNDMANAGER->isPlaySound(_curSound))
					SOUNDMANAGER->stop(_curSound);
			}
			_clickHome.isSelected = false;
			if (PtInRect(&_clickHome.rc, _ptMouse))
			{
				_clickHome.isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_princessAnswer++;
					if (_princess->getStatus().stress <= 0)
					{
						setDialog("아, 재미있었다.");
						_princessFrameX = 1;
					}
					else
					{
						setDialog("다녀왔습니다.");
						_princessFrameX = 0;
					}
					_dialogX = 360, _dialogY = 410;
					_dialogIdx = 0;
					_dialogType = DIALOG_ING;
				}
			}
		}
		else
		{
			_clickHome.isSelected = false;
			if (PtInRect(&_clickHome.rc, _ptMouse))
			{
				_clickHome.isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_fin = true;
					if (SOUNDMANAGER->isPlaySound(_curSound))
						SOUNDMANAGER->stop(_curSound);
				}
			}
		}
		break;
	}
}

void relaxScene::render()
{
	if (_fin || _status == RELAX_NONE) return;
	switch (_status)
	{
	case RELAX_SELECT:
		IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}

			IMAGEMANAGER->findImage("2Back")->render(DC, 590, 315);
			for (int i = 0; i < 2; i++)
			{
				if (_selectBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_selectBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _selectBox[i].rc.left + 2, _selectBox[i].rc.top + 5, _selectBox[i].str.c_str(), strlen(_selectBox[i].str.c_str()));
			}
		}
		break;
	case RELAX_OK:
		if (_type == RELAX_FREE)
		{
			if (_princessAnswer == 0)
			{
				IMAGEMANAGER->findImage("frame")->render(DC, 600, 400);
				IMAGEMANAGER->findImage("princessFace")->frameRender(DC, 610, 410, _princessFrameX, 0);
				IMAGEMANAGER->findImage("status2Back")->render(DC, 350, 400);
				if (dialogRender())
				{
					for (int i = 0; i < _vDialog.size(); i++)
					{
						TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
					}
				}
			}
			else
			{
				IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
				if (dialogRender())
				{
					for (int i = 0; i < _vDialog.size(); i++)
					{
						TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
					}
				}
			}
		}
		else
		{
			IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
		}
		break;
	case RELAX_FAIL:
		IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		break;
	case RELAX_ING: case RELAX_FIN:
		if (_type == RELAX_FREE)
		{
			IMAGEMANAGER->findImage("storeFrame")->render(DC, 100, 200);
			IMAGEMANAGER->findImage("자유행동사진")->render(DC, 120, 210);

			for (int i = 0; i < _vPStatus.size(); i++)
			{
				_vPStatus[i].first->render(DC, _vPStatus[i].second.strRc.left - 10, _vPStatus[i].second.strRc.top - 10);
				HBRUSH brush, oldBrush;
				brush = CreateSolidBrush(RGB(111, 17, 17));
				oldBrush = (HBRUSH)SelectObject(DC, brush);
				FillRect(DC, &_vPStatus[i].second.strRc, brush);
				Rectangle(DC, _vPStatus[i].second.strRc.left, _vPStatus[i].second.strRc.top, _vPStatus[i].second.strRc.right, _vPStatus[i].second.strRc.bottom);
				TextOut(DC, _vPStatus[i].second.strRc.left, _vPStatus[i].second.strRc.top + 2, _vPStatus[i].second.str.c_str(), strlen(_vPStatus[i].second.str.c_str()));
				SelectObject(DC, oldBrush);
				DeleteObject(brush);

				brush = CreateSolidBrush(RGB(0, 0, 0));
				oldBrush = (HBRUSH)SelectObject(DC, brush);
				Rectangle(DC, _vPStatus[i].second.dataRc.left, _vPStatus[i].second.dataRc.top, _vPStatus[i].second.dataRc.right, _vPStatus[i].second.dataRc.bottom);
				char str[128];
				sprintf_s(str, "%3d", _vPStatus[i].second.data);
				TextOut(DC, _vPStatus[i].second.dataRc.left + 2, _vPStatus[i].second.dataRc.top + 2, str, strlen(str));
				SelectObject(DC, oldBrush);
				DeleteObject(brush);

				_vPStatus[i].second.progressBar->render();
			}
			if (_status == RELAX_FIN)
			{
				if (_princessAnswer == 1)
				{
					IMAGEMANAGER->findImage("1Back")->render(DC, _clickHome.rc.left - 10, _clickHome.rc.top - 20);
					if (_clickHome.isSelected)
					{
						HBRUSH brush, oldBrush;
						brush = CreateSolidBrush(RGB(43, 0, 0));
						oldBrush = (HBRUSH)SelectObject(DC, brush);
						FillRect(DC, &_clickHome.rc, brush);
						SelectObject(DC, oldBrush);
						DeleteObject(brush);
					}
					TextOut(DC, _clickHome.rc.left + 2, _clickHome.rc.top + 5, _clickHome.str.c_str(), strlen(_clickHome.str.c_str()));
				}
				else
				{
					IMAGEMANAGER->findImage("frame")->render(DC, 600, 400);
					IMAGEMANAGER->findImage("princessFace")->frameRender(DC, 610, 410, _princessFrameX, 0);
					IMAGEMANAGER->findImage("status2Back")->render(DC, 350, 400);
					if (dialogRender())
					{
						for (int i = 0; i < _vDialog.size(); i++)
						{
							TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
						}
					}
				}
			}
			
		}
		else
		{
				IMAGEMANAGER->findImage("black")->render(DC);
				_back->frameRender(DC, 0, 100, _back->getFrameX(), _back->getFrameY());
				IMAGEMANAGER->findImage("cal")->render(DC);
				_yearImg.img->frameRender(DC, 68, 11, 0, _yearImg.frameY);
				_monImg.img->frameRender(DC, 10, 40, 0, _monImg.frameY);
				_dayOfWeekImg.img->frameRender(DC, 20, 70, 0, _dayOfWeekImg.frameY);
				_dayImg.img->frameRender(DC, 88, 38, 0, _dayImg.frameY);

				for (int i = 0; i < _vPStatus.size(); i++)
				{
					_vPStatus[i].first->render(DC, _vPStatus[i].second.strRc.left - 10, _vPStatus[i].second.strRc.top - 10);
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(111, 17, 17));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_vPStatus[i].second.strRc, brush);
					Rectangle(DC, _vPStatus[i].second.strRc.left, _vPStatus[i].second.strRc.top, _vPStatus[i].second.strRc.right, _vPStatus[i].second.strRc.bottom);
					TextOut(DC, _vPStatus[i].second.strRc.left, _vPStatus[i].second.strRc.top + 2, _vPStatus[i].second.str.c_str(), strlen(_vPStatus[i].second.str.c_str()));
					SelectObject(DC, oldBrush);
					DeleteObject(brush);

					brush = CreateSolidBrush(RGB(0, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					Rectangle(DC, _vPStatus[i].second.dataRc.left, _vPStatus[i].second.dataRc.top, _vPStatus[i].second.dataRc.right, _vPStatus[i].second.dataRc.bottom);
					char str[128];
					if(_vPStatus[i].second.str == "몸무게")
						sprintf_s(str, "%.2f", _vPStatus[i].second.data);
					else
						sprintf_s(str, "%3d", _vPStatus[i].second.data);
					TextOut(DC, _vPStatus[i].second.dataRc.left + 2, _vPStatus[i].second.dataRc.top + 2, str, strlen(str));
					SelectObject(DC, oldBrush);
					DeleteObject(brush);

					_vPStatus[i].second.progressBar->render();
			}
			if(_status == RELAX_FIN)
			{
				IMAGEMANAGER->findImage("1Back")->render(DC, _clickHome.rc.left - 10, _clickHome.rc.top - 20);
				if (_clickHome.isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_clickHome.rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _clickHome.rc.left + 2, _clickHome.rc.top + 5, _clickHome.str.c_str(), strlen(_clickHome.str.c_str()));
			}
		}
		break;
	/*case RELAX_FIN:
		if (_clickHome.isSelected)
		{
			HBRUSH brush, oldBrush;
			brush = CreateSolidBrush(RGB(43, 0, 0));
			oldBrush = (HBRUSH)SelectObject(DC, brush);
			FillRect(DC, &_clickHome.rc, brush);
			SelectObject(DC, oldBrush);
			DeleteObject(brush);
		}
		TextOut(DC, _clickHome.rc.left + 2, _clickHome.rc.top + 5, _clickHome.str.c_str(), strlen(_clickHome.str.c_str()));
		break;*/
	}
}

void relaxScene::release()
{
}

void relaxScene::setRelax(int idx)
{
	_relaxInfo = _relax->getRelaxIdx(idx);
	if (_type == RELAX_FREE)
	{
		if (idx == 0)
		{
			if (_princess->getGold() >= _princess->getInfo().age*_dayCount)
			{
				_moneyOk = true;
				string str = _princess->getInfo().name + "에게 용돈 " + to_string(_relax->getGold()*_dayCount) + "G를 줬습니다.";
				setDialog(str);
				_dialogIdx = 0;
				_princess->getStatusP()->withFather += 3;
				initStatus(1);
				_princess->setGold(_princess->getInfo().age*_dayCount);
				_status = RELAX_OK;
			}
			else
			{
				//나중에 큐브로 바꿔라
				string str = "재정상의 문제로 용돈을 주는 것은 무리입니다.";
				setDialog(str);
				_dialogIdx = 0;
				initStatus(0);
				_status = RELAX_FAIL;
			}
		}
		else
		{
			initStatus(0);
			_status = RELAX_OK;
		}
	}
	else
	{
		if (_princess->getGold() >= _dayCount*_princess->getInfo().age)
		{
			SEASON_TYPE season = _princess->getSeason();
			if (idx == 0)
				_back = IMAGEMANAGER->findImage("산사진");
			else
				_back = IMAGEMANAGER->findImage("바다사진");
			if (_princess->getInfo().age <= 11)
				_back->setFrameY(0);
			else if (_princess->getInfo().age <= 13)
				_back->setFrameY(1);
			else if (_princess->getInfo().age <= 15)
				_back->setFrameY(2);
			else
				_back->setFrameY(3);
			string str = "부녀는 함께 ";
			switch (season)
			{
			case SPRING:
				str += "봄의 ";
				_back->setFrameX(0);
				break;
			case SUMMER:
				str += "여름의 ";
				_back->setFrameX(1);
				break;
			case AUTUMN:
				str += "가을의 ";
				_back->setFrameX(2);
				break;
			case WINTER:
				str += "겨울의 ";
				_back->setFrameX(3);
				break;
			}
			if (idx == 0)
				str += "산으로 놀러갔다...";
			else
				str += "바다로 놀러갔다...";
			setDialog(str);
			_dialogIdx = 0;
			_dialogType = DIALOG_ING;
			initStatus(2);
			_status = RELAX_OK;
		}
		else
		{
			string str = "바캉스에 갈 돈이 없습니다";
			setDialog(str);
			_dialogIdx = 0;
			initStatus(3);
			_status = RELAX_FAIL;
		}
	}
}

void relaxScene::initStatus(int idx)
{
	_relaxStatus.clear();
	_vPStatus.clear();

	if (idx == 0 || idx == 1)//스트레스만
	{
		if(idx == 0)
			_relaxStatus.push_back(make_pair("스트레스", -5));
		else
			_relaxStatus.push_back(make_pair("스트레스", -10));

		image* img = new image;
		img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;

		temp.str = "스트레스";
		temp.data = _princess->getStatus().stress;

		temp.strRc = RectMake(500, 240, 80, 25);
		temp.dataRc = RectMake(580, 240, 30, 25);

		temp.progressBar = new progressBar;
		temp.progressBar->init(610, 240, 110, 20);
		temp.progressBar->setGauge(temp.data, 500);

		_vPStatus.push_back(make_pair(img, temp));
	}
	else if (idx == 2) //바캉스상태
	{
		for (int i = 0; i < 3; i++)
		{
			image* img = new image;
			img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

			tagProgress temp;

			if (i == 0)
			{
				_relaxStatus.push_back(make_pair("스트레스", _relaxInfo.stress));

				temp.str = "스트레스";
				temp.data = _princess->getStatus().stress;
			}
			else if (i == 1)
			{
				if (_relaxInfo.sensitivity == 0)
				{
					if (_relaxInfo.weight == 0)
						break;
					else
					{
						_relaxStatus.push_back(make_pair("몸무게", _relaxInfo.weight));
						temp.str = "몸무게";
						temp.data = _princess->getBodyInfo().weight;
					}
				}
				else 
				{
					_relaxStatus.push_back(make_pair("감수성", _relaxInfo.sensitivity));
					temp.str = "감수성";
					temp.data = _princess->getStatus().sensitivity;
				}
			}
			else
			{
				if (_relaxInfo.weight == 0)
					break;
				_relaxStatus.push_back(make_pair("몸무게", _relaxInfo.weight));
				temp.str = "몸무게";
				temp.data = _princess->getBodyInfo().weight;
			}

			temp.strRc = RectMake(50 + 280 * (i % 2), 480 + (i / 2) * 50, 80, 25);
			temp.dataRc = RectMake(130 + 280 * (i % 2), 480 + (i / 2) * 50, 30, 25);

			temp.progressBar = new progressBar;
			temp.progressBar->init(160 + 280 * (i % 2), 480 + (i / 2) * 50, 110, 20);
			temp.progressBar->setGauge(temp.data, 500);

			_vPStatus.push_back(make_pair(img, temp));

			if (i == 0 && temp.str == "몸무게") break;
		}
	}
	else //비용만
	{
		image* img = new image;
		img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;

		temp.str = "비용";
		temp.data = _dayCount * _princess->getInfo().age;

		temp.strRc = RectMake(500, 300, 80, 25);
		temp.dataRc = RectMake(580, 300, 30, 25);

		_vPStatus.push_back(make_pair(img, temp));
	}
}

float relaxScene::changeStatus(string name, float value)
{
	int temp;
	if (name == "스트레스")
	{
		_princess->getStatusP()->stress += value;
		if (_princess->getStatus().stress < 0)
			_princess->getStatusP()->stress = 0;
		temp = _princess->getStatus().stress;
	}
	else if (name == "감수성")
	{
		_princess->getStatusP()->sensitivity += value;
		if (_princess->getStatus().sensitivity < 0)
			_princess->getStatusP()->sensitivity = 0;
		temp = _princess->getStatus().sensitivity;
	}
	else if (name == "몸무게")
	{
		_princess->getBodyInfoP()->weight += value;
		if (_princess->getBodyInfo().weight < 0)
			_princess->getBodyInfoP()->weight = 0;
		temp = _princess->getBodyInfo().weight;
	}
	return temp;
}

void relaxScene::changeDay()
{
	_count = 0;

	if (_dayIdx < _dayCount - 1)
	{
		_day++;
		_dayIdx++;
		switch (_dayOfWeek)
		{
		case MON:
			_dayOfWeek = TUE;
			break;
		case TUE:
			_dayOfWeek = WED;
			break;
		case WED:
			_dayOfWeek = THU;
			break;
		case THU:
			_dayOfWeek = FRI;
			break;
		case FRI:
			_dayOfWeek = SAT;
			break;
		case SAT:
			_dayOfWeek = SUN;
			break;
		case SUN:
			_dayOfWeek = MON;
			break;
		}
		_princess->setDay(_day);
		_princess->setDayOfWeek(_dayOfWeek);
		_dayImg.frameY = _princess->getDate().day - 1;
		_dayOfWeekImg.frameY = _princess->getDate().dayOfWeek;
		for (int i = 0; i < _vPStatus.size(); i++)
		{
			int temp = changeStatus(_relaxStatus[i].first, _relaxStatus[i].second);
			_vPStatus[i].second.progressBar->setGauge(temp, 500);
			_vPStatus[i].second.data = temp;
		}
	}
	else
	{
		_clickHome.str = "집으로 돌아갑니다.";
		_clickHome.isSelected = false;
		_clickHome.rc = RectMake(600, 400, 150, 28);
		_status = RELAX_FIN;
	}
}

void relaxScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	while (1)
	{
		if (strSize > 40)
		{
			_vDialog.push_back(str.substr(idx, 40));
			idx += 40;
			strSize -= 40;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}


bool relaxScene::dialogRender()
{
	if (_dialogType != DIALOG_ING) return true;

	if (_dialogIdx < _vDialog.size())
	{
		string temp = DIALOG->getCurrentDialog();
		if (temp == "end")
		{
			_dialogIdx++;
			if (_dialogIdx < _vDialog.size())
				DIALOG->setDialog(_vDialog[_dialogIdx], 5);
		}
		else
		{
			if (_dialogIdx > 0)
			{
				for (int i = 0; i < _dialogIdx; i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, _dialogX, _dialogY + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
