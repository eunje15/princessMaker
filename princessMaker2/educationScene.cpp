#include "stdafx.h"
#include "educationScene.h"
#include "princess.h"


educationScene::educationScene()
{
}


educationScene::~educationScene()
{
}

HRESULT educationScene::init(status* education, int dayCount, int idx)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	_dayOfWeek = (DAYOFWEEK)_princess->getDate().dayOfWeek;
	_day = _princess->getDate().day;

	_education = education;
	_eduName = _education->getName();
	_dayCount = dayCount;
	_idx = idx;

	if (_eduName == "자연과학")
		_type = EDU_SCHOOL;
	else if (_eduName == "시문")
		_type = EDU_POETRY;
	else if (_eduName == "신학")
		_type = EDU_THEOLOGY;
	else if (_eduName == "군사학")
		_type = EDU_STRATEGY;
	else if (_eduName == "검술")
		_type = EDU_SWORDS;
	else if (_eduName == "격투술")
		_type = EDU_FIGHTING;
	else if (_eduName == "마법")
		_type = EDU_MAGIC;
	else if (_eduName == "예법")
		_type = EDU_SCIENCE;
	else if (_eduName == "무용")
		_type = EDU_BALLET;
	else if (_eduName == "미술")
		_type = EDU_ART;

	initStatus();
	setImage();
	setTeachDialog();

	_gold = _education->getTuition();
	_success = _count = _frameCount = _dayIdx = _printDay = 0;
	_frameX = _startF;
	_fin = _goldOk = _eduFin = _noGold = _resultDialog = false;
	_statusProgress = STATUS_START;
	string str = _princess->getInfo().name + "는 오늘부터 " + _eduName + "을 배웁니다";
	setDialog(str);
	_dialogX = 20, _dialogY = WINSIZEY - 180;
	_dialogIdx = 0, _dialogType = DIALOG_ING;

	return S_OK;
}

void educationScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_statusProgress)
	{
	case STATUS_START:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_statusProgress = STATUS_TEACH;
			setDialog(_teachDialog[1]);
			_dialogX = 190, _dialogY = 235;
			_dialogIdx = 0, _dialogType = DIALOG_ING;
		}
		break;
	case STATUS_TEACH:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_statusProgress = STATUS_ING;
			_dialogType = DIALOG_FIN;
			_dialogX = 450, _dialogY = 250;
		}
		break;
	case STATUS_ING:
		if (!_goldOk)
		{
			if (_princess->getGold() > _gold)
			{
				_princess->setGold(-_gold);
				_pGold.data += _gold;
				_goldOk = true;
			}
			else
			{
				while (_dayIdx++ < _dayCount)
				{
					if (_dayOfWeek != SUN)
						_printDay++;
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
					if (_dayIdx < _dayCount)
					{
						_day++;
						_princess->setDay(_day);
						_princess->setDayOfWeek(_dayOfWeek);
					}
				}
			}
		}
		changeFrame();
		break;
	case STATUS_FIN:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_noGold)
				_fin = true;
			if (_resultDialog)
			{
				if (_princess->getGold() < _gold)
				{
					_noGold = true;
					setDialog(_teachDialog[3]);
					_dialogIdx = 0, _dialogType = DIALOG_ING;
					_dialogX = 190, _dialogY = 235;
				}
				else
					_fin = true;
			}
			else
			{
				_resultDialog = true;
				setDialog(_teachDialog[2]);
				_dialogIdx = 0, _dialogType = DIALOG_ING;
				_dialogX = 190, _dialogY = 235;
			}
		}
		break;
	}

	
}

void educationScene::render()
{
	switch (_statusProgress)
	{
	case STATUS_START:
		IMAGEMANAGER->findImage("교육액자")->render(DC, 10, WINSIZEY - 190);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		break;
	case STATUS_TEACH:
		IMAGEMANAGER->findImage("frame")->render(DC, 35, 225);
		IMAGEMANAGER->findImage("교육선생")->frameRender(DC, 45, 235, _teacherFrameX, 0);
		IMAGEMANAGER->findImage("dialogFrame")->render(DC, 180, 225);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		break;
	case STATUS_ING:
		IMAGEMANAGER->findImage("info2Back")->render(DC, 440, 238);
		if (dialogRender())
		{
			eduRender();
		}
		break;
	case STATUS_FIN:
		if (_resultDialog)
		{
			IMAGEMANAGER->findImage("frame")->render(DC, 35, 225);
			IMAGEMANAGER->findImage("교육선생")->frameRender(DC, 45, 235, _teacherFrameX, 0);
			IMAGEMANAGER->findImage("dialogFrame")->render(DC, 180, 225);
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			break;
		}
		else
		{
			IMAGEMANAGER->findImage("info2Back")->render(DC, 440, 238);
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			eduRender();
		}
		break;
	}
}

void educationScene::release()
{
}

void educationScene::initStatus()
{
	_pGold.str = "사용금액", _pGold.data = 0;

	_pGold.strRc = RectMake(45, 205, 80, 25);
	_pGold.dataRc = RectMake(125, 205, 50, 25);

	_eduStatus.clear();
	_vPStatus.clear();

	for (int i = 0; i < _education->getProperty().size(); i++)
	{
		_eduStatus.push_back(make_pair(_education->getProperty()[i].name, 0));
	}

	for (int i = 0; i < _eduStatus.size() + 1; i++)
	{
		image* img = new image;
		img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;

		if (i == _eduStatus.size())
		{
			temp.str = "스트레스";
			temp.data = _princess->getStatus().stress;
		}
		else
		{
			temp.str = _eduStatus[i].first;
			temp.data = changeStatus(_eduStatus[i].first, 0);
		}
		temp.strRc = RectMake(50 + 250 * (i % 2), 440 + (i / 2) * 50, 80, 25);
		temp.dataRc = RectMake(130 + 250 * (i % 2), 440 + (i / 2) * 50, 30, 25);

		temp.progressBar = new progressBar;
		temp.progressBar->init(160 + 250 * (i % 2), 440 + (i / 2) * 50, 110, 20);
		temp.progressBar->setGauge(temp.data, 500);

		_vPStatus.push_back(make_pair(img, temp));
	}
}

void educationScene::setImage()
{
	string str = _eduName + "배경";
	_back = IMAGEMANAGER->findImage(str);
	str = _eduName + "공주";
	_princessImg = IMAGEMANAGER->findImage(str);
	_friends.clear();
	switch (_type)
	{
	case EDU_SCHOOL:
		_friends.push_back(IMAGEMANAGER->findImage("자연과학선생"));
		_friends.push_back(IMAGEMANAGER->findImage("자연과학친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("자연과학친구2"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
		}
		break;
	case EDU_POETRY:
		_friends.push_back(IMAGEMANAGER->findImage("시문선생"));
		_friends.push_back(IMAGEMANAGER->findImage("시문친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("시문친구2"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 3;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 4, _endF = 7;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 8, _endF = 9;
		}

		break;
	case EDU_THEOLOGY:
		_friends.push_back(IMAGEMANAGER->findImage("신학선생"));
		_friends.push_back(IMAGEMANAGER->findImage("신학친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("신학친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("신학친구3"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 1;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 2, _endF = 3;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 4, _endF = 5;
		}

		break;
	case EDU_STRATEGY:
		_friends.push_back(IMAGEMANAGER->findImage("군사학선생"));
		_friends.push_back(IMAGEMANAGER->findImage("군사학친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("군사학친구2"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
		}

		break;
	case EDU_SWORDS:
		_friends.push_back(IMAGEMANAGER->findImage("검술선생"));
		_friends.push_back(IMAGEMANAGER->findImage("검술친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("검술친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("검술친구3"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 3;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 4, _endF = 5;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 6, _endF = 7;
		}

		break;
	case EDU_FIGHTING:
		_friends.push_back(IMAGEMANAGER->findImage("격투술선생"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술횃불"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술막대기"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
		}

		break;
	case EDU_MAGIC:
		_friends.push_back(IMAGEMANAGER->findImage("마법선생"));
		_friends.push_back(IMAGEMANAGER->findImage("마법횃불1"));
		_friends.push_back(IMAGEMANAGER->findImage("마법횃불2"));
		_friends.push_back(IMAGEMANAGER->findImage("마법친구1"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 7;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 8, _endF = 11;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 12, _endF = 13;
		}

		break;
	case EDU_SCIENCE:
		_friends.push_back(IMAGEMANAGER->findImage("예법선생"));
		_friends.push_back(IMAGEMANAGER->findImage("예법친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("예법친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("예법친구3"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
		}

		break;
	case EDU_BALLET:
		_friends.push_back(IMAGEMANAGER->findImage("무용선생"));
		_friends.push_back(IMAGEMANAGER->findImage("무용친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("무용친구2"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 3;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 4, _endF = 5;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 6, _endF = 7;
		}

		break;
	case EDU_ART:
		_friends.push_back(IMAGEMANAGER->findImage("미술친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("미술친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("미술선생"));

		if (selectStatus() == EDU_STUDY)
		{
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
		}
		else if (selectStatus() == EDU_SLEEP)
		{
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
		}
		else
		{
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
		}

		break;
	}
}

void educationScene::setTeachDialog()
{
	vector<string> vStr = TXTDATA->txtDataLoadSlash("dialog/선생다이얼로그.txt");
	char cStr[100000];
	strcpy(cStr, vStr[(int)_type].c_str());
	_teacherFrameX = (int)_type;
	//vector<string> temp = TXTDATA->charArraySeparation(cStr);
	_teachDialog = TXTDATA->charArraySeparation(cStr);
	//_teachDialog[1] = temp[1];
}

void educationScene::changeFrame()
{
	if (_eduFin) return;

	if (_dayIdx >= _dayCount)
	{
		setResultDialog();
		_eduFin = true;
		_princess->setEducationCountIdx(_idx);
		return;
	}
	_count++;
	if (!(_count % 5))
	{
		if (_dayOfWeek != SUN)
		{
			for (int i = 0; i < _friends.size(); i++)
			{
				if (_friends[i]->getFrameX() < _friends[i]->getMaxFrameX())
					_friends[i]->setFrameX(_friends[i]->getFrameX() + 1);
				else
					_friends[i]->setFrameX(0);
			}
			if (_frameX >= _endF)
			{
				_frameX = _startF;
				_frameCount++;
			}
			else
				_frameX++;
		}
		else
			_frameCount++;
		if (_frameCount == 3)
		{
			_day++;
			//_princess->setDay(_day);
			if (_dayOfWeek != SUN)
				_printDay++;
			_dayIdx++;
			_frameCount = 0;
			switch (_dayOfWeek)
			{
			case MON:
				_dayOfWeek = TUE;
				_goldOk = false;
				break;
			case TUE:
				_dayOfWeek = WED;
				_goldOk = false;
				break;
			case WED:
				_dayOfWeek = THU;
				_goldOk = false;
				break;
			case THU:
				_dayOfWeek = FRI;
				_goldOk = false;
				break;
			case FRI:
				_dayOfWeek = SAT;
				_goldOk = false;
				break;
			case SAT:
				_dayOfWeek = SUN;
				break;
			case SUN:
				_dayOfWeek = MON;
				_goldOk = false;
				break;
			}
			//_princess->setDayOfWeek(int(_dayOfWeek));
			if (_dayOfWeek != MON)
			{
				if (_status == EDU_STUDY)
				{
					for (int i = 0; i < _education->getProperty().size(); i++)
					{
						int randNum;
						if (_eduStatus[i].first == "항마력")
						{
							randNum = RND->getInt(2);
						}
						else
						{
							if (_education->getProperty()[i].startP != _education->getProperty()[i].endP)
								randNum = RND->getFromIntTo(_education->getProperty()[i].startP, _education->getProperty()[i].endP);
							else
								randNum = _education->getProperty()[i].endP;
						}
						changeStatus(_eduStatus[i].first, randNum);
						if (_eduStatus[i].first == "항마력")
						{
							_eduStatus[i].second -= randNum;
							_vPStatus[i].second.data -= randNum;
						}
						else
						{
							_eduStatus[i].second += randNum;
							_vPStatus[i].second.data += randNum;
						}
					}
				}
			}
			switch (_type)
			{
			case EDU_SCHOOL:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 2;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 3, _endF = 4;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 5, _endF = 6;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 2;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 3, _endF = 4;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 5, _endF = 6;
				//	break;
				//}
				break;
			case EDU_POETRY:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 3;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 4, _endF = 7;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 8, _endF = 9;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 3;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 4, _endF = 7;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 8, _endF = 9;
				//	break;
				//}
				break;
			case EDU_THEOLOGY:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 1;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 2, _endF = 3;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 4, _endF = 5;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 1;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 2, _endF = 3;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 4, _endF = 5;
				//	break;
				//}
				break;
			case EDU_STRATEGY:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 2;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 3, _endF = 4;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 5, _endF = 6;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 2;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 3, _endF = 4;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 5, _endF = 6;
				//	break;
				//}
				break;
			case EDU_SWORDS:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 3;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 4, _endF = 5;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 6, _endF = 7;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 3;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 4, _endF = 5;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 6, _endF = 7;
				//	break;
				//}
				break;
			case EDU_FIGHTING:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 2;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 3, _endF = 4;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 5, _endF = 6;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 2;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 3, _endF = 4;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 5, _endF = 6;
				//	break;
				//}
				break;
			case EDU_MAGIC:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 7;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 8, _endF = 11;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 12, _endF = 13;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 7;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 8, _endF = 11;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 12, _endF = 13;
				//	break;
				//}
				break;
			case EDU_SCIENCE:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 2;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 3, _endF = 4;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 5, _endF = 6;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 2;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 3, _endF = 4;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 5, _endF = 6;
				//	break;
				//}
				break;
			case EDU_BALLET:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 3;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 4, _endF = 5;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 6, _endF = 7;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 3;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 4, _endF = 5;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 6, _endF = 7;
				//	break;
				//}
				break;
			case EDU_ART:
				if (selectStatus() == EDU_STUDY)
				{
					_status = EDU_STUDY;
					_startF = 0, _endF = 2;
				}
				else if (selectStatus() == EDU_SLEEP)
				{
					_status = EDU_SLEEP;
					_startF = 3, _endF = 4;
				}
				else
				{
					_status = EDU_NOSTUDY;
					_startF = 5, _endF = 6;
				}
				//switch (RND->getInt(3))
				//{
				//case 0:
				//	//setDialog("서서히 성과가 나타나고 있습니다.");
				//	//_dialogType = DIALOG_FIN;
				//	_status = EDU_STUDY;
				//	_startF = 0, _endF = 2;
				//	break;
				//case 1:
				//	_status = EDU_SLEEP;
				//	_startF = 3, _endF = 4;
				//	break;
				//case 2:
				//	_status = EDU_NOSTUDY;
				//	_startF = 5, _endF = 6;
				//	break;
				//}
				break;
			}
			_frameX = _startF;
			if (_dayIdx < _dayCount)
			{
				_princess->getStatusP()->stress += 1;
				_vPStatus[_vPStatus.size() - 1].second.data += 1;
				_princess->setDay(_day);
				_princess->setDayOfWeek(_dayOfWeek);
				for (int i = 0; i < _vPStatus.size() - 1; i++)
				{
					_vPStatus[i].second.progressBar->setGauge(changeStatus(_eduStatus[i].first, 0), 500);
				}
				_vPStatus[_eduStatus.size()].second.progressBar->setGauge(_princess->getStatus().stress, 500);
			}
		}
	}
}

EDU_STATUS educationScene::selectStatus()
{
	if (_princess->getStatus().stress > _princess->getStatus().faith)
		return EDU_SLEEP;
	if (_princess->getStatus().stress > _princess->getStatus().morality)
		return EDU_NOSTUDY;
	return EDU_STUDY;
}

int educationScene::changeStatus(string name, int value)
{
	int temp;
	if (name == "지능")
	{
		temp = _princess->getStatus().intelligence;
		_princess->getStatusP()->intelligence += value;
		if (_princess->getStatus().intelligence < 0)
			_princess->getStatusP()->intelligence = 0;
	}
	else if (name == "전투기술")
	{
		temp = _princess->getStatus().warriorSkill;
		_princess->getStatusP()->warriorSkill += value;
		if (_princess->getStatus().warriorSkill < 0)
			_princess->getStatusP()->warriorSkill = 0;
	}
	else if (name == "마법기술")
	{
		temp = _princess->getStatus().magicSkill;
		_princess->getStatusP()->magicSkill += value;
		if (_princess->getStatus().magicSkill < 0)
			_princess->getStatusP()->magicSkill = 0;
	}
	else if (name == "기품")
	{
		temp = _princess->getStatus().elegance;
		_princess->getStatusP()->elegance += value;
		if (_princess->getStatus().elegance < 0)
			_princess->getStatusP()->elegance = 0;
	}
	else if (name == "체력")
	{
		temp = _princess->getStatus().hp;
		_princess->getStatusP()->hp += value;
		if (_princess->getStatus().hp < 0)
			_princess->getStatusP()->hp = 0;
	}
	else if (name == "감수성")
	{
		temp = _princess->getStatus().sensitivity;
		_princess->getStatusP()->sensitivity += value;
		if (_princess->getStatus().sensitivity < 0)
			_princess->getStatusP()->sensitivity = 0;
	}
	else if (name == "신앙심")
	{
		temp = _princess->getStatus().faith;
		_princess->getStatusP()->faith += value;
		if (_princess->getStatus().faith < 0)
			_princess->getStatusP()->faith = 0;
	}
	else if (name == "공격력")
	{
		temp = _princess->getStatus().power;
		_princess->getStatusP()->power += value;
		if (_princess->getStatus().power < 0)
			_princess->getStatusP()->power = 0;
	}
	else if (name == "방어력")
	{
		temp = _princess->getStatus().defPower;
		_princess->getStatusP()->defPower += value;
		if (_princess->getStatus().defPower < 0)
			_princess->getStatusP()->defPower = 0;
	}
	else if (name == "마력")
	{
		temp = _princess->getStatus().spell;
		_princess->getStatusP()->spell += value;
		if (_princess->getStatus().spell < 0)
			_princess->getStatusP()->spell = 0;
	}
	else if (name == "예의범절")
	{
		temp = _princess->getStatus().manner;
		_princess->getStatusP()->manner += value;
		if (_princess->getStatus().manner < 0)
			_princess->getStatusP()->manner = 0;
	}
	else if (name == "매력")
	{
		temp = _princess->getStatus().sexual;
		_princess->getStatusP()->sexual += value;
		if (_princess->getStatus().sexual < 0)
			_princess->getStatusP()->sexual = 0;
	}
	else if (name == "예술")
	{
		temp = _princess->getStatus().art;
		_princess->getStatusP()->art += value;
		if (_princess->getStatus().art < 0)
			_princess->getStatusP()->art = 0;
	}
	else if (name == "항마력")
	{
		temp = _princess->getStatus().spellDefence;
		if (value == 0)
			_princess->getStatusP()->spellDefence += 0;
		else
			_princess->getStatusP()->spellDefence += -1;

		if (_princess->getStatus().spellDefence < 0)
			_princess->getStatusP()->spellDefence = 0;
	}
	else if (name == "스트레스")
	{
		temp = _princess->getStatus().stress;
		_princess->getStatusP()->stress += value;
		if (_princess->getStatus().stress < 0)
			_princess->getStatusP()->stress = 0;
	}
	return temp;
}

void educationScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if (_vDialog.size() > 0)
		_vDialog.clear();
	if (_statusProgress == STATUS_TEACH)
		_vDialog.push_back(_teachDialog[0]);
	/*if (_statusProgess == STATUS_ING)
	{
	string temp = _eduName + " " + to_string(_dayCount + 1) + "일차";
	_vDialog.push_back(temp);
	}*/
	int strLength = 40;
	if (_statusProgress == STATUS_FIN || _statusProgress == STATUS_TEACH) strLength = 28;
	while (1)
	{
		if (strSize > strLength)
		{
			_vDialog.push_back(str.substr(idx, strLength));
			idx += strLength;
			strSize -= strLength;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

void educationScene::setResultDialog()
{
	_statusProgress = STATUS_FIN;
	_vDialog.clear();
	string str = to_string(_printDay) + "일간의 수업 결과는...";
	_vDialog.push_back(str);
	for (int i = 0; i < _eduStatus.size(); i++)
	{
		if (_eduStatus[i].second > 0)
		{
			if (_eduStatus[i].first != "항마력")
				str = _eduStatus[i].first + "이 " + to_string(_eduStatus[i].second) + "올라갔다!";
			else
				str = "항마력이 " + to_string(_eduStatus[i].second*(-1)) + "내려갔다!";
			_vDialog.push_back(str);
		}
	}
	if (_vDialog.size() == 1)
		_vDialog.push_back("아무 것도 증가하지 않았다!");
	DIALOG->setDialog(_vDialog[0], 5);
}

bool educationScene::dialogRender()
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

void educationScene::eduRender()
{
	IMAGEMANAGER->findImage("교육액자")->render(DC, 10, 240);
	int backX = 20, backY = 250;
	_back->render(DC, backX, backY);
	IMAGEMANAGER->findImage("goldBack")->render(DC, _pGold.strRc.left - 35, _pGold.strRc.top - 10);

	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(111, 17, 17));
	oldBrush = (HBRUSH)SelectObject(DC, brush);
	FillRect(DC, &_pGold.strRc, brush);
	Rectangle(DC, _pGold.strRc.left, _pGold.strRc.top, _pGold.strRc.right, _pGold.strRc.bottom);
	TextOut(DC, _pGold.strRc.left + 5, _pGold.strRc.top + 7, _pGold.str.c_str(), strlen(_pGold.str.c_str()));
	SelectObject(DC, oldBrush);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(DC, brush);
	Rectangle(DC, _pGold.dataRc.left, _pGold.dataRc.top, _pGold.dataRc.right, _pGold.dataRc.bottom);
	char str[128];
	sprintf_s(str, "%3dG", _pGold.data);
	TextOut(DC, _pGold.dataRc.left + 5, _pGold.dataRc.top + 7, str, strlen(str));
	SelectObject(DC, oldBrush);
	DeleteObject(brush);

	if (_statusProgress == STATUS_FIN) return;

	if (_dayOfWeek == SUN && (_dayIdx < _dayCount))
	{
		TextOut(DC, 450, 250, "오늘은 일요일입니다.", strlen("오늘은 일요일입니다."));
		return;
	}
	switch (_type)
	{
	case EDU_SCHOOL:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 19 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 60 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_POETRY:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 19 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 60 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_THEOLOGY:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 140 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 350 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 260 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_STRATEGY:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 50 + backX, 19 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 60 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_SWORDS:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 175 + backX, 10 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 350 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 260 + backX, 42 + backY, _frameX, 0);

		break;
	case EDU_FIGHTING:
		for (int i = 0; i < _friends.size() - 1; i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 175 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 350 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_friends[_friends.size() - 1]->render(DC, 260 + backX, 42 + backY);
		_princessImg->frameRender(DC, 260 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_MAGIC:
		for (int i = 1; i < _friends.size() - 1; i++)
		{
			_friends[i]->frameRender(DC, 88 + (i - 1) * 202 + backX, 0 + backY, _friends[i]->getFrameX(), 0);
		}
		_friends[0]->frameRender(DC, 152 + backX, 42 + backY, _friends[0]->getFrameX(), 0);
		_friends[_friends.size() - 1]->frameRender(DC, 70 + backX, 42 + backY, _friends[_friends.size() - 1]->getFrameX(), 0);
		_princessImg->frameRender(DC, 280 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_SCIENCE:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 180 + backX, 28 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 340 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 10 + (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 269 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_BALLET:
		for (int i = 0; i < _friends.size(); i++)
		{
			_friends[i]->frameRender(DC, 50 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 310 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_ART:
		_friends[0]->frameRender(DC, 89 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 160 + backX, 42 + backY, _friends[1]->getFrameX(), 0);
		_friends[_friends.size() - 1]->frameRender(DC, 310 + backX, 42 + backY, _friends[_friends.size() - 1]->getFrameX(), 0);
		_princessImg->frameRender(DC, 10 + backX, 42 + backY, _frameX, 0);
		break;
	}

	string temp = _eduName + " " + to_string(_printDay + 1) + "일차";
	TextOut(DC, 450, 250, temp.c_str(), strlen(temp.c_str()));
	char str2[128];
	switch (_status)
	{
	case EDU_STUDY:
		TextOut(DC, 445, 280, "서서히 성과가 드러나고 있습니다.", strlen("서서히 성과가 드러나고 있습니다."));
		break;
	case EDU_SLEEP:
		TextOut(DC, 445, 280, "수업에 집중을 못합니다.", strlen("수업에 집중을 못합니다."));
		break;
	case EDU_NOSTUDY:
		TextOut(DC, 445, 280, "농땡이를 피웁니다.", strlen("농땡이를 피웁니다."));
		break;
	}

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
}
