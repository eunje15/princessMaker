#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{

	return S_OK;
}

void txtData::release()
{

}

//저장
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char str[100000];

	strncpy_s(str, 100000, vectorArrayCombine(vStr), 99998);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 100000, &write, NULL);

	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	//버퍼는 우선 128로 잡아둡니다 
	//여러분이 버퍼갯수를 정해두지말고, 들어올때마다 크기에따라
	//문자열 동적할당을 하게끔 바꿔두면 편하게쬽?
	char str[100000] = "";
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 100000, vArray[i].c_str(), 99998);
		// vArray[0] vArray[1] vArray[2] vArray[3]
		// 20, 20, 30, 30
		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}

//로드
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[100000] = "";

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 100000, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}


vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = ",";
	char* token;

	token = strtok_s(charArray, separator, &temp);
	if (token != NULL)
		vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

vector<string> txtData::txtDataLoadSlash(const char* loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[100000] = "";

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 100000, &read, NULL);

	CloseHandle(file);

	return charArraySlashSeparation(str);
}


vector<string> txtData::charArraySlashSeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = "/";
	char* token;

	token = strtok_s(charArray, separator, &temp);
	if (token != NULL)
		vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	return vArray;
}


vector<string> txtData::txtLoadCsv(const char* loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[100000] = "";

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 100000, &read, NULL);

	CloseHandle(file);

	return charArraySeparationCsv(str);
}


vector<string> txtData::txtLoadCsv(const char* loadFileName, const char* constellation)
{
	HANDLE file;
	DWORD read;

	char str[100000] = "";

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 100000, &read, NULL);

	CloseHandle(file);

	return charArraySeparationCsv(str, constellation);
}

vector<string> txtData::charArraySeparationCsv(char charArray[])
{
	vector<string> vArray, vArray2;

	char* temp;
	const char* separator = "\r\n";
	char* token;

	token = strtok_s(charArray, separator, &temp);

	if (token != NULL)
	{
		//vArray = charArraySeparation(token);
		vArray.push_back(token);
	}

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		//vArray2 = charArraySeparation(token);
		//vArray.insert(vArray.end(), vArray2.begin(), vArray2.end());
		vArray.push_back(token);
	}

	return vArray;
}

vector<string> txtData::charArraySeparationCsv(char charArray[], const char* constellation)
{
	vector<string> vArray;

	char* temp;
	const char* separator = "\r\n";
	char* token;

	token = strtok_s(charArray, separator, &temp);

	if (token != NULL)
	{
		if (strstr(token, constellation) != NULL)
		{
			return charArraySeparation(token);
		}
	}

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		if (strstr(token, constellation) != NULL)
		{
			return charArraySeparation(token);
		}
	}

	return vArray;
}