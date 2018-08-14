#pragma once
#include "gameNode.h"
#include "princess.h"
#include "cube.h"
#include "weaponStore.h"
#include "clothesStore.h"
#include "cookStore.h"
#include "goodsStore.h"
#include "church.h"
#include "hospital.h"
#include "castleScene.h"
#include "inventoryScene.h"
#include "itemManager.h"
#include "saveLoadScene.h"
#include "scheduleScene.h"
#include "statusManager.h"


class princessScene : public gameNode
{
private:
	enum MENU_TYPE {
		SELECT_NONE, SELECT_STATUS, SELECT_TALK, SELECT_CHANGE_INFO, SELECT_INFO,
		SELECT_TOWN, SELECT_CASTLE, SELECT_WEAPON, SELECT_SAVE, SELECT_SCHEDULE
	};
	enum STORE_TYPE { STORE_NONE, STORE_WEAPON, STORE_ARMOR, STORE_COOK, STORE_GOODS, STORE_CHURCH, STORE_HOSTIPITAL, STORE_SELECT };

private:
	princess* _princess;
	image *_back, *_selectMenu;
	MENU_TYPE _menuType;
	STORE_TYPE _storeType;
	int _year, _mon, _day, _dayOfWeek, _finDay;
	int _perHealth, _perBad, _personalConnect, _idx, _count;
	SEASON_TYPE _season;
	tagImg _cal, _status, _menu, _flower, _frame;
	tagImg _yearImg, _monImg, _dayImg, _dayOfWeekImg, _constellationImg;
	tagObj _menubox[9];
	RECT _nameRc, _firstNameRc;
	tagString _strStatus[4], _printStrStatus;
	tagProgress _pInfo[10], _p4Stat[4], _pSkill[6], _pBasicStat[6];
	tagProgressFloat _pBodyInfo[5];
	tagString _dadTalk[3], _changeInfo[4], _dialog[4], _chooseAnswer[2];
	bool _dialogSelect, _isClick, _scheduleOk;
	cube* _cube;
	vector<string> _vDialog;
	tagImg _store[7], _goldImg[7], _bodyInfo[5][3];
	string _storeDialog;

	weaponStore* _weaponStore;
	clothesStore* _clothesStore;
	cookStore* _cookStore;
	goodsStore* _goodsStore;
	church*	_church;
	hospital* _hospital;

	castleScene* _castleScene;
	inventoryScene* _inventoryScene;
	saveLoadScene* _saveLoadScene;
	scheduleScene* _scheduleScene;

	itemManager* _im;
	statusManager* _sm;

public:
	princessScene();
	~princessScene();

	HRESULT init();
	void update();
	void render();
	void setInfo();
	void setStat();
	void setDadTalk();
	void changeInfo();
	void infoRender();
	void statusRender();
	void setGoldImg();
	void setBodyInfo();
	void setDate();
	void setNextMonth();
	void setLoadData();
	void dadTalkRender();
	void changeInfoRender();
	void release();

	void setStringStatus();
	void setDialog(string dialog);
	void setStore();
	void setRectZero(RECT * rc);
	void clickStore();
	void storeRender();
};

