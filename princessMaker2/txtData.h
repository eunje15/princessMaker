#pragma once
#include "singletonBase.h"
#include <vector>

class txtData : public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT init();
	void release();

	//����
	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//�ε�
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	vector<string> txtDataLoadSlash(const char * loadFileName);
	vector<string> charArraySlashSeparation(char charArray[]);

	vector<string> txtLoadCsv(const char * loadFileName);
	vector<string> charArraySeparationCsv(char charArray[]);

	vector<string> txtLoadCsv(const char * loadFileName, const char* constellation);
	vector<string> charArraySeparationCsv(char charArray[], const char* constellation);
};

