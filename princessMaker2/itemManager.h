#pragma once
#include "gameNode.h"
#include "item.h"

enum DATA_TYPE { DATA_WEAPON, DATA_ARMOR, DATA_CLOTHES, DATA_GOODS, DATA_COOK };
class itemManager : public gameNode
{
private:
	vector<item*> _vWeapon;
	vector<item*> _vArmor;
	vector<item*> _vClothes;
	vector<item*> _vGoods;
	vector<item*> _vCook;
	vector<item*> _vTotal;

	DATA_TYPE _type;
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void update();
	void render();
	void release();
	void loadData(const char* dataName);

	vector<item*> getVWeapon() { return _vWeapon; }
	vector<item*> getVArmor() { return _vArmor; }
	vector<item*> getVClothes() { return _vClothes; }
	vector<item*> getVGoods() { return _vGoods; }
	vector<item*> getVCook() { return _vCook; }
	vector<item*> getVTotal() { return _vTotal; }
};

