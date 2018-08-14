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
	tagGod god;				//���ڸ�����
	int hp;					//ü��
	int physical;			//�ٷ�
	int intelligence;		//����
	int elegance;			//��ǰ
	int sexual;				//����(�ŷ�)
	int morality;			//������
	int faith;				//�ž�
	int sensitivity;		//������
	int warrior;			//������
	int warriorSkill;		//�������
	int power;				//���ݷ�
	int defPower;			//����
	int magic;				//������
	int magicSkill;			//�������
	int spell;				//����
	int spellDefence;		//�׸���
	int sociality;			//�米��
	int manner;				//���ǹ���
	int art;				//����
	int conversation;		//ȭ��
	int housework;			//������
	int cooking;			//�丮
	int cleaning;			//û�Ҽ�Ź
	int personality;		//��ǰ
	int karma;				//����
	int stress;				//��Ʈ����
	int withFather;			//�ƺ����� ����
	int total;				//����
	string plusNorth;		//����
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

struct tagDate
{
	int idx;
	string name;
	string firstName;
	int year;
	int mon;
	int day;
	int dayOfWeek; //�� : 0 ~ �� : 6
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
	float weight;	//����
};

enum DIALOG_TYPE { DIALOG_ING, DIALOG_FIN };
enum STATUS_TYPE {STATUS_START, STATUS_TEACH, STATUS_ING, STATUS_FIN };
enum SEASON_TYPE { SPRING, SUMMER, AUTUMN, WINTER };
enum DAYOFWEEK { MON, TUE, WED, THU, FRI, SAT, SUN };
enum ITEM_TYPE { ITEM_WEAPON, ITEM_ARMOR, ITEM_CLOTHES, ITEM_COOK, ITEM_GOODS };
#endif