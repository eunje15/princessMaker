#pragma once

#ifndef _DATA_H_
#define _DATA_H_

#include "progressBar.h"

struct tagObj
{
	RECT rc;
	bool isData;
	int idX, idY;
	bool isSelected;
};

enum BLOOD_TYPE { BLOOD_A, BLOOD_B, BLOOD_O, BLOOD_AB };
struct tagInfo
{
	string firstName;
	string name;
	int year;
	int mon;
	int day;
	int age;
	int dayOfWeek;
	int gold;
	BLOOD_TYPE blood;
	string strBlood;
	string dietType;
};



struct tagGod
{
	string planet;
	string name;
	string constellation;
	int idx;
};

struct tagStatus
{
	tagGod god;				//별자리정보
	int hp;					//체력
	int physical;			//근력
	int intelligence;		//지능
	int elegance;			//기품
	int sexual;				//색기(매력)
	int morality;			//도덕심
	int faith;				//신앙
	int sensitivity;		//감수성
	int warrior;			//전사평가
	int warriorSkill;		//전투기술
	int power;				//공격력
	int defPower;			//방어력
	int magic;				//마법평가
	int magicSkill;			//마법기술
	int spell;				//마력
	int spellDefence;		//항마력
	int sociality;			//사교평가
	int manner;				//예의범절
	int art;				//예술
	int conversation;		//화술
	int housework;			//가사평가
	int cooking;			//요리
	int cleaning;			//청소세탁
	int personality;		//성품
	int karma;				//업보
	int stress;				//스트레스
	int withFather;			//아빠와의 관계
	int total;				//총합
	string plusNorth;		//무신
};

struct tagBody
{
	float height;
	float weight;
	float bast;
	float waist;
	float hip;
	int clothesType;
};



struct tagString
{
	string str;
	RECT rc;
	bool isSelected;
	bool isChoose;
};

struct tagImg
{
	image* img;
	int x, y;
	int frameX, frameY;
	tagString data;
};

struct tagProgress
{
	string str;
	int data;
	progressBar* progressBar;
	RECT strRc, dataRc;
};

struct tagProgressFloat
{
	string str;
	float data;
	progressBar* progressBar;
	RECT strRc, dataRc;
};

enum PRINCESS_TYPE { PRINCESS_NORMAL, PRINCESS_SICK, PRINCESS_DISOBEY, PRINCESS_LOVE, PRINCESS_OBESITY };
struct tagDate
{
	int idx;
	string name;
	string firstName;
	int year;
	int mon;
	int day;
	int dayOfWeek; //일 : 0 ~ 토 : 6
	PRINCESS_TYPE type;
};

struct tagStatusData
{
	string name;
	int startP;
	int endP;
	int plusStart;
	int plusEnd;
};

struct tagRelax
{
	int sensitivity;
	int stress;
	float weight;	//무게
};

enum DIALOG_TYPE { DIALOG_ING, DIALOG_FIN };
enum STATUS_TYPE {STATUS_START, STATUS_TEACH, STATUS_ING, STATUS_FIN };
enum SEASON_TYPE { SPRING, SUMMER, AUTUMN, WINTER };
enum DAYOFWEEK { MON, TUE, WED, THU, FRI, SAT, SUN };
enum ITEM_TYPE { ITEM_WEAPON, ITEM_ARMOR, ITEM_CLOTHES, ITEM_COOK, ITEM_GOODS };
#endif