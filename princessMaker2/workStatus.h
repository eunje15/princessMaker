#pragma once
#include "gameNode.h"
class workStatus : public gameNode
{
private:
	string _name;
	string _person;

	int _salary;
	int _plusSalary;

	int _age;
	int _stress;
	int _weight; //°¡ÁßÄ¡
	int _frameX;

	vector<pair<string, pair<int, int>>> _property;
	vector<pair<string, int>> _success;

public:
	workStatus();
	~workStatus();

	HRESULT init();
	void update();
	void render();
	void release();
	void setInfo(string name, string person, int salary, int plus, int age, int stress, int weight);
	void setVector(vector<pair<string, pair<int, int>>> property, vector<pair<string, int>> success, int frameX);

	int getFrameIndex() { return _frameX; }
	int getAge() { return _age; }
	string getName() { return _name; }
	int getSalary() { return _salary; }
	int getStress() { return _stress; }

	vector<pair<string, pair<int, int>>> getProperty() { return _property; }
	vector<pair<string, int>> getSuccess() { return _success; }
};

