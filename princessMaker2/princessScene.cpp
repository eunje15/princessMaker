#include "stdafx.h"
#include "princessScene.h"


princessScene::princessScene()
{
}


princessScene::~princessScene()
{
}

HRESULT princessScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();
	_princess->setAge(_princess->getInfo().age);

	_curSound = "START";
	changeSound();

	_im = new itemManager;
	_im->init();

	_sm = new statusManager;
	_sm->init();

	_back = IMAGEMANAGER->findImage("back");
	_cal.img = IMAGEMANAGER->findImage("cal");
	_cal.x = _cal.y = 0;

	_year = _princess->getDate().year;
	_mon = _princess->getDate().mon;
	_day = _princess->getDate().day;
	_dayOfWeek = _princess->getDate().dayOfWeek;
	
	_yearImg.img = IMAGEMANAGER->findImage("year");
	_yearImg.frameY = _year - 1200;
	_monImg.img = IMAGEMANAGER->findImage("month");
	_monImg.frameY = _mon - 1;
	_dayImg.img = IMAGEMANAGER->findImage("day");
	_dayImg.frameY = _day - 1;
	_dayOfWeekImg.img = IMAGEMANAGER->findImage("dayOfWeek");
	_dayOfWeekImg.frameY = _dayOfWeek;

	if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
		_finDay = 31;
	else if (_mon == 2)
		_finDay = 28;
	else
		_finDay = 30;

	_season = _princess->getSeason();
	_flower.img = IMAGEMANAGER->findImage("flower");
	_flower.frameX = (int)_season;
	_flower.x = 0, _flower.y = 155;

	_frame.img = IMAGEMANAGER->findImage("mainFrame");
	_frame.frameX = 5;
	_frame.x = 460, _frame.y = 92;

	_status.img = IMAGEMANAGER->findImage("status");
	_status.x = WINSIZEX - _status.img->getWidth();
	_status.y = 0;
	setStringStatus();
	
	_princess->setDietType(_princess->getInfo().dietType);
	_printStrStatus.rc = RectMake(600, 166, _status.img->getWidth(), 22);
	_nameRc = RectMake(600, 12, _status.img->getWidth(), 22);
	_firstNameRc = RectMake(600, 34, _status.img->getWidth(), 22);

	_menu.img = IMAGEMANAGER->findImage("menu");
	_menu.x = WINSIZEX - _menu.img->getFrameWidth();
	_menu.y = _status.img->getHeight();
	_menu.frameX = 0;

	_constellationImg.img = IMAGEMANAGER->findImage("constellation");
	_constellationImg.frameX = _princess->getStatus().god.idx;

	_selectMenu = IMAGEMANAGER->findImage("selectMenu");
	_selectMenu->setX(WINSIZEX - _menu.img->getFrameWidth());
	_selectMenu->setY(_status.img->getHeight());


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_menubox[i * 4 + j].rc = RectMake(_menu.x + j * 50, _menu.y + 40 * i, 50, 40);
			_menubox[i].isSelected = false;
		}
	}
	_menubox[8].rc = RectMake(_menu.x, _menu.y + 80, 200, 40);
	_menubox[8].isSelected = false;
	_menuType = SELECT_NONE;

	_storeType = STORE_NONE;

	_perHealth = _perBad = _personalConnect = 0;

	setGoldImg();
	setBodyInfo();

	for (int i = 0; i < 5; i++)
	{
		if (i < 2)
			_statusImg[i].img = IMAGEMANAGER->findImage("weapon");
		else
		{
			_statusImg[i].img = IMAGEMANAGER->findImage("statusImg");
			_statusImg[i].frameX = i - 2;
		}
		_statusImg[i].data.rc = RectMake(WINSIZEX - 200 + i * 40, 117, 40, 40);
		_statusImg[i].x = WINSIZEX - 200 + i * 40, _statusImg[i].y = 117;
		_statusImg[i].frameY = 0;
	}
	_scheduleOk = false;
	
	_cube = new cube;
	_cube->init();

	_weaponStore = new weaponStore;
	//_weaponStore->init();


	_clothesStore = new clothesStore;
	//_clothesStore->init();

	_cookStore = new cookStore;
	//_cookStore->init();

	_goodsStore = new goodsStore;
	//_goodsStore->init();

	_church = new church;
	//_church->init();

	_hospital = new hospital;
	//_hospital->init();

	_castleScene = new castleScene;

	_inventoryScene = new inventoryScene;

	_saveLoadScene = new saveLoadScene;
	_saveLoadScene->setVTotalItem(_im->getVTotal());

	_scheduleScene = new scheduleScene;
	_scheduleScene->setStatusManagerAddressLink(_sm);

//	if (_princess->getStatus().hp < 200)
//		_princess->getStatusP()->hp = 200;
	return S_OK;
}

void princessScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		_princess->getStatusP()->stress = 100;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		_princess->getStatusP()->stress = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		_princess->setGold(-1000000);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F11))
	{
		_princess->setGold(1000000);
	}
	//♥♡온니짱♥♡

	if (_menuType == SELECT_NONE)
	{
		for (int i = 0; i < 9; i++)
		{
			_menubox[i].isSelected = false;
			if (PtInRect(&_menubox[i].rc, _ptMouse))
			{
				_menubox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					switch (i)
					{
					case 0:
						_menuType = SELECT_STATUS;
						setStat();
						break;
					case 1:
						_menuType = SELECT_TALK;
						setDadTalk();
						break;
					case 2:
						_menuType = SELECT_CHANGE_INFO;
						setStringStatus();
						break;
					case 3:
						_dialogSelect = false;
						_menuType = SELECT_INFO;
						setBodyInfo();
						break;
					case 4:
						_menuType = SELECT_TOWN;
						_storeType = STORE_SELECT;
						SOUNDMANAGER->stop(_curSound);
						SOUNDMANAGER->play("town");
						_curSound = "town";
						setStore();
						break;
					case 5:
						_menuType = SELECT_CASTLE;
						SOUNDMANAGER->stop(_curSound);
						_curSound = "castle";
						_castleScene->init();
						break;
					case 6:
						_menuType = SELECT_WEAPON;
						_inventoryScene->init();
						break;
					case 7:
						_menuType = SELECT_SAVE;
						_saveLoadScene->init();
						break;
					case 8:
						_menuType = SELECT_SCHEDULE;
						if (_scheduleOk)
						{
							setNextMonth();
							_scheduleOk = false;
						}
						_scheduleScene->init(_year, _mon, _curSound);
						break;
					}
					_menubox[i].isData = true;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _menuType != SELECT_SCHEDULE)
	{
		_menuType = SELECT_NONE;
		_storeType = STORE_NONE;
		if (_cube->getDialogFin()) _cube->setDialogFin(false);
		//changeSound();
	}

	if (_menuType == SELECT_TALK)
	{
		for (int i = 0; i < 3; i++)
		{
			_dadTalk[i].isSelected = false;
			if (PtInRect(&_dadTalk[i].rc, _ptMouse))
			{
				_dadTalk[i].isSelected = true;
			}
		}
	}
	else if (_menuType == SELECT_CHANGE_INFO)
	{
		changeInfo();
	}
	else if (_menuType == SELECT_TOWN)
	{
		//	clickStore();
		switch (_storeType)
		{
		case STORE_NONE: case STORE_SELECT:
		/*	if (SOUNDMANAGER->isPlaySound(_curSound)) SOUNDMANAGER->stop(_curSound);
			SOUNDMANAGER->play("town");
			_curSound = "town";*/
			clickStore();
			break;
		case STORE_WEAPON:
			_weaponStore->update();
			setGoldImg();
			if (_weaponStore->getFin())
				_storeType = STORE_SELECT;
			break;
		case STORE_ARMOR:
			_clothesStore->update();
			setGoldImg();
			if (_clothesStore->getFin())
				_storeType = STORE_SELECT;
			break;
		case STORE_COOK:
			_cookStore->update();
			setGoldImg();
			if (_cookStore->getFin())
				_storeType = STORE_SELECT;
			break;
		case STORE_GOODS:
			_goodsStore->update();
			setGoldImg();
			if (_goodsStore->getFin())
				_storeType = STORE_SELECT;
			break;
		case STORE_CHURCH:
			_church->update();
			setGoldImg();
			if (_church->getFin())
				_storeType = STORE_SELECT;
			break;
		case STORE_HOSTIPITAL:
			_hospital->update();
			setGoldImg();
			if (_hospital->getFin())
				_storeType = STORE_SELECT;
			break;
		}
	}
	else if (_menuType == SELECT_CASTLE)
	{
		_castleScene->update();
		if (_castleScene->getFin())
		{
			_menuType = SELECT_NONE;
			changeSound();
		}
	}
	else if (_menuType == SELECT_WEAPON)
	{
		_inventoryScene->update();
		if (_inventoryScene->getWeaponOk(0))
		{
			_statusImg[0].frameX = _inventoryScene->getWeaponFrameX(0);
			_statusImg[0].data.isSelected = true;
		}
		else
			_statusImg[0].data.isSelected = false;
		if (_inventoryScene->getWeaponOk(1))
		{
			_statusImg[1].frameX = _inventoryScene->getWeaponFrameX(1);
			_statusImg[1].data.isSelected = true;
		}
		else
			_statusImg[1].data.isSelected = false;
		if (_inventoryScene->getFin())
			_menuType = SELECT_NONE;
	}
	else if (_menuType == SELECT_SAVE)
	{
		_saveLoadScene->update();
		if (_saveLoadScene->getFin())
		{
			_menuType = SELECT_NONE;
			
			setLoadData();
		}
	}
	else if (_menuType == SELECT_SCHEDULE)
	{
		_scheduleScene->update();
		setDate();
		if (_scheduleScene->getFin())
		{
			_menuType = SELECT_NONE;
			_scheduleOk = true;
			changeSound();
			//setNextMonth();
		}
	}

	setGoldImg();
}

void princessScene::render()
{
	_back->render(DC);
	_cal.img->render(DC);
	_yearImg.img->frameRender(DC, 68, 11, 0, _yearImg.frameY);
	_monImg.img->frameRender(DC, 10, 40, 0, _monImg.frameY);
	_dayOfWeekImg.img->frameRender(DC, 20, 70, 0, _dayOfWeekImg.frameY);
	_dayImg.img->frameRender(DC, 88, 38, 0, _dayImg.frameY);
	_flower.img->frameRender(DC, _flower.x, _flower.y, _flower.frameX, 0);
	_frame.img->frameRender(DC, _frame.x, _frame.y, _frame.frameX, 0);

	_princess->render();

	_status.img->render(DC, _status.x, _status.y);
	DrawText(DC, _princess->getInfo().name.c_str(), strlen(_princess->getInfo().name.c_str()), &_nameRc, DT_CENTER | DT_VCENTER);
	DrawText(DC, _princess->getInfo().firstName.c_str(), strlen(_princess->getInfo().firstName.c_str()), &_firstNameRc, DT_CENTER | DT_VCENTER);
	DrawText(DC, _princess->getInfo().dietType.c_str(), strlen(_princess->getInfo().dietType.c_str()), &_printStrStatus.rc, DT_CENTER | DT_VCENTER);
	IMAGEMANAGER->findImage("number")->frameRender(DC, 615, 80, 1, 0);
	IMAGEMANAGER->findImage("number")->frameRender(DC, 630, 80, _princess->getInfo().age % 10, 0);
	_constellationImg.img->frameRender(DC, 650, 70, _constellationImg.frameX, 0);
	for (int i = 0; i < 5; i++)
	{
		if (_statusImg[i].data.isSelected)
			_statusImg[i].img->frameRender(DC, _statusImg[i].x, _statusImg[i].y, _statusImg[i].frameX, _statusImg[i].frameY);
	}

	for (int i = 0; i < 7; i++)
	{
		if (!_goldImg[i].data.isSelected) continue;
		_goldImg[i].img->frameRender(DC, _goldImg[i].data.rc.left, _goldImg[i].data.rc.top, _goldImg[i].frameX, 0);
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//Rectangle(DC, _bodyInfo[i][j].data.rc.left, _bodyInfo[i][j].data.rc.top, _bodyInfo[i][j].data.rc.right, _bodyInfo[i][j].data.rc.bottom);
			if (!_bodyInfo[i][j].data.isSelected) continue;
			_bodyInfo[i][j].img->frameRender(DC, _bodyInfo[i][j].data.rc.left, _bodyInfo[i][j].data.rc.top, _bodyInfo[i][j].frameX, 0);

		}
	}

	switch (_menuType)
	{
	case SELECT_NONE:
		_menu.img->frameRender(DC, _menu.x, _menu.y, _menu.frameX, 0);
		for (int i = 0; i < 9; i++)
		{
			if (!_menubox[i].isSelected) continue;
			_selectMenu->render(DC, _menubox[i].rc.left, _menubox[i].rc.top, 50 * (i % 4), 40 * (i / 4), _menubox[i].rc.right - _menubox[i].rc.left, _menubox[i].rc.bottom - _menubox[i].rc.top);
		}

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < 9; i++)
			{
				Rectangle(DC, _menubox[i].rc.left, _menubox[i].rc.top, _menubox[i].rc.right, _menubox[i].rc.bottom);
			}

			for (int i = 0; i < 5; i++)
			{
				Rectangle(DC, _statusImg[i].data.rc.left, _statusImg[i].data.rc.top, _statusImg[i].data.rc.right, _statusImg[i].data.rc.bottom);
			}
		}
		break;
	case SELECT_STATUS:
		statusRender();
		break;
	case SELECT_TALK:
		dadTalkRender();
		break;
	case SELECT_CHANGE_INFO:
		changeInfoRender();
		break;
	case SELECT_INFO:
		infoRender();
		break;
	case SELECT_TOWN:
		IMAGEMANAGER->findImage("storeFrame")->render(DC, 32, 113);
		IMAGEMANAGER->findImage("storePicture")->render(DC, 52, 123);
		switch (_storeType)
		{
		case STORE_NONE: case STORE_SELECT:
			storeRender();
			break;
		case STORE_WEAPON:
			_weaponStore->render();
			break;
		case STORE_ARMOR:
			_clothesStore->render();
			break;
		case STORE_COOK:
			_cookStore->render();
			break;
		case STORE_GOODS:
			_goodsStore->render();
			break;
		case STORE_CHURCH:
			_church->render();
			break;
		case STORE_HOSTIPITAL:
			_hospital->render();
			break;
		}
		break;
	case SELECT_CASTLE:
		IMAGEMANAGER->findImage("storeFrame")->render(DC, 32, 113);
		IMAGEMANAGER->findImage("castlePicture")->render(DC, 52, 123);
		_castleScene->render();
		break;
	case SELECT_WEAPON:
		_inventoryScene->render();
		break;
	case SELECT_SAVE:
		_saveLoadScene->render();
		break;
	case SELECT_SCHEDULE:
		_scheduleScene->render();
		break;
	}
	//char str[128];
	SetBkMode(DC, TRANSPARENT);
	SetTextColor(DC, RGB(255, 255, 255));
	//sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	//TextOut(DC, 50, 50, str, strlen(str));
}

void princessScene::changeSound()
{
	if (_curSound != "START")
		SOUNDMANAGER->stop(_curSound);
	if (_princess->getSeason() == SPRING)
	{
		SOUNDMANAGER->play("spring");
		_curSound = "spring";
	}
	else if (_princess->getSeason() == SUMMER)
	{
		SOUNDMANAGER->play("summer");
		_curSound = "summer";
	}
	else if (_princess->getSeason() == AUTUMN)
	{
		SOUNDMANAGER->play("autumn");
		_curSound = "autumn";
	}
	else if (_princess->getSeason() == WINTER)
	{
		SOUNDMANAGER->play("winter");
		_curSound = "winter";
	}
}

void princessScene::setInfo()
{
	_constellationImg.frameX = _princess->getStatus().god.idx;
}

void princessScene::setStat()
{
	_pInfo[0].str = "체력", _pInfo[0].data = _princess->getStatus().hp;
	_pInfo[1].str = "근력", _pInfo[1].data = _princess->getStatus().physical;
	_pInfo[2].str = "지능", _pInfo[2].data = _princess->getStatus().intelligence;
	_pInfo[3].str = "기품", _pInfo[3].data = _princess->getStatus().elegance;
	_pInfo[4].str = "매력", _pInfo[4].data = _princess->getStatus().sexual;
	_pInfo[5].str = "도덕성", _pInfo[5].data = _princess->getStatus().morality;
	_pInfo[6].str = "신앙", _pInfo[6].data = _princess->getStatus().faith;
	_pInfo[7].str = "인과", _pInfo[7].data = _princess->getStatus().karma;
	_pInfo[8].str = "감수성", _pInfo[8].data = _princess->getStatus().sensitivity;
	_pInfo[9].str = "스트레스", _pInfo[9].data = _princess->getStatus().stress;

	for (int i = 0; i < 10; i++)
	{
		_pInfo[i].strRc = RectMake(15, 160 + i * 20, 80, 20);
		_pInfo[i].dataRc = RectMake(95, 160 + i * 20, 30, 20);

		_pInfo[i].progressBar = new progressBar;
		_pInfo[i].progressBar->init(125, 160 + i * 20, 110, 20);
		_pInfo[i].progressBar->setGauge(_pInfo[i].data, 500);
	}

	_p4Stat[0].str = "전사평가", _p4Stat[0].data = _princess->getStatus().warrior;
	_p4Stat[1].str = "마법평가", _p4Stat[1].data = _princess->getStatus().magic;
	_p4Stat[2].str = "사교평가", _p4Stat[2].data = _princess->getStatus().sociality;
	_p4Stat[3].str = "가사평가", _p4Stat[3].data = _princess->getStatus().housework;

	for (int i = 0; i < 4; i++)
	{
		_p4Stat[i].strRc = RectMake(WINSIZEX - 253, 285 + i * 20, 80, 20);
		_p4Stat[i].dataRc = RectMake(WINSIZEX - 173, 285 + i * 20, 30, 20);

		_p4Stat[i].progressBar = new progressBar;
		_p4Stat[i].progressBar->init(WINSIZEX - 143, 285 + i * 20, 110, 20);
		_p4Stat[i].progressBar->setGauge(_p4Stat[i].data, 500);
	}

	_pSkill[0].str = "전투기술", _pSkill[0].data = _princess->getStatus().warriorSkill;
	_pSkill[1].str = "공격력", _pSkill[1].data = _princess->getStatus().power;
	_pSkill[2].str = "방어력", _pSkill[2].data = _princess->getStatus().defPower;
	_pSkill[3].str = "마법기술", _pSkill[3].data = _princess->getStatus().magicSkill;
	_pSkill[4].str = "마력", _pSkill[4].data = _princess->getStatus().spell;
	_pSkill[5].str = "항마력", _pSkill[5].data = _princess->getStatus().spellDefence;

	for (int i = 0; i < 6; i++)
	{
		_pSkill[i].strRc = RectMake(15, 395 + i * 20, 80, 20);
		_pSkill[i].dataRc = RectMake(95, 395 + i * 20, 30, 20);

		_pSkill[i].progressBar = new progressBar;
		_pSkill[i].progressBar->init(125, 395 + i * 20, 110, 20);
		_pSkill[i].progressBar->setGauge(_pSkill[i].data, 100);
	}

	_pBasicStat[0].str = "예의범절", _pBasicStat[0].data = _princess->getStatus().manner;
	_pBasicStat[1].str = "예술", _pBasicStat[1].data = _princess->getStatus().art;
	_pBasicStat[2].str = "화술", _pBasicStat[2].data = _princess->getStatus().conversation;
	_pBasicStat[3].str = "요리", _pBasicStat[3].data = _princess->getStatus().cooking;
	_pBasicStat[4].str = "청소세탁", _pBasicStat[4].data = _princess->getStatus().cleaning;
	_pBasicStat[5].str = "성품", _pBasicStat[5].data = _princess->getStatus().personality;

	for (int i = 0; i < 6; i++)
	{
		_pBasicStat[i].strRc = RectMake(WINSIZEX - 253, 400 + i * 20, 80, 20);
		_pBasicStat[i].dataRc = RectMake(WINSIZEX - 173, 400 + i * 20, 30, 20);

		_pBasicStat[i].progressBar = new progressBar;
		_pBasicStat[i].progressBar->init(WINSIZEX - 143, 400 + i * 20, 110, 20);
		_pBasicStat[i].progressBar->setGauge(_pBasicStat[i].data, 100);
	}
}

void princessScene::setDadTalk()
{
	_dadTalk[0].str = "부녀간의 이야기";
	_dadTalk[1].str = "용돈";
	_dadTalk[2].str = "설교";

	for (int i = 0; i < 3; i++)
	{
		_dadTalk[i].rc = RectMake(602, 300 + i * 28, 150, 28);
		_dadTalk[i].isSelected = false;
	}
}

void princessScene::changeInfo()
{
	for (int i = 0; i < 4; i++)
	{
		_strStatus[i].isSelected = false;
		if (PtInRect(&_strStatus[i].rc, _ptMouse))
		{
			_strStatus[i].isSelected = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (!_isClick) return;
				_strStatus[i].isChoose = true;
				_dialogSelect = true;

				char temp[128];
				sprintf_s(temp, "DADTALK%d", i);

				setDialog(_cube->getDialog(temp));

				for (int i = 0; i < 2; i++)
				{
					_chooseAnswer[i].rc = RectMake(610, 295 + i * 28, 120, 28);
					_chooseAnswer[i].isSelected = _chooseAnswer[i].isChoose = false;
				}
				_chooseAnswer[0].str = "이 방침으로";
				_chooseAnswer[1].str = "지금까지대로";
				for (int i = 0; i < 4; i++)
				{
					_strStatus[i].rc = RectMake(0, 0, 0, 0);
				}
				return;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		_chooseAnswer[i].isSelected = false;
		if (PtInRect(&_chooseAnswer[i].rc, _ptMouse))
		{
			_chooseAnswer[i].isSelected = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (!_isClick) return;
				_menuType = SELECT_NONE;
				_dialogSelect = false;
				_idx = 0;
				if (_cube->getDialogFin()) _cube->setDialogFin(false);
				if (i == 0)
				{
					for (int i = 0; i < 4; i++)
					{
						if (_strStatus[i].isChoose)
						{
							_princess->setDietType(_strStatus[i].str);
						}
					}
				}
			}
		}
	}
}

void princessScene::infoRender()
{
	IMAGEMANAGER->findImage("info1Back")->render(DC, 28, 103);
	IMAGEMANAGER->findImage("info2Back")->render(DC, 28, 106 + IMAGEMANAGER->findImage("info1Back")->getHeight());
	IMAGEMANAGER->findImage("info3Back")->render(DC, WINSIZEX - 260, 105 + IMAGEMANAGER->findImage("info1Back")->getHeight());
	//IMAGEMANAGER->findImage("info4Back")->render(DC, WINSIZEX - 285, 228 + IMAGEMANAGER->findImage("info1Back")->getHeight());
	IMAGEMANAGER->findImage("wideBack")->render(DC, WINSIZEX - 405, 228 + IMAGEMANAGER->findImage("info1Back")->getHeight());

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 400, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("돋움체"));
	oldFont = (HFONT)SelectObject(DC, font);
	//info1
	TextOut(DC, 40, 110, "이름", strlen("이름"));
	TextOut(DC, 40, 135, "성", strlen("성"));
	TextOut(DC, 40, 160, "혈액형", strlen("혈액형"));
	TextOut(DC, 40, 185, "나이", strlen("나이"));
	TextOut(DC, 40, 210, "생일", strlen("생일"));
	TextOut(DC, 40, 235, "별자리", strlen("별자리"));
	TextOut(DC, 40, 260, "수호성", strlen("수호성"));

	TextOut(DC, 120, 110, _princess->getInfo().name.c_str(), strlen(_princess->getInfo().name.c_str()));
	TextOut(DC, 120, 135, _princess->getInfo().firstName.c_str(), strlen(_princess->getInfo().firstName.c_str()));
	TextOut(DC, 120, 160, _princess->getInfo().strBlood.c_str(), strlen(_princess->getInfo().strBlood.c_str()));
	TextOut(DC, 120, 185, to_string(_princess->getInfo().age).c_str(), strlen(to_string(_princess->getInfo().age).c_str()));
	char str[128];
	sprintf_s(str, "%d/%d/%d", _princess->getInfo().year, _princess->getInfo().mon, _princess->getInfo().day);
	TextOut(DC, 120, 210, str, strlen(str));
	TextOut(DC, 120, 235, _princess->getStatus().god.constellation.c_str(), strlen(_princess->getStatus().god.constellation.c_str()));
	TextOut(DC, 120, 260, _princess->getStatus().god.planet.c_str(), strlen(_princess->getStatus().god.planet.c_str()));

	//info2
	TextOut(DC, 40, 300, "질병 지수", strlen("질병 지수"));
	TextOut(DC, 40, 325, "불량화 지수", strlen("불량화 지수"));
	TextOut(DC, 40, 350, "인맥", strlen("인맥"));

	TextOut(DC, 200, 300, (to_string(_perHealth) + "%").c_str(), strlen((to_string(_perHealth) + "%").c_str()));
	TextOut(DC, 200, 325, (to_string(_perBad) + "%").c_str(), strlen((to_string(_perBad) + "%").c_str()));
	TextOut(DC, 200, 350, to_string(_personalConnect).c_str(), strlen(to_string(_personalConnect).c_str()));

	//임시로 지정
	TextOut(DC, 40, 375, "건강합니다", strlen("건강합니다"));
	TextOut(DC, 40, 400, "솔직합니다", strlen("솔직합니다"));

	string str1 = "건강「" + _princess->getInfo().dietType + "」";
	TextOut(DC, 40, 440, str1.c_str(), strlen(str1.c_str()));

	//info3
	/*TextOut(DC, WINSIZEX - 250, 300, "키", strlen("키"));
	TextOut(DC, WINSIZEX - 250, 320, "몸무게", strlen("몸무게"));
	TextOut(DC, WINSIZEX - 250, 340, "가슴", strlen("가슴"));
	TextOut(DC, WINSIZEX - 250, 360, "허리", strlen("허리"));
	TextOut(DC, WINSIZEX - 250, 380, "엉덩이", strlen("엉덩이"));*/
	for (int i = 0; i < 5; i++)
	{
		HBRUSH brush, oldBrush;
		brush = CreateSolidBrush(RGB(111, 17, 17));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		FillRect(DC, &_pBodyInfo[i].strRc, brush);
		Rectangle(DC, _pBodyInfo[i].strRc.left, _pBodyInfo[i].strRc.top, _pBodyInfo[i].strRc.right, _pBodyInfo[i].strRc.bottom);
		TextOut(DC, _pBodyInfo[i].strRc.left, _pBodyInfo[i].strRc.top + 2, _pBodyInfo[i].str.c_str(), strlen(_pBodyInfo[i].str.c_str()));
		SelectObject(DC, oldBrush);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		Rectangle(DC, _pBodyInfo[i].dataRc.left, _pBodyInfo[i].dataRc.top, _pBodyInfo[i].dataRc.right, _pBodyInfo[i].dataRc.bottom);
		char str[128];
		sprintf_s(str, "%6.2f", _pBodyInfo[i].data);
		TextOut(DC, _pBodyInfo[i].dataRc.left, _pBodyInfo[i].dataRc.top + 2, str, strlen(str));
		SelectObject(DC, oldBrush);
		DeleteObject(brush);
		_pBodyInfo[i].progressBar->render();
	}

	//info4
	TextOut(DC, WINSIZEX - 395, 425, "무기", strlen("무기"));
	if (_weaponOk[1])
	{
		IMAGEMANAGER->findImage("weapon")->frameRender(DC, WINSIZEX - 355, 420, _selectItem[1]->getFrameX(), 0);
		TextOut(DC, WINSIZEX - 315, 420, _selectItem[1]->getName().c_str(), strlen(_selectItem[1]->getName().c_str()));
		int strSize = 0;
		for (int i = 0; i < _selectItem[1]->getProperty().size(); i++)
		{
			string str = _selectItem[1]->getProperty()[i].first;
			if (_selectItem[1]->getProperty()[i].second > 0)
				str += "+";
			str += to_string((int)_selectItem[1]->getProperty()[i].second) + " ";
			TextOut(DC, WINSIZEX - 315 + strSize*6, 445, str.c_str(), strlen(str.c_str()));
			strSize += strlen(str.c_str()) + 6;
		}
	}
	TextOut(DC, WINSIZEX - 395, 480, "방어구", strlen("방어구"));
	if (_weaponOk[0])
	{
		IMAGEMANAGER->findImage("weapon")->frameRender(DC, WINSIZEX - 335, 475, _selectItem[0]->getFrameX(), 0);
		TextOut(DC, WINSIZEX - 295, 475, _selectItem[0]->getName().c_str(), strlen(_selectItem[0]->getName().c_str()));
		int strSize = 0;
		for (int i = 0; i < _selectItem[0]->getProperty().size(); i++)
		{
			string str = _selectItem[0]->getProperty()[i].first;
			if (_selectItem[0]->getProperty()[i].second > 0)
				str += "+";
			str += to_string((int)_selectItem[0]->getProperty()[i].second) + " ";
			TextOut(DC, WINSIZEX - 295 + strSize*6, 500, str.c_str(), strlen(str.c_str()));
			strSize += strlen(str.c_str()) + 6;
		}
	}
	SelectObject(DC, oldFont);
	DeleteObject(font);
}

void princessScene::statusRender()
{
	IMAGEMANAGER->findImage("status1Back")->render(DC, 8, 150);
	IMAGEMANAGER->findImage("status2Back")->render(DC, 8, 165 + IMAGEMANAGER->findImage("status1Back")->getHeight());
	IMAGEMANAGER->findImage("status3Back")->render(DC, WINSIZEX - 260, 275);
	IMAGEMANAGER->findImage("status4Back")->render(DC, WINSIZEX - 260, 390);

	for (int i = 0; i < 10; i++)
	{
		HBRUSH brush, oldBrush;
		brush = CreateSolidBrush(RGB(111, 17, 17));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		FillRect(DC, &_pInfo[i].strRc, brush);
		Rectangle(DC, _pInfo[i].strRc.left, _pInfo[i].strRc.top, _pInfo[i].strRc.right, _pInfo[i].strRc.bottom);
		TextOut(DC, _pInfo[i].strRc.left, _pInfo[i].strRc.top + 2, _pInfo[i].str.c_str(), strlen(_pInfo[i].str.c_str()));
		if (i < 4)
		{
			FillRect(DC, &_p4Stat[i].strRc, brush);
			Rectangle(DC, _p4Stat[i].strRc.left, _p4Stat[i].strRc.top, _p4Stat[i].strRc.right, _p4Stat[i].strRc.bottom);
			TextOut(DC, _p4Stat[i].strRc.left, _p4Stat[i].strRc.top + 2, _p4Stat[i].str.c_str(), strlen(_p4Stat[i].str.c_str()));
		}
		SelectObject(DC, oldBrush);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		Rectangle(DC, _pInfo[i].dataRc.left, _pInfo[i].dataRc.top, _pInfo[i].dataRc.right, _pInfo[i].dataRc.bottom);
		char str[128];
		sprintf_s(str, "%3d", _pInfo[i].data);
		TextOut(DC, _pInfo[i].dataRc.left + 2, _pInfo[i].dataRc.top + 2, str, strlen(str));
		if (i < 4)
		{
			FillRect(DC, &_p4Stat[i].dataRc, brush);
			Rectangle(DC, _p4Stat[i].dataRc.left, _p4Stat[i].dataRc.top, _p4Stat[i].dataRc.right, _p4Stat[i].dataRc.bottom);
			sprintf_s(str, "%3d", _p4Stat[i].data);
			TextOut(DC, _p4Stat[i].dataRc.left + 2, _p4Stat[i].dataRc.top + 2, str, strlen(str));
			_p4Stat[i].progressBar->render();
		}
		SelectObject(DC, oldBrush);
		DeleteObject(brush);
		_pInfo[i].progressBar->render();
	}

	for (int i = 0; i < 6; i++)
	{
		HBRUSH brush, oldBrush;
		brush = CreateSolidBrush(RGB(53, 78, 159));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		FillRect(DC, &_pSkill[i].strRc, brush);
		Rectangle(DC, _pSkill[i].strRc.left, _pSkill[i].strRc.top, _pSkill[i].strRc.right, _pSkill[i].strRc.bottom);
		TextOut(DC, _pSkill[i].strRc.left, _pSkill[i].strRc.top + 2, _pSkill[i].str.c_str(), strlen(_pSkill[i].str.c_str()));
		FillRect(DC, &_pBasicStat[i].strRc, brush);
		Rectangle(DC, _pBasicStat[i].strRc.left, _pBasicStat[i].strRc.top, _pBasicStat[i].strRc.right, _pBasicStat[i].strRc.bottom);
		TextOut(DC, _pBasicStat[i].strRc.left, _pBasicStat[i].strRc.top + 2, _pBasicStat[i].str.c_str(), strlen(_pBasicStat[i].str.c_str()));
		SelectObject(DC, oldBrush);
		DeleteObject(brush);
		brush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		Rectangle(DC, _pSkill[i].dataRc.left, _pSkill[i].dataRc.top, _pSkill[i].dataRc.right, _pSkill[i].dataRc.bottom);
		char str[128];
		sprintf_s(str, "%3d", _pSkill[i].data);
		TextOut(DC, _pSkill[i].dataRc.left + 2, _pSkill[i].dataRc.top + 2, str, strlen(str));
		_pSkill[i].progressBar->render();
		Rectangle(DC, _pBasicStat[i].dataRc.left, _pBasicStat[i].dataRc.top, _pBasicStat[i].dataRc.right, _pBasicStat[i].dataRc.bottom);
		sprintf_s(str, "%3d", _pBasicStat[i].data);
		TextOut(DC, _pBasicStat[i].dataRc.left + 2, _pBasicStat[i].dataRc.top + 2, str, strlen(str));
		_pBasicStat[i].progressBar->render();
		SelectObject(DC, oldBrush);
		DeleteObject(brush);
	}
}

void princessScene::setGoldImg()
{
	int gold = _princess->getGold();

	for (int i = 0; i < 7; i++)
	{
		_goldImg[i].data.isSelected = false;
	}

	for (int i = 0; i < 7; i++)
	{
		_goldImg[i].img = IMAGEMANAGER->findImage("number");
		_goldImg[i].frameX = gold % 10;
		_goldImg[i].data.isSelected = true;
		_goldImg[i].data.rc = RectMake(760 - i * 10, 88, 10, 20);
		if ((gold = gold / 10) == 0) break;
	}
}

void princessScene::setBodyInfo()
{
	tagBody bodyInfo = _princess->getBodyInfo();

	for (int i = 0; i < 5; i++)
	{
		int idx;

		if (i == 0) idx = bodyInfo.height;
		else if (i == 1) idx = bodyInfo.weight;
		else if (i == 2) idx = bodyInfo.bast;
		else if (i == 3) idx = bodyInfo.waist;
		else if (i == 4) idx = bodyInfo.hip;

		for (int j = 0; j < 3; j++)
		{
			_bodyInfo[i][j].img = IMAGEMANAGER->findImage("number");
			_bodyInfo[i][j].frameX = idx % 10;
			_bodyInfo[i][j].data.isSelected = true;
			if (i < 3)
				_bodyInfo[i][j].data.rc = RectMake(630 - (j) * 10 + i * 34, 189, 10, 20);
			else
				_bodyInfo[i][j].data.rc = RectMake(630 - (j) * 10 + i * 36, 189, 10, 20);
			if ((idx = idx / 10) == 0) break;
		}
	}

	_pBodyInfo[0].str = "키", _pBodyInfo[0].data = _princess->getBodyInfo().height;
	_pBodyInfo[1].str = "몸무게", _pBodyInfo[1].data = _princess->getBodyInfo().weight;
	_pBodyInfo[2].str = "가슴", _pBodyInfo[2].data = _princess->getBodyInfo().bast;
	_pBodyInfo[3].str = "허리", _pBodyInfo[3].data = _princess->getBodyInfo().waist;
	_pBodyInfo[4].str = "엉덩이", _pBodyInfo[4].data = _princess->getBodyInfo().hip;


	for (int i = 0; i < 5; i++)
	{
		_pBodyInfo[i].strRc = RectMake(WINSIZEX - 250, 300 + i * 20, 80, 20);
		_pBodyInfo[i].dataRc = RectMake(WINSIZEX - 170, 300 + i * 20, 60, 20);

		_pBodyInfo[i].progressBar = new progressBar;
		_pBodyInfo[i].progressBar->init(WINSIZEX - 110, 300 + i * 20, 80, 20);
		if (i == 0)
			_pBodyInfo[i].progressBar->setGauge(_pBodyInfo[i].data, 200);
		else
			_pBodyInfo[i].progressBar->setGauge(_pBodyInfo[i].data, 150);
	}

	_weaponOk[0] = _weaponOk[1] = false;
	for (int i = 0; i < _princess->getVItem().size(); i++)
	{
		if (_princess->getVItem()[i]->getIsWear())
		{
			if (_princess->getVItem()[i]->getType() == ITEM_WEAPON)
			{
				_selectItem[1] = _princess->getVItem()[i];
				_weaponOk[1] = true;
			}
			else if (_princess->getVItem()[i]->getType() == ITEM_ARMOR)
			{
				_selectItem[0] = _princess->getVItem()[i];
				_weaponOk[0] = true;
			}
		}
	}
}

void princessScene::setDate()
{
	if (_scheduleScene->getProgess() == 2)
	{
		_scheduleScene->setProgess(0);
		if (_day < _finDay)
		{
			_day = _princess->getDate().day + 1;
			_dayImg.frameY = _day - 1;
			_dayOfWeek = _princess->getDate().dayOfWeek + 1;
			if (_dayOfWeek == 7) _dayOfWeek = 0;
			_dayOfWeekImg.frameY = _dayOfWeek;
			_princess->setDay(_day);
			_princess->setDayOfWeek(_dayOfWeek);
		}
		return;
	}
	_day = _princess->getDate().day;
	_dayImg.frameY = _day - 1;
	_dayOfWeek = _princess->getDate().dayOfWeek;
	_dayOfWeekImg.frameY = _dayOfWeek;
}

void princessScene::setNextMonth()
{
	if (_mon < 12)
		_mon++;
	else
	{
		_mon = 1;
		_year++;
		_yearImg.frameY = _year - 1200;
		_princess->setYear(_year);
		_princess->setAge(_princess->getInfo().age + 1);
		_princess->getInfoP()->age++;
		_princess->getBodyInfoP()->waist -= 0.3f;
	}

	if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
		_finDay = 31;
	else if (_mon == 2)
		_finDay = 28;
	else
		_finDay = 30;

	_monImg.frameY = _mon - 1;
	_day = 1;
	_dayImg.frameY = _day - 1;
	_dayOfWeek = _princess->getDate().dayOfWeek + 1;
	if (_dayOfWeek == 7) _dayOfWeek = 0;
	_dayOfWeekImg.frameY = _dayOfWeek;

	if (_princess->getInfo().strBlood == "A")
	{
		_princess->getStatusP()->morality += 3;
		_princess->getStatusP()->stress += 2;
	}
	else if (_princess->getInfo().strBlood == "B")
	{
		_princess->getStatusP()->stress -= 2;
		if (_princess->getStatus().stress < 0)
			_princess->getStatusP()->stress = 0;
	}
	else if (_princess->getInfo().strBlood == "AB")
	{
		_princess->getStatusP()->sensitivity += 2;
	}

	if (_princess->getInfo().dietType == "어쨌든 튼튼하게")
	{
		if (_princess->getInfo().age < 16)
			_princess->getBodyInfoP()->weight += RND->getFromFloatTo(0.28f, 0.35f);
		else
			_princess->getBodyInfoP()->weight += RND->getFromFloatTo(0.16f, 0.20f);
		_princess->getBodyInfoP()->height += 0.4f;
		_princess->getBodyInfoP()->bast += 0.04f;
		_princess->getBodyInfoP()->hip += 0.08f;
	}
	else if (_princess->getInfo().dietType == "무리하지 않는다")
	{
		if (_princess->getInfo().age < 16)
			_princess->getBodyInfoP()->weight += RND->getFromFloatTo(0.19f, 0.22f);
		else
			_princess->getBodyInfoP()->weight += RND->getFromFloatTo(0.05f, 0.08f);
		_princess->getBodyInfoP()->height += 0.3f;
		_princess->getBodyInfoP()->bast += 0.03f;
		_princess->getBodyInfoP()->hip += 0.06f;
	}
	else if (_princess->getInfo().dietType == "얌전한 아이로")
	{
		if (_princess->getInfo().age < 16)
			_princess->getBodyInfoP()->weight += RND->getFromFloatTo(0.10f, 0.13f);
		else
			_princess->getBodyInfoP()->weight += RND->getFromFloatTo(0.01f, 0.04f);
		_princess->getBodyInfoP()->height += 0.3f;
		_princess->getBodyInfoP()->bast += 0.02f;
		_princess->getBodyInfoP()->hip += 0.05f;
	}
	else if (_princess->getInfo().dietType == "다이어트를 시킨다")
	{
		if (_princess->getInfo().age < 16)
			_princess->getBodyInfoP()->weight -= RND->getFromFloatTo(0.00f, 0.06f);
		else
			_princess->getBodyInfoP()->weight -= RND->getFromFloatTo(0.5f, 1.0f);
		_princess->getBodyInfoP()->height += 0.2f;
		_princess->getBodyInfoP()->bast += 0.01f;
		_princess->getBodyInfoP()->hip += 0.04f;
	}
	if (_mon == 3)
		_season = SPRING;
	else if (_mon == 6)
		_season = SUMMER;
	else if (_mon == 9)
		_season = AUTUMN;
	else if (_mon == 12)
		_season = WINTER;
	_flower.frameX = (int)_season;

	_princess->setMonth(_mon);
	_princess->setDay(_day);
	_princess->setDayOfWeek(_dayOfWeek);
	_princess->setSeason((int)_season);
	setStat();
	setBodyInfo();

	if (_princess->getStatus().stress <= 0)
		_princess->getDateP()->faceType = PRINCESS_NOSTRESS;
	else
		_princess->getDateP()->faceType = PRINCESS_NORMAL;
}

void princessScene::setLoadData()
{
	setInfo();
	_year = _princess->getDate().year;
	_yearImg.frameY = _year - 1200;
	_mon = _princess->getDate().mon;
	_monImg.frameY = _mon - 1;
	_day = _princess->getDate().day;
	_dayImg.frameY = _day - 1;
	_dayOfWeek = _princess->getDate().dayOfWeek;
	_dayOfWeekImg.frameY = _dayOfWeek;
	setStat();
	setBodyInfo();
	_flower.frameX = (int)_princess->getSeason();
	if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
	{
		if(_day != 31)
			_scheduleOk = false;
	}
	else if (_mon == 2 && _day != 28)
		_scheduleOk = false;
	else
	{
		if(_day != 30)
			_scheduleOk = false;
	}
}

void princessScene::dadTalkRender()
{
	IMAGEMANAGER->findImage("3Back")->render(DC, 592, 286);

	for (int i = 0; i < 3; i++)
	{
		if (_dadTalk[i].isSelected)
		{
			HBRUSH brush, oldBrush;
			brush = CreateSolidBrush(RGB(43, 0, 0));
			oldBrush = (HBRUSH)SelectObject(DC, brush);
			FillRect(DC, &_dadTalk[i].rc, brush);
			SelectObject(DC, oldBrush);
			DeleteObject(brush);
		}
		TextOut(DC, _dadTalk[i].rc.left + 2, _dadTalk[i].rc.top + 5, _dadTalk[i].str.c_str(), strlen(_dadTalk[i].str.c_str()));
	}
}

void princessScene::changeInfoRender()
{
	IMAGEMANAGER->findImage("dialogFrame")->render(DC, 10, 426);
	IMAGEMANAGER->findImage("frame")->render(DC, 20 + IMAGEMANAGER->findImage("dialogFrame")->getWidth(), 426);
	_cube->setXY(30 + IMAGEMANAGER->findImage("dialogFrame")->getWidth(), 436);
	_cube->render();

	if (_cube->getDialogFin())
	{
		if (!_dialogSelect)
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, 15, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}

			IMAGEMANAGER->findImage("4Back")->render(DC, 600, 280);

			for (int i = 0; i < 4; i++)
			{
				if (_strStatus[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_strStatus[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _strStatus[i].rc.left + 2, _strStatus[i].rc.top + 5, _strStatus[i].str.c_str(), strlen(_strStatus[i].str.c_str()));
			}
		}
		else
		{
			IMAGEMANAGER->findImage("answer")->render(DC, 10, 260);

			string str;
			for (int i = 0; i < 4; i++)
			{
				if (_strStatus[i].isChoose)
				{
					str = _strStatus[i].str;
					break;
				}
			}
			TextOut(DC, 20, 280, str.c_str(), strlen(str.c_str()));

			if (_idx < _vDialog.size())
			{
				_isClick = false;
				string temp = DIALOG->getCurrentDialog();
				if (temp == "end")
				{
					_idx++;
					if (_idx < _vDialog.size())
						DIALOG->setDialog(_vDialog[_idx], 5);
				}
				else
				{
					if (_idx > 0)
					{
						for (int i = 0; i < _idx; i++)
						{
							TextOut(DC, 15, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
						}
					}
					TextOut(DC, 15, 440 + _idx * 30, temp.c_str(), strlen(temp.c_str()));
				}
			}
			else
			{
				_isClick = true;
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, 15, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}

				IMAGEMANAGER->findImage("2Back")->render(DC, 600, 280);
				for (int i = 0; i < 2; i++)
				{
					if (_chooseAnswer[i].isSelected)
					{
						HBRUSH brush, oldBrush;
						brush = CreateSolidBrush(RGB(43, 0, 0));
						oldBrush = (HBRUSH)SelectObject(DC, brush);
						FillRect(DC, &_chooseAnswer[i].rc, brush);
						SelectObject(DC, oldBrush);
						DeleteObject(brush);
					}
					TextOut(DC, _chooseAnswer[i].rc.left + 2, _chooseAnswer[i].rc.top + 5, _chooseAnswer[i].str.c_str(), strlen(_chooseAnswer[i].str.c_str()));
				}
			}
		}
	}
	else
	{
		if (_idx < _vDialog.size())
		{
			_isClick = false;
			string temp = DIALOG->getCurrentDialog();
			if (temp == "end")
			{
				_idx++;
				if (_idx < _vDialog.size())
					DIALOG->setDialog(_vDialog[_idx], 5);
			}
			else
			{
				if (_idx > 0)
				{
					for (int i = 0; i < _idx; i++)
					{
						TextOut(DC, 15, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
					}
				}
				TextOut(DC, 15, 440 + _idx * 30, temp.c_str(), strlen(temp.c_str()));
			}
		}
		else
		{
			_idx = 0;
			_isClick = true;
			_cube->setDialogFin(true);
		}
	}
}

void princessScene::release()
{
}

void princessScene::setStringStatus()
{
	_strStatus[0].str = "무리하지 않는다";
	_strStatus[1].str = "어쨌든 튼튼하게";
	_strStatus[2].str = "얌전한 아이로";
	_strStatus[3].str = "다이어트 시킨다";

	if (_menuType == SELECT_CHANGE_INFO)
	{
		for (int i = 0; i < 4; i++)
		{
			_strStatus[i].rc = RectMake(610, 290 + i * 28, 150, 28);
			_strStatus[i].isSelected = false;
			_strStatus[i].isChoose = false;
			_dialog[i].isSelected = false;
		}

		setDialog(_cube->getDialog("DADTALK"));

		for (int i = 0; i < 2; i++)
		{
			_chooseAnswer[i].rc = RectMake(0, 0, 0, 0);
			_chooseAnswer[i].isSelected = _chooseAnswer[i].isChoose = false;
		}
	}
}

void princessScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	while (1)
	{
		if (strSize > 30)
		{
			_vDialog.push_back(str.substr(idx, 30));
			idx += 30;
			strSize -= 30;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

void princessScene::setStore()
{
	_storeDialog = "딸과 거리를 나왔습니다. 어디로 가겠습니까?";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (_store[i * 2 + j].img == NULL)
			{
				_store[i * 2 + j].img = new image;
				_store[i * 2 + j].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, false, RGB(255, 0, 255));
			}
			_store[i * 2 + j].data.rc = RectMake(460 + j * 170, 254 + i * 60, 160, 52);
			_store[i * 2 + j].frameX = _store[i * 2 + j].frameY = 0;
			_store[i * 2 + j].data.isSelected = _store[i * 2 + j].data.isChoose = false;
			_store[i * 2 + j].x = i * 2 + j;
		}
	}
	if (_store[6].img == NULL)
	{
		_store[6].img = new image;
		_store[6].img->init("image/main/storeQuit(240x40,2x1).bmp", 240, 40, 2, 1, false, RGB(255, 0, 255));
	}
	_store[6].data.rc = RectMake(526, 446, 120, 40);
	_store[6].frameX = _store[6].frameY = 0;
	_store[6].data.isSelected = _store[6].data.isChoose = false;

	_store[0].data.str = "무기점", _store[1].data.str = "의상실", _store[2].data.str = "요리점";
	_store[3].data.str = "잡화점", _store[4].data.str = "교회", _store[5].data.str = "병원";
	_store[6].data.str = "관둔다";
	_count = 0;
}

void princessScene::setRectZero(RECT* rc)
{
	*rc = RectMake(0, 0, 0, 0);
}
void princessScene::clickStore()
{
	_count++;
	if (_count < 30) return;

	for (int i = 0; i < 7; i++)
	{
		_store[i].frameX = 0;
		if (PtInRect(&_store[i].data.rc, _ptMouse))
		{
			_store[i].frameX = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (_storeType != STORE_SELECT) return;
				switch (i)
				{
				case 0:
					_storeType = STORE_WEAPON;
					_weaponStore->init(_im->getVWeapon(), _im->getVArmor());
					_weaponStore->setFin(false);
					break;
				case 1:
					_storeType = STORE_ARMOR;
					_clothesStore->init(_im->getVClothes());
					_clothesStore->setFin(false);
					break;
				case 2:
					_storeType = STORE_COOK;
					_cookStore->init(_im->getVCook());
					_cookStore->setFin(false);
					break;
				case 3:
					_storeType = STORE_GOODS;
					_goodsStore->init(_im->getVGoods());
					_goodsStore->setFin(false);
					break;
				case 4:
					_storeType = STORE_CHURCH;
					_church->init();
					_church->setFin(false);
					break;
				case 5:
					_storeType = STORE_HOSTIPITAL;
					_hospital->init();
					_hospital->setFin(false);
					break;
				case 6:
					_menuType = SELECT_NONE;
					_storeType = STORE_NONE;
					changeSound();
					break;
				}
			}
		}
	}
}

void princessScene::storeRender()
{
	IMAGEMANAGER->findImage("wideBack")->render(DC, 35, 410);
	TextOut(DC, 45, 420, _storeDialog.c_str(), strlen(_storeDialog.c_str()));

	for (int i = 0; i < 7; i++)
	{
		//Rectangle(DC, _store[i].data.rc.left, _store[i].data.rc.top, _store[i].data.rc.right, _store[i].data.rc.bottom);
		_store[i].img->frameRender(DC, _store[i].data.rc.left, _store[i].data.rc.top, _store[i].frameX, _store[i].frameY);
		if (i < 6)
		{
			IMAGEMANAGER->findImage("storeIcon")->frameRender(DC, _store[i].data.rc.left + 10, _store[i].data.rc.top + 6, _store[i].x, 0);
			TextOut(DC, _store[i].data.rc.left + 70, _store[i].data.rc.top + 15, _store[i].data.str.c_str(), strlen(_store[i].data.str.c_str()));
		}
		else
			TextOut(DC, _store[i].data.rc.left + 20, _store[i].data.rc.top + 10, _store[i].data.str.c_str(), strlen(_store[i].data.str.c_str()));
	}
}
