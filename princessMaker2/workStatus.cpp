#include "stdafx.h"
#include "workStatus.h"


workStatus::workStatus()
{
}


workStatus::~workStatus()
{
}

HRESULT workStatus::init()
{
	return S_OK;
}

void workStatus::update()
{
}

void workStatus::render()
{
}

void workStatus::release()
{
}

void workStatus::setInfo(string name, string person, int salary, int plus, int age, int stress, int weight)
{
	_name = name;
	_person = person;
	_salary = salary;
	_plusSalary = plus;
	_age = age;
	_stress = stress;
	_weight = weight;
}

void workStatus::setVector(vector<pair<string, pair <int, int>>> property, vector<pair<string, int>> success, int frameX)
{
	_property = property;
	_success = success;
	_frameX = frameX;
}

