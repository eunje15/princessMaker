#include "stdafx.h"
#include "scheduleScene.h"
#include "princess.h"

scheduleScene::scheduleScene()
{
}


scheduleScene::~scheduleScene()
{
}

HRESULT scheduleScene::init(int year, int mon)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	//�� ������ �Ͽ��Ϻ��� ������ ����
	_year = year, _mon = mon;

	int finday = 30;
	if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
		finday = 31;
	else if (mon == 2)
		finday = 28;

	for (int i = 0; i < 42; i++)
	{
		_calImg[i].data.rc = RectMake(20 + (i % 7) * 40, 160 + 40 * (i / 7), 40, 40);
		_calImg[i].x = (_calImg[i].data.rc.right + _calImg[i].data.rc.left) / 2 - 3;
		_calImg[i].y = (_calImg[i].data.rc.bottom + _calImg[i].data.rc.top) / 2 - 3;
		_calImg[i].data.isSelected = _calImg[i].data.isChoose = false;
		if (i < finday)
		{
			_calImg[i].data.str = to_string(i + 1);
			_calImg[i].data.isChoose = true;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		_chooseBox[i].rc = RectMake(610, 290 + i * 28, 150, 28);
		_chooseBox[i].isChoose = _chooseBox[i].isSelected = false;
		if (i > 1) continue;
		_selectBox[i].rc = RectMake(600, 330 + i * 28, 150, 28);
		_selectBox[i].isChoose = _selectBox[i].isSelected = false;
	}

	_chooseBox[0].str = "���� �ܷý�Ų��";
	_chooseBox[1].str = "������ ���� ��Ų��";
	_chooseBox[2].str = "��������� ������";
	_chooseBox[3].str = "�޽��� �ش�";

	_selectBox[0].str = "�����ٿ� ���Ѵ�";
	_selectBox[1].str = "���";

	_type = SCHEDULE_NONE;

	setDialog("�̹��� ���� ������?(ù��°)");
	_dialogType = DIALOG_ING;
	_dialogIdx = _scheduleIdx = 0;
	_selectNum = -1;
	setScheduleImage();

	_fin = _select = _scheduleStart = false;
	_progress = SCHEDULE_START;

	_education = new educationScene;
	_work = new partTimeScene;
	_relax = new relaxScene;

	return S_OK;
}

void scheduleScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_type)
	{
	case SCHEDULE_NONE:
		for (int i = 0; i < 4; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						_type = SCHEDULE_TEACH;
						setDialog("������ ������ ����ġ�ðڽ��ϱ�?");
					}
					else if (i == 1)
					{
						_type = SCHEDULE_WORK;
						setDialog("��� ���� ��Ű�ðڽ��ϱ�?");
					}
					else if (i == 2)
					{
						_type = SCHEDULE_FIGHT;
						setDialog("��������� ���� �����ðڽ��ϱ�?");
					}
					else if (i == 3)
					{
						_type = SCHEDULE_RELAX;
						setDialog("� �޽��� �ֽðڽ��ϱ�?");

					}
				}
			}
		}
		break;
	case SCHEDULE_TEACH:
	{
		if (!_select)
		{
			for (int i = 0; i < 10; i++)
			{
				_teachImg[i].frameX = 0;
				if (PtInRect(&_teachImg[i].data.rc, _ptMouse))
				{
					_teachImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _sm->getVTeach()[_selectNum]->getFrameIndex();
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "teach";
										_itemIdx[_scheduleIdx] = _calImg[i].frameX;
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "teach";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else if (_mon == 2)
									{
										if (count == 8)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "teach";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "teach";
											_itemIdx[_scheduleIdx] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "��, �����ٿ� ���ϰڽ��ϴ�. �̹��� ���� ������?";
							if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "�̹��� ���� ������?";
							if (_scheduleIdx == 0)
								str += "(ù��°)";
							else if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}

		}
	}
	break;
	case SCHEDULE_WORK:
		if (!_select)
		{
			for (int i = 0; i < 15; i++)
			{
				_workImg[i].frameX = 0;
				if (PtInRect(&_workImg[i].data.rc, _ptMouse) && _workImg[i].data.isSelected)
				{
					_workImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _sm->getVWork()[_selectNum]->getFrameIndex();
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "work";
										_itemIdx[_scheduleIdx] = _calImg[i].frameX;
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "work";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else if (_mon == 2)
									{
										if (count == 8)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "teach";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "work";
											_itemIdx[_scheduleIdx] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "��, �����ٿ� ���ϰڽ��ϴ�. �̹��� ���� ������?";
							if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "�̹��� ���� ������?";
							if (_scheduleIdx == 0)
								str += "(ù��°)";
							else if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}
		}
		break;
	case SCHEDULE_FIGHT:
		if (!_select)
		{
			for (int i = 0; i < 4; i++)
			{
				_fightImg[i].frameX = 0;
				if (PtInRect(&_fightImg[i].data.rc, _ptMouse))
				{
					_fightImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _fightImg[_selectNum].frameY;
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "fight";
										_itemIdx[_scheduleIdx] = _calImg[i].frameX;
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "fight";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else if (_mon == 2)
									{
										if (count == 8)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "teach";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "fight";
											_itemIdx[_scheduleIdx] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "��, �����ٿ� ���ϰڽ��ϴ�. �̹��� ���� ������?";
							if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "�̹��� ���� ������?";
							if (_scheduleIdx == 0)
								str += "(ù��°)";
							else if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}

		}
		break;
	case SCHEDULE_RELAX:
		if (!_select)
		{
			for (int i = 0; i < 2; i++)
			{
				_relaxImg[i].frameX = 0;
				if (PtInRect(&_relaxImg[i].data.rc, _ptMouse))
				{
					_relaxImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _relaxImg[_selectNum].frameY;
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "relax";
										_itemIdx[_scheduleIdx] = _calImg[i].frameX;
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "relax";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else if (_mon == 2)
									{
										if (count == 8)
										{
											_scheduleWeek[_scheduleIdx] = _scheduleWeek[_scheduleIdx + 1] = "teach";
											_itemIdx[_scheduleIdx] = _itemIdx[_scheduleIdx + 1] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "relax";
											_itemIdx[_scheduleIdx] = _calImg[i].frameX;
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "��, �����ٿ� ���ϰڽ��ϴ�. �̹��� ���� ������?";
							if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "�̹��� ���� ������?";
							if (_scheduleIdx == 0)
								str += "(ù��°)";
							else if (_scheduleIdx == 1)
								str += "(�ι�°)";
							else if (_scheduleIdx == 2)
								str += "(����°)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}

		}
		break;
	case SCHEDULE_OK:
		for (int i = 0; i < 2; i++)
		{
			_selectBox[i].isSelected = false;
			if (PtInRect(&_selectBox[i].rc, _ptMouse))
			{
				_selectBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						//_fin = true;
						_type = SCHEDULE_GO;
						_scheduleIdx = 0;
						_select = false;

						string str;
						if (_princess->getInfo().dietType == "��·�� ưư�ϰ�")
							str = "�ĺ� 80G �ʿ��մϴ�.", _gold = -80;
						else if (_princess->getInfo().dietType == "�������� �ʴ´�")
							str = "�ĺ� 30G �ʿ��մϴ�.", _gold = -30;
						else if (_princess->getInfo().dietType == "������ ���̷�")
							str = "�ĺ� 10G �ʿ��մϴ�.", _gold = -10;
						else if (_princess->getInfo().dietType == "���̾�Ʈ�� ��Ų��")
							str = "�ĺ� 5G �ʿ��մϴ�.", _gold = -5;

						setDialog(str);
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
					else
					{
						_type = SCHEDULE_NONE;
						_scheduleIdx = 0;
						_select = false;
						for (int i = 0; i < 3; i++)
						{
							_scheduleWeek[i] = "";
						}
						for (int i = 0; i < 42; i++)
						{
							_calImg[i].data.isSelected = false;
						}
					}
				}
			}
		}
		break;
	case SCHEDULE_GO:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_scheduleStart)
			{
				_princess->setGold(_gold);
				_scheduleStart = true;
				setSchedule();
				//if (_scheduleWeek[0] == "teach")
				//_education->init(_sm->getVTeach()[_itemIdx[0]], 10);
			}
		}

		if (_scheduleStart)
		{
			if (_scheduleIdx > 2) break;
			if (_scheduleWeek[_scheduleIdx] == "teach")
			{
				_education->update();
				if (_education->getFin())
				{
					if (_progress == SCHEDULE_ING)
					{
						_scheduleIdx++;
						_progress = SCHEDULE_FIN;
						if (_scheduleIdx > 2)
						{
							_fin = true;
						}
					}
				}
			}
			else if (_scheduleWeek[_scheduleIdx] == "work")
			{
				_work->update();
				if (_work->getFin())
				{
					if (_progress == SCHEDULE_ING)
					{
						_scheduleIdx++;
						_progress = SCHEDULE_FIN;
						if (_scheduleIdx > 2)
						{
							_fin = true;
						}
					}
				}
			}
			else if (_scheduleWeek[_scheduleIdx] == "relax")
			{
				_relax->update();
				if (_relax->getFin())
				{
					if (_progress == SCHEDULE_ING)
					{
						_scheduleIdx++;
						_progress = SCHEDULE_FIN;
						if (_scheduleIdx > 2)
						{
							_fin = true;
						}
					}
				}
			}
			if (_progress == SCHEDULE_START)
				setSchedule();
		}
		break;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_type == SCHEDULE_NONE) _fin = true;
		_type = SCHEDULE_NONE;
		string str = "�̹��� ���� ������?";
		if (_scheduleIdx == 0)
			str += "(ù��°)";
		else if (_scheduleIdx == 1)
			str += "(�ι�°)";
		else if (_scheduleIdx == 2)
			str += "(����°)";
		setDialog(str);
		_select = false;
		_dialogType = DIALOG_FIN;
		for (int i = 0; i < 3; i++)
		{
			_scheduleWeek[i] = "";
		}
		for (int i = 0; i < 42; i++)
		{
			_calImg[i].data.isSelected = false;
		}
	}
}


void scheduleScene::render()
{
	if (!_scheduleStart)
	{
		IMAGEMANAGER->findImage("schedule")->render(DC, 10, 110);
		IMAGEMANAGER->findImage("year")->frameRender(DC, 100, 119, 0, _year - 1200);
		IMAGEMANAGER->findImage("month")->frameRender(DC, 160, 119, 0, _mon - 1);

		IMAGEMANAGER->findImage("dialogFrame")->render(DC, 10, 426);
		IMAGEMANAGER->findImage("frame")->render(DC, 20 + IMAGEMANAGER->findImage("dialogFrame")->getWidth(), 426);
		IMAGEMANAGER->findImage("cube")->frameRender(DC, 30 + IMAGEMANAGER->findImage("dialogFrame")->getWidth(), 436, 0, 0);
	}
	if (dialogRender())
	{
		if (!_scheduleStart)
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		switch (_type)
		{
		case SCHEDULE_NONE:
			IMAGEMANAGER->findImage("4Back")->render(DC, 600, 280);

			for (int i = 0; i < 4; i++)
			{
				//IMAGEMANAGER->findImage("�˹پ���")->render(DC, 10, 430);
				if (dialogRender())
				{
					for (int i = 0; i < _vDialog.size(); i++)
					{
						TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
					}
				}
				if (_chooseBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_chooseBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _chooseBox[i].rc.left + 2, _chooseBox[i].rc.top + 5, _chooseBox[i].str.c_str(), strlen(_chooseBox[i].str.c_str()));
			}

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				/*for (int i = 0; i < 42; i++)
				{
				Rectangle(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].data.rc.right, _calImg[i].data.rc.bottom);
				}
				*/
				for (int i = 0; i < 10; i++)
				{
					Rectangle(DC, _teachImg[i].data.rc.left, _teachImg[i].data.rc.top, _teachImg[i].data.rc.right, _teachImg[i].data.rc.bottom);
				}
			}
			break;
		case SCHEDULE_TEACH:
			if (!_select)
			{
				for (int i = 0; i < 10; i++)
				{
					_teachImg[i].img->frameRender(DC, _teachImg[i].data.rc.left, _teachImg[i].data.rc.top, _teachImg[i].frameX, 0);
					IMAGEMANAGER->findImage("teachImg")->frameRender(DC, _teachImg[i].data.rc.left + 5, _teachImg[i].data.rc.top + 7, _teachImg[i].frameY, 0);
					TextOut(DC, _teachImg[i].data.rc.left + 50, _teachImg[i].data.rc.top + 7, _sm->getVTeach()[i]->getName().c_str(), strlen(_sm->getVTeach()[i]->getName().c_str()));
					string str = _sm->getVTeach()[i]->getStringStep() + " " + to_string(_sm->getVTeach()[i]->getTuition()) + "G";
					TextOut(DC, _teachImg[i].data.rc.left + 50, _teachImg[i].data.rc.top + 30, str.c_str(), strlen(str.c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		case SCHEDULE_WORK:
			if (!_select)
			{
				for (int i = 0; i < 15; i++)
				{
					if (!_workImg[i].data.isSelected) continue;
					_workImg[i].img->frameRender(DC, _workImg[i].data.rc.left, _workImg[i].data.rc.top, _workImg[i].frameX, 0);
					IMAGEMANAGER->findImage("workImg")->frameRender(DC, _workImg[i].data.rc.left + 5, _workImg[i].data.rc.top + 7, _workImg[i].frameY, 0);
					TextOut(DC, _workImg[i].data.rc.left + 50, _workImg[i].data.rc.top + 7, _sm->getVWork()[i]->getName().c_str(), strlen(_sm->getVWork()[i]->getName().c_str()));
					string str = to_string(_sm->getVWork()[i]->getSalary()) + "G";
					TextOut(DC, _workImg[i].data.rc.left + 50, _workImg[i].data.rc.top + 30, str.c_str(), strlen(str.c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		case SCHEDULE_FIGHT:
			if (!_select)
			{
				for (int i = 0; i < 4; i++)
				{
					_fightImg[i].img->frameRender(DC, _fightImg[i].data.rc.left, _fightImg[i].data.rc.top, _fightImg[i].frameX, 0);
					IMAGEMANAGER->findImage("fightImg")->frameRender(DC, _fightImg[i].data.rc.left + 5, _fightImg[i].data.rc.top + 7, _fightImg[i].frameY, 0);
					TextOut(DC, _fightImg[i].data.rc.left + 50, _fightImg[i].data.rc.top + 7, _sm->getVFight()[i]->getDirection().c_str(), strlen(_sm->getVFight()[i]->getDirection().c_str()));
					TextOut(DC, _fightImg[i].data.rc.left + 50, _fightImg[i].data.rc.top + 30, _sm->getVFight()[i]->getWhere().c_str(), strlen(_sm->getVFight()[i]->getWhere().c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		case SCHEDULE_RELAX:
			if (!_select)
			{
				for (int i = 0; i < 2; i++)
				{
					_relaxImg[i].img->frameRender(DC, _relaxImg[i].data.rc.left, _relaxImg[i].data.rc.top, _relaxImg[i].frameX, 0);
					IMAGEMANAGER->findImage("relaxImg")->frameRender(DC, _relaxImg[i].data.rc.left + 5, _relaxImg[i].data.rc.top + 7, _relaxImg[i].frameY, 0);
					TextOut(DC, _relaxImg[i].data.rc.left + 50, _relaxImg[i].data.rc.top + 7, _sm->getVRelax()[i]->getName().c_str(), strlen(_sm->getVRelax()[i]->getName().c_str()));
					string str = "";
					if (i == 1)
						str = to_string(_sm->getVRelax()[i]->getGold()*_princess->getInfo().age) + "G";
					else
						str = "0G";
					TextOut(DC, _relaxImg[i].data.rc.left + 50, _relaxImg[i].data.rc.top + 30, str.c_str(), strlen(str.c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		case SCHEDULE_OK:
			IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
			break;
		case SCHEDULE_GO:
			if (_scheduleStart)
			{
				if (_scheduleIdx > 2) break;
				if (_scheduleWeek[_scheduleIdx] == "teach")
				{
					_education->render();
				}
				else if (_scheduleWeek[_scheduleIdx] == "work")
				{
					_work->render();
				}
				else if (_scheduleWeek[_scheduleIdx] == "relax")
				{
					_relax->render();
				}
			}
			break;
		}
	}

	if (!_scheduleStart)
	{
		int count = 0;
		for (int i = 0; i < 42; i++)
		{
			if (!_calImg[i].data.isChoose) break;
			if (_calImg[i].data.isSelected)
			{
				if (i == 30)
					int a = 0;
				/*if (count / 10 < 0)
				{
				IMAGEMANAGER->findImage("teachImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
				}*/
				if (_scheduleWeek[count / 10] == "teach")
					IMAGEMANAGER->findImage("teachImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
				else if (_scheduleWeek[count / 10] == "work")
					IMAGEMANAGER->findImage("workImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
				else if (_scheduleWeek[count / 10] == "fight")
					IMAGEMANAGER->findImage("fightImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
				else if (_scheduleWeek[count / 10] == "relax")
					IMAGEMANAGER->findImage("relaxImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
				count++;
			}
			IMAGEMANAGER->findImage("smallDay")->frameRender(DC, _calImg[i].x, _calImg[i].y, 0, atoi(_calImg[i].data.str.c_str()) - 1);
		}
		if (_scheduleIdx == 3)
		{
			_type = SCHEDULE_OK;
			_selectBox[0].str = "�������� �����Ѵ�";
			setDialog("�̴�� �������� �����Ͻðڽ��ϱ�?");
			_dialogType = DIALOG_FIN;
		}
	}
}

void scheduleScene::release()
{
}

void scheduleScene::setSchedule()
{
	if (_progress != SCHEDULE_START) return;

	_progress = SCHEDULE_ING;

	if (_scheduleWeek[_scheduleIdx] == "teach")
	{
		if (_scheduleIdx == 2 && (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12))
			_education->init(_sm->getVTeach()[_itemIdx[_scheduleIdx]], 11, _itemIdx[_scheduleIdx]);
		else if (_scheduleIdx == 2 && _mon == 2)
			_education->init(_sm->getVTeach()[_itemIdx[_scheduleIdx]], 8, _itemIdx[_scheduleIdx]);
		else
			_education->init(_sm->getVTeach()[_itemIdx[_scheduleIdx]], 10, _itemIdx[_scheduleIdx]);
	}
	else if (_scheduleWeek[_scheduleIdx] == "work")
	{
		if (_scheduleIdx == 2 && (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12))
			_work->init(_sm->getVWork()[_itemIdx[_scheduleIdx]], 11, _itemIdx[_scheduleIdx]);
		else if (_scheduleIdx == 2 && _mon == 2)
			_work->init(_sm->getVWork()[_itemIdx[_scheduleIdx]], 8, _itemIdx[_scheduleIdx]);
		else
			_work->init(_sm->getVWork()[_itemIdx[_scheduleIdx]], 10, _itemIdx[_scheduleIdx]);
	}
	else if (_scheduleWeek[_scheduleIdx] == "fight")
	{

	}
	else if (_scheduleWeek[_scheduleIdx] == "relax")
	{
		if (_scheduleIdx == 2 && (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12))
			_relax->init(_sm->getVRelax()[_itemIdx[_scheduleIdx]], 11, _itemIdx[_scheduleIdx]);
		else if (_scheduleIdx == 2 && _mon == 2)
			_relax->init(_sm->getVRelax()[_itemIdx[_scheduleIdx]], 8, _itemIdx[_scheduleIdx]);
		else
			_relax->init(_sm->getVRelax()[_itemIdx[_scheduleIdx]], 10, _itemIdx[_scheduleIdx]);

	}
}


void scheduleScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if (_vDialog.size() > 0)
		_vDialog.clear();
	string temp = "������ ����";
	_vDialog.push_back(temp);
	while (1)
	{
		if (strSize > 28)
		{
			_vDialog.push_back(str.substr(idx, 28));
			idx += 28;
			strSize -= 28;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

void scheduleScene::setScheduleImage()
{
	//����
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_teachImg[j + i * 2].img = new image;
			_teachImg[j + 2 * i].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
			_teachImg[j + 2 * i].data.rc = RectMake(460 + 170 * j, 135 + 60 * i, 160, 52);

			_teachImg[j + 2 * i].frameY = j + 2 * i;
		}
	}
	//�˹�
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i == 7 && j == 1) break;
			_workImg[j + 2 * i].img = new image;
			_workImg[j + 2 * i].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
			_workImg[j + 2 * i].data.rc = RectMake(460 + 170 * j, 435 - 60 * i, 160, 52);
			_workImg[j + 2 * i].frameY = j + 2 * i;

			if (_sm->getVWork()[j + 2 * i]->getAge() <= _princess->getInfo().age)
			{
				_workImg[j + 2 * i].data.isSelected = true;
			}
		}
	}
	//�������
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_fightImg[i * 2 + j].img = new image;
			_fightImg[i * 2 + j].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
			_fightImg[i * 2 + j].data.rc = RectMake(460 + 170 * j, 300 + i * 60, 160, 52);
			_fightImg[i * 2 + j].frameY = i * 2 + j;
		}
	}

	//�޽�
	for (int i = 0; i < 2; i++)
	{
		_relaxImg[i].img = new image;
		_relaxImg[i].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
		_relaxImg[i].data.rc = RectMake(460 + 170 * i, 300, 160, 52);
		_relaxImg[i].frameY = i;
	}
}

bool scheduleScene::dialogRender()
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
					TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, 20, 440 + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}