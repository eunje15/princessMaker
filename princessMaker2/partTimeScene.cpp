#include "stdafx.h"
#include "partTimeScene.h"
#include "princess.h"

partTimeScene::partTimeScene()
{
}


partTimeScene::~partTimeScene()
{
}

HRESULT partTimeScene::init(workStatus* work, int dayCount, int idx)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	_dayOfWeek = (DAYOFWEEK)_princess->getDate().dayOfWeek;
	_day = _princess->getDate().day;

	_idx = idx;
	_work = work;
	_workName = _work->getName();
	_dayCount = dayCount;

	if (_workName == "집안일")
		_type = WORK_HOUSE;
	else if (_workName == "보모")
		_type = WORK_NURSERY;
	else if (_workName == "여관")
		_type = WORK_INN;
	else if (_workName == "농장")
		_type = WORK_FARM;
	else if (_workName == "성당")
		_type = WORK_CHURCH;
	else if (_workName == "레스토랑")
		_type = WORK_RESTAURANT;
	else if (_workName == "나무꾼")
		_type = WORK_WOOD;
	else if (_workName == "미용실")
		_type = WORK_HAIR;
	else if (_workName == "미장이")
		_type = WORK_PLASTERER;
	else if (_workName == "사냥꾼")
		_type = WORK_HUNTER;
	else if (_workName == "묘지기")
		_type = WORK_GRAVE;
	else if (_workName == "가정교사")
		_type = WORK_COACH;
	else if (_workName == "주점")
		_type = WORK_DRINK;
	else if (_workName == "밤의주점")
		_type = WORK_NIGHT_DRINK;
	else if (_workName == "밤의전당")
		_type = WORK_NIGHT_CLUB;

	initStatus();
	setImage();
	setTeachDialog();

	_gold = _work->getSalary();
	_success = _count = _frameCount = _dayIdx = _printDay = 0;
	_frameX = _startF;
	_fin = _workFin = false;
	_goldOk = true;
	_progress = STATUS_START;
	string str = _princess->getInfo().name + "은/는 오늘부터 " + _workName + " 일을 시작합니다.";
	setDialog(str);
	_dialogX = 20, _dialogY = WINSIZEY - 180;
	_dialogIdx = 0, _dialogType = DIALOG_ING;

	return S_OK;
}

void partTimeScene::update()
{
	if (_fin) return;
	if (_dialogType == DIALOG_ING) return;
	switch (_progress)
	{
	case STATUS_START:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_progress = STATUS_TEACH;
			if (_workStart)
				setDialog(_teachDialog[1]);
			else
				setDialog(_teachDialog[2]);
			_dialogX = 190, _dialogY = 235;
			_dialogIdx = 0, _dialogType = DIALOG_ING;
		}
		break;
	case STATUS_TEACH:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_progress = STATUS_ING;
			_dialogType = DIALOG_FIN;
			_dialogX = 450, _dialogY = 250;
		}
		break;
	case STATUS_ING:
		/*if (!_goldOk)
		{
		_princess->setGold(_gold);
		_pGold.data += _gold;
		_goldOk = true;
		}*/
		changeFrame();
		break;
	case STATUS_FIN:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_fin = true;
		}
		break;
	}
}

void partTimeScene::render()
{
	if (_fin) return;

	switch (_progress)
	{
	case STATUS_START:
		IMAGEMANAGER->findImage("알바액자")->render(DC, 10, WINSIZEY - 190);
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
		IMAGEMANAGER->findImage("알바선생")->frameRender(DC, 45, 235, _teacherFrameX, 0);
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
			workRender();
		}

		//char str[128];
		//sprintf_s(str, "print : %d, success : %d", _printDay, _success);
		//TextOut(DC, WINSIZEX / 2, 50, str, strlen(str));
		break;
	case STATUS_FIN:
		IMAGEMANAGER->findImage("frame")->render(DC, 35, 225);
		IMAGEMANAGER->findImage("알바선생")->frameRender(DC, 45, 235, _teacherFrameX, 0);
		IMAGEMANAGER->findImage("dialogFrame")->render(DC, 180, 225);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		if (_workName != "집안일" && _success > 0)
		{
			char str[128];
			sprintf_s(str, "%d일 분으로 %dG", _printDay, _pGold.data);
			TextOut(DC, _dialogX, _dialogY + (_vDialog.size()) * 30, str, strlen(str));
		}
		break;
	}
}

void partTimeScene::release()
{
}

void partTimeScene::initStatus()
{
	_pGold.str = "수입", _pGold.data = 0;

	_pGold.strRc = RectMake(45, 205, 80, 25);
	_pGold.dataRc = RectMake(125, 205, 50, 25);

	_workStatus.clear();
	_vPStatus.clear();

	for (int i = 0; i < _work->getProperty().size(); i++)
	{
		_workStatus.push_back(make_pair(_work->getProperty()[i].first, 0));
	}

	for (int i = 0; i < _workStatus.size() + 1; i++)
	{
		image* img = new image;
		img->init("image/education/progressBack(240x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;
		if (i == _workStatus.size())
		{
			temp.str = "스트레스";
			temp.data = _princess->getStatus().stress;
		}
		else
		{
			temp.str = _workStatus[i].first;
			temp.data = changeStatus(_workStatus[i].first, 0);
		}

		temp.strRc = RectMake(50 + 250 * (i % 2), 440 + (i / 2) * 50, 80, 25);
		temp.dataRc = RectMake(130 + 250 * (i % 2), 440 + (i / 2) * 50, 30, 25);

		temp.progressBar = new progressBar;
		temp.progressBar->init(160 + 250 * (i % 2), 440 + (i / 2) * 50, 110, 20);
		temp.progressBar->setGauge(temp.data, 500);

		_vPStatus.push_back(make_pair(img, temp));
	}
}

void partTimeScene::setImage()
{
	//이미지 따기]
	string str = _workName + "배경";
	_back = IMAGEMANAGER->findImage(str);
	str = _workName + "공주";
	_princessImg = IMAGEMANAGER->findImage(str);
	_friends.clear();
	switch (_type)
	{
	case WORK_HOUSE:
		_friends.push_back(IMAGEMANAGER->findImage("집안일선생"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 2;
			_friends[0]->setFrameX(0);

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 2, _endF = 7;
			_friends[0]->setFrameX(1);

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 8, _endF = 9;
			_friends[0]->setFrameX(1);

		}
		break;
	case WORK_NURSERY:
		_friends.push_back(IMAGEMANAGER->findImage("보모선생"));
		_friends.push_back(IMAGEMANAGER->findImage("보모친구1"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 4, _endF = 7;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 8, _endF = 9;

		}
		break;
	case WORK_INN:
		_friends.push_back(IMAGEMANAGER->findImage("여관선생"));
		_friends.push_back(IMAGEMANAGER->findImage("여관닭"));
		_friends.push_back(IMAGEMANAGER->findImage("여관이불"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 4, _endF = 8;
			_friends[2]->setFrameX(0);

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 9, _endF = 10;

		}
		break;
	case WORK_FARM:
		_friends.push_back(IMAGEMANAGER->findImage("농장선생"));
		_friends.push_back(IMAGEMANAGER->findImage("농장오리"));
		_friends.push_back(IMAGEMANAGER->findImage("농장풍차1"));
		_friends.push_back(IMAGEMANAGER->findImage("농장풍차2"));
		_friends.push_back(IMAGEMANAGER->findImage("말머리"));
		_friends.push_back(IMAGEMANAGER->findImage("말궁둥이"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 4;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 5, _endF = 9;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 10, _endF = 11;

		}
		break;
	case WORK_CHURCH:
		_friends.push_back(IMAGEMANAGER->findImage("성당선생"));
		_friends.push_back(IMAGEMANAGER->findImage("성당책상"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 4, _endF = 5;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 6, _endF = 7;

		}
		break;
	case WORK_RESTAURANT:
		_friends.push_back(IMAGEMANAGER->findImage("레스토랑불"));
		_friends.push_back(IMAGEMANAGER->findImage("레스토랑선생"));
		_friends.push_back(IMAGEMANAGER->findImage("레스토랑친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("레스토랑친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("레스토랑친구3"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 1;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 2, _endF = 3;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 4, _endF = 5;

		}
		break;
	case WORK_WOOD:
		_friends.push_back(IMAGEMANAGER->findImage("나무꾼선생"));
		_friends.push_back(IMAGEMANAGER->findImage("나무꾼친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("나무꾼친구2"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 4;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 0, _endF = 9;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 11, _endF = 12;

		}
		break;
	case WORK_HAIR:
		_friends.push_back(IMAGEMANAGER->findImage("미용실선생"));
		_friends.push_back(IMAGEMANAGER->findImage("미용실친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("미용실친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("미용실친구3"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;
			_friends[1]->setFrameY(0);

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 4, _endF = 7;
			_friends[1]->setFrameY(1);

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 8, _endF = 9;
			_friends[1]->setFrameY(1);

		}
		break;
	case WORK_PLASTERER:
		_friends.push_back(IMAGEMANAGER->findImage("미장이선생"));
		_friends.push_back(IMAGEMANAGER->findImage("미장이친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("미장이강아지"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 0, _endF = 6;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 7, _endF = 8;

		}
		break;
	case WORK_HUNTER:
		_friends.push_back(IMAGEMANAGER->findImage("사냥꾼선생"));
		_friends.push_back(IMAGEMANAGER->findImage("사냥꾼토끼"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 4;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 2, _endF = 5;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 6, _endF = 7;

		}
		break;
	case WORK_GRAVE:
		_friends.push_back(IMAGEMANAGER->findImage("묘지기선생"));
		_friends.push_back(IMAGEMANAGER->findImage("묘지기불"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 4, _endF = 5;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 6, _endF = 7;

		}
		break;
	case WORK_COACH:
		_friends.push_back(IMAGEMANAGER->findImage("가정교사선생"));
		_friends.push_back(IMAGEMANAGER->findImage("가정교사친구"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_SLEEP;
			_startF = 5, _endF = 7;
		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 4;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 8, _endF = 9;

		}
		break;
	case WORK_DRINK:
		_friends.push_back(IMAGEMANAGER->findImage("주점선생"));
		_friends.push_back(IMAGEMANAGER->findImage("주점친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("주점친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("주점친구3"));

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 7;

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 7, _endF = 17;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 18, _endF = 19;

		}
		break;
	case WORK_NIGHT_DRINK:
		_back = IMAGEMANAGER->findImage("밤의주점배경");
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점선생"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점친구3"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점친구4"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점친구5"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점친구6"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의주점촛불"));
		_princessImg = IMAGEMANAGER->findImage("밤의주점공주");

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;
		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 4, _endF = 7;
		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 4, _endF = 7;
		}
		break;
	case WORK_NIGHT_CLUB:
		_back = IMAGEMANAGER->findImage("밤의전당배경");
		_friends.push_back(IMAGEMANAGER->findImage("밤의전당선생"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의전당친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의전당친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의전당친구3"));
		_friends.push_back(IMAGEMANAGER->findImage("밤의전당친구4"));
		_princessImg = IMAGEMANAGER->findImage("밤의전당공주");

		if (selectStatus() == WORK_HARD)
		{
			_status = WORK_HARD;
			_startF = 0, _endF = 3;
			_friends[1]->setFrameX(0), _friends[2]->setFrameX(0);

		}
		else if (selectStatus() == WORK_SLEEP)
		{
			_status = WORK_SLEEP;
			_startF = 3, _endF = 7;

		}
		else
		{
			_status = WORK_NOHARD;
			_startF = 8, _endF = 9;

		}
		break;
	}
}

void partTimeScene::setTeachDialog()
{
	//다이얼로그 만들기, 다시합시당
	vector<string> vStr = TXTDATA->txtLoad("dialog/workStart.txt");
	vStr[(int)_type] == "T" ? _workStart = false : _workStart = true;
	if (_workStart)
	{
		vStr[(int)_type] = "T";
		TXTDATA->txtSave("dialog/workStart.txt", vStr);
	}
	_teacherFrameX = (int)_type;
	vStr = TXTDATA->txtLoadCsv("dialog/workTeach.csv");
	char cStr[100000];
	strcpy(cStr, vStr[(int)_type].c_str());
	_teachDialog = TXTDATA->charArraySeparation(cStr);
}

void partTimeScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if (_vDialog.size() > 0)
		_vDialog.clear();
	if (_progress == STATUS_TEACH)
		_vDialog.push_back(_teachDialog[0]);
	int strLength = 50;
	if (_progress == STATUS_FIN || _progress == STATUS_TEACH) strLength = 28;
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

void partTimeScene::setResultDialog()
{
	_progress = STATUS_FIN;
	_vDialog.clear();
	//게임보고 마무리 어떻게 지어지나 봐야해
	/*string str = to_string(_printDay) + "일간의 급여는" + to_string(_pGold.data) + "이다.";
	_vDialog.push_back(str);*/
	if (_workName == "집안일")
		_vDialog.push_back(_teachDialog[3]);
	else
	{
		if (_success == 0)
			_vDialog.push_back(_teachDialog[3]);
		else
		{
			if (_success < _printDay)
				_vDialog.push_back(_teachDialog[4]);
			else
			{
				_vDialog.push_back(_teachDialog[5]);
				_pGold.data *= 1.5;
			}
		}
	}
	_princess->setGold(_pGold.data);
	//DIALOG->setDialog(_vDialog[0], 5);
	setDialog(_vDialog[0]);
	_dialogX = 190, _dialogY = 235;
	_dialogType = DIALOG_FIN;
}

void partTimeScene::changeFrame()
{
	if (_workFin) return;

	if (_dayIdx >= _dayCount)
	{
		setResultDialog();
		_workFin = true;
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
			if (_frameX < _endF)
				_frameX++;
			else
			{
				_frameX = _startF;
				_frameCount++;
			}
		}
		else
			_frameCount++;
		if (_frameCount == 3)
		{
			_frameCount = 0;
			_day++;
			_dayIdx++;
			if (_dayOfWeek != SUN)
			{
				_printDay++;
				if (_status == WORK_HARD)
				{
					_success++;
					//_princess->setGold(_gold);
					_pGold.data += _gold;
				}
			}
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
			if (_dayOfWeek != MON)
			{
				//workStatus올려주기
				for (int i = 0; i < _work->getProperty().size(); i++)
				{
					int randNum;
					if (_work->getProperty()[i].second.first == _work->getProperty()[i].second.second)
						randNum = _work->getProperty()[i].second.first;
					else
					{
						if (_work->getProperty()[i].second.second < 0)
						{
							randNum = RND->getFromIntTo(_work->getProperty()[i].second.first, -_work->getProperty()[i].second.second);
							randNum = -randNum;
						}
						else
						{
							randNum = RND->getFromIntTo(_work->getProperty()[i].second.first, _work->getProperty()[i].second.second);
						}
					}
					int temp = changeStatus(_work->getProperty()[i].first, randNum);
					int result = 0;
					if (temp + randNum > 0)
						result = temp + randNum;
					_workStatus[i].second = result;
					_vPStatus[i].second.data = result;
				}
				/*}
				if(_dayOfWeek != SUN)
				{*/
				switch (_type)
				{
				case WORK_HOUSE:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 2;
						_friends[0]->setFrameX(0);

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 2, _endF = 7;
						_friends[0]->setFrameX(1);

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 8, _endF = 9;
						_friends[0]->setFrameX(1);

					}
					break;
				case WORK_NURSERY:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 4, _endF = 7;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 8, _endF = 9;

					}
					break;
				case WORK_INN:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 4, _endF = 8;
						_friends[2]->setFrameX(0);

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 9, _endF = 10;

					}
					break;
				case WORK_FARM:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 4;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 5, _endF = 9;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 10, _endF = 11;

					}
					break;
				case WORK_CHURCH:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 4, _endF = 5;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 6, _endF = 7;

					}
					break;
				case WORK_RESTAURANT:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 1;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 2, _endF = 3;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 4, _endF = 5;

					}
					break;
				case WORK_WOOD:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 4;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 0, _endF = 9;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 11, _endF = 12;

					}
					break;
				case WORK_HAIR:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;
						_friends[1]->setFrameY(0);

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 4, _endF = 7;
						_friends[1]->setFrameY(1);

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 8, _endF = 9;
						_friends[1]->setFrameY(1);

					}
					break;
				case WORK_PLASTERER:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 0, _endF = 6;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 7, _endF = 8;

					}
					break;
				case WORK_HUNTER:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 4;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 2, _endF = 5;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 6, _endF = 7;

					}
					break;
				case WORK_GRAVE:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 4, _endF = 5;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 6, _endF = 7;

					}
					break;
				case WORK_COACH:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_SLEEP;
						_startF = 5, _endF = 7;
					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 4;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 8, _endF = 9;

					}
					break;
				case WORK_DRINK:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 7;

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 7, _endF = 17;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 18, _endF = 19;

					}
					break;
				case WORK_NIGHT_DRINK:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;
					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 4, _endF = 7;
					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 4, _endF = 7;
					}
					break;
				case WORK_NIGHT_CLUB:
					if (selectStatus() == WORK_HARD)
					{
						_status = WORK_HARD;
						_startF = 0, _endF = 3;
						_friends[1]->setFrameX(0), _friends[2]->setFrameX(0);

					}
					else if (selectStatus() == WORK_SLEEP)
					{
						_status = WORK_SLEEP;
						_startF = 3, _endF = 7;

					}
					else
					{
						_status = WORK_NOHARD;
						_startF = 8, _endF = 9;

					}
					break;
				}
			}
			if (_dayIdx < _dayCount)
			{
				_princess->getStatusP()->stress += _work->getStress();
				_vPStatus[_vPStatus.size() - 1].second.data += _work->getStress();
				_princess->setDay(_day);
				_princess->setDayOfWeek(_dayOfWeek);
			}
		}
	}
}

WORK_STATUS partTimeScene::selectStatus()
{
	bool conditionOk = true;
	for (int i = 0; i < _work->getSuccess().size(); i++)
	{
		string name = _work->getSuccess()[i].first;
		int value = _work->getSuccess()[i].second;
		if (changeStatus(name, 0) < (value*1.5))
		{
			conditionOk = false;
			break;
		}
	}
	if (!conditionOk)
	{
		if (_princess->getStatus().stress > _princess->getStatus().faith)
			return WORK_SLEEP;
		if (_princess->getStatus().stress > _princess->getStatus().morality)
			return WORK_NOHARD;
	//	if (!RND->getInt(2))
			return WORK_SLEEP;
	//	else
	//		return WORK_NOHARD;
	}
	//_success++;
	//_princess->setGold(_gold);
	//_pGold.data += _gold;
	return WORK_HARD;
}

int partTimeScene::changeStatus(string name, int value)
{
	int temp = -999;

	if (name == "요리")
	{
		temp = _princess->getStatus().cooking;
		_princess->getStatusP()->cooking += value;
		if (_princess->getStatus().cooking < 0)
			_princess->getStatusP()->cooking = 0;
	}
	else if (name == "감수성")
	{
		temp = _princess->getStatus().sensitivity;
		_princess->getStatusP()->sensitivity += value;
		if (_princess->getStatus().sensitivity < 0)
			_princess->getStatusP()->sensitivity = 0;
	}
	else if (name == "청소세탁")
	{
		temp = _princess->getStatus().cleaning;
		_princess->getStatusP()->cleaning += value;
		if (_princess->getStatus().cleaning < 0)
			_princess->getStatusP()->cleaning = 0;
	}
	else if (name == "체력")
	{
		temp = _princess->getStatus().hp;
		_princess->getStatusP()->hp += value;
		if (_princess->getStatus().hp < 0)
			_princess->getStatusP()->hp = 0;
	}
	else if (name == "도덕성")
	{
		temp = _princess->getStatus().morality;
		_princess->getStatusP()->morality += value;
		if (_princess->getStatus().morality < 0)
			_princess->getStatusP()->morality = 0;
	}
	else if (name == "근력")
	{
		temp = _princess->getStatus().physical;
		_princess->getStatusP()->physical += value;
		if (_princess->getStatus().physical < 0)
			_princess->getStatusP()->physical = 0;
	}
	else if (name == "매력")
	{
		temp = _princess->getStatus().sexual;
		_princess->getStatusP()->sexual += value;
		if (_princess->getStatus().sexual < 0)
			_princess->getStatusP()->sexual = 0;
	}
	else if (name == "전투기술")
	{
		temp = _princess->getStatus().warriorSkill;
		_princess->getStatusP()->warriorSkill += value;
		if (_princess->getStatus().warriorSkill < 0)
			_princess->getStatusP()->warriorSkill = 0;
	}
	else if (name == "신앙심")
	{
		temp = _princess->getStatus().faith;
		_princess->getStatusP()->faith += value;
		if (_princess->getStatus().faith < 0)
			_princess->getStatusP()->faith = 0;
	}
	else if (name == "기품")
	{
		temp = _princess->getStatus().elegance;
		_princess->getStatusP()->elegance += value;
		if (_princess->getStatus().elegance < 0)
			_princess->getStatusP()->elegance = 0;
	}
	else if (name == "항마력")
	{
		temp = _princess->getStatus().spellDefence;
		_princess->getStatusP()->spellDefence += value;
		if (_princess->getStatus().spellDefence < 0)
			_princess->getStatusP()->spellDefence = 0;
	}
	else if (name == "화술")
	{
		temp = _princess->getStatus().conversation;
		_princess->getStatusP()->conversation += value;
		if (_princess->getStatus().conversation < 0)
			_princess->getStatusP()->conversation = 0;
	}
	else if (name == "인과")
	{
		temp = _princess->getStatus().karma;
		_princess->getStatusP()->karma += value;
		if (_princess->getStatus().karma < 0)
			_princess->getStatusP()->karma = 0;
	}
	else if (name == "성품")
	{
		temp = _princess->getStatus().personality;
		_princess->getStatusP()->personality += value;
		if (_princess->getStatus().personality < 0)
			_princess->getStatusP()->personality = 0;
	}
	else if (name == "지능")
	{
		temp = _princess->getStatus().intelligence;
		_princess->getStatusP()->intelligence += value;
		if (_princess->getStatus().intelligence < 0)
			_princess->getStatusP()->intelligence = 0;
	}
	else if (name == "관계")
	{
		temp = _princess->getStatus().withFather;
		_princess->getStatusP()->withFather += value;
		if (_princess->getStatus().withFather < 0)
			_princess->getStatusP()->withFather = 0;
	}
	else if (name == "예술")
	{
		temp = _princess->getStatus().art;
		_princess->getStatusP()->art += value;
		if (_princess->getStatus().art < 0)
			_princess->getStatusP()->art = 0;
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

bool partTimeScene::dialogRender()
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

void partTimeScene::workRender()
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

	if (_progress == STATUS_FIN) return;

	if (_dayOfWeek == SUN && (_dayIdx < _dayCount))
	{
		TextOut(DC, 450, 250, "오늘은 일요일입니다.", strlen("오늘은 일요일입니다."));
		return;
	}

	switch (_type)
	{
	case WORK_HOUSE:
		_friends[0]->frameRender(DC, 89 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case WORK_NURSERY:
		_friends[0]->frameRender(DC, 320 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 250 + backX, 44 + backY, _friends[1]->getFrameX(), 0);
		_princessImg->frameRender(DC, 50 + backX, 43 + backY, _frameX, 0);
		break;
	case WORK_INN:
		_friends[0]->frameRender(DC, backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 250 + backX, 44 + backY, _friends[1]->getFrameX(), 0);
		if (_status == WORK_NOHARD)
			_princessImg->frameRender(DC, 170 + backX, 42 + backY, _frameX, 0);
		else
		{
			_princessImg->frameRender(DC, 170 + backX, backY, _frameX, 0);
			if (_status == WORK_SLEEP)
			{
				_friends[2]->frameRender(DC, 200 + backX, 50 + backY, _friends[2]->getFrameX(), 0);
			}
		}
		break;
	case WORK_FARM:
		_friends[0]->frameRender(DC, 10 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 250 + backX, 44 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, 80 + backX, 40 + backY, _friends[2]->getFrameX(), 0);
		_friends[3]->frameRender(DC, 130 + backX, 40 + backY, _friends[3]->getFrameX(), 0);
		_friends[4]->frameRender(DC, 300 + backX, 44 + backY, _friends[4]->getFrameX(), 0);
		_friends[5]->frameRender(DC, 350 + backX, 44 + backY, _friends[5]->getFrameX(), 0);
		_princessImg->frameRender(DC, 100 + backX, 42 + backY, _frameX, 0);

		break;
	case WORK_CHURCH:
		_friends[0]->frameRender(DC, 300 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->render(DC, 250 + backX, 43 + backY);
		_princessImg->frameRender(DC, 100 + backX, 42 + backY, _frameX, 0);

		break;
	case WORK_RESTAURANT:
		_friends[0]->frameRender(DC, 100 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 100 + backX, 43 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, 200 + backX, 43 + backY, _friends[2]->getFrameX(), 0);
		_friends[3]->frameRender(DC, 280 + backX, 43 + backY, _friends[3]->getFrameX(), 0);
		_friends[4]->frameRender(DC, 330 + backX, 43 + backY, _friends[4]->getFrameX(), 0);
		_princessImg->frameRender(DC, 50 + backX, 42 + backY, _frameX, 0);

		break;
	case WORK_WOOD:
		_friends[0]->frameRender(DC, 330 + backX, 20 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 200 + backX, 43 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, backX, 43 + backY, _friends[2]->getFrameX(), 0);
		_princessImg->frameRender(DC, 80 + backX, 42 + backY, _frameX, 0);
		IMAGEMANAGER->findImage("나무꾼풀")->render(DC, backX, 108 + backY);

		break;
	case WORK_HAIR:
		_friends[0]->frameRender(DC, 270 + backX, 40 + backY, _friends[0]->getFrameX(), 0);

		_friends[2]->frameRender(DC, 250 + backX, 40 + backY, _friends[2]->getFrameX(), 0);
		IMAGEMANAGER->findImage("미용실친구3팔")->render(DC, 160 + backX, 40 + backY);
		_friends[3]->frameRender(DC, 180 + backX, 40 + backY, _friends[2]->getFrameX(), 0);

		if (_frameX >= 6)
			_princessImg->frameRender(DC, 100 + backX, 42 + backY, _frameX, 0);
		else
			_princessImg->frameRender(DC, 78 + backX, 43 + backY, _frameX, 0);

		_friends[1]->frameRender(DC, 60 + backX, 40 + backY, _friends[1]->getFrameX(), _friends[1]->getFrameY());

		break;
	case WORK_PLASTERER:
		_friends[0]->frameRender(DC, 5 + backX, backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 280 + backX, 45 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, 200 + backX, 40 + backY, _friends[2]->getFrameX(), 0);

		_princessImg->frameRender(DC, 20 + backX, 40 + backY, _frameX, 0);

		break;
	case WORK_HUNTER:
		_friends[0]->frameRender(DC, 340 + backX, 40 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 20 + backX, 40 + backY, _friends[1]->getFrameX(), 0);

		_princessImg->frameRender(DC, 260 + backX, 40 + backY, _frameX, 0);

		break;
	case WORK_GRAVE:
		_friends[1]->frameRender(DC, 95 + backX, 70 + backY, _friends[1]->getFrameX(), 0);
		_friends[0]->frameRender(DC, 130 + backX, 42 + backY, _friends[0]->getFrameX(), 0);
		_princessImg->frameRender(DC, 300 + backX, 40 + backY, _frameX, 0);

		break;
	case WORK_COACH:
		_friends[0]->frameRender(DC, 20 + backX, 42 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 200 + backX, 42 + backY, _friends[1]->getFrameX(), 0);
		_princessImg->frameRender(DC, 150 + backX, 42 + backY, _frameX, 0);

		break;
	case WORK_DRINK:
		_friends[0]->frameRender(DC, 200 + backX, backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 60 + backX, 17 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, 210 + backX, 42 + backY, _friends[2]->getFrameX(), 0);
		_friends[3]->frameRender(DC, 270 + backX, 43 + backY, _friends[3]->getFrameX(), 0);
		_princessImg->frameRender(DC, 300 + backX, 17 + backY, _frameX, 0);

		break;
	case WORK_NIGHT_DRINK:
		_friends[0]->frameRender(DC, backX, 42 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 70 + backX, 42 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, 115 + backX, 42 + backY, _friends[2]->getFrameX(), 0);
		_friends[3]->frameRender(DC, 145 + backX, 43 + backY, _friends[3]->getFrameX(), 0);
		_friends[4]->frameRender(DC, 270 + backX, 42 + backY, _friends[4]->getFrameX(), 0);
		_friends[5]->frameRender(DC, 300 + backX, 42 + backY, _friends[5]->getFrameX(), 0);
		_friends[6]->frameRender(DC, 200 + backX, backY, _friends[6]->getFrameX(), 0);
		_friends[7]->frameRender(DC, 70 + backX, backY, _friends[7]->getFrameX(), 0);
		if(_status == WORK_HARD)
			_princessImg->frameRender(DC, 330 + backX, 42 + backY, _frameX, 0);
		else
			_princessImg->frameRender(DC, 340 + backX, 42 + backY, _frameX, 0);
		break;
	case WORK_NIGHT_CLUB:
		_friends[0]->frameRender(DC, backX, 42 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 130 + backX, 42 + backY, _friends[1]->getFrameX(), 0);
		_friends[2]->frameRender(DC, 230 + backX, 42 + backY, _friends[2]->getFrameX(), 0);
		_friends[3]->frameRender(DC, 50 + backX, 43 + backY, _friends[3]->getFrameX(), 0);
		_friends[4]->frameRender(DC, 350 + backX, 42 + backY, _friends[4]->getFrameX(), 0);
		_princessImg->frameRender(DC, 180 + backX, 42 + backY, _frameX, 0);
		break;
	}

	string temp = _workName + " " + to_string(_printDay + 1) + "일차";
	TextOut(DC, 450, 250, temp.c_str(), strlen(temp.c_str()));
	char str2[128];
	switch (_status)
	{
	case WORK_HARD:
		TextOut(DC, 445, 280, "오늘은 착실하게 일을 했다.", strlen("오늘은 착실하게 일을 했다."));
		break;
	case WORK_SLEEP:
		TextOut(DC, 445, 280, "오늘은 실수를 한 것 같다.", strlen("오늘은 실수를 한 것 같다."));
		break;
	case WORK_NOHARD:
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
