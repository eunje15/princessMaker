#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::image_init()
{
	//==================���ѷα�=======================
	IMAGEMANAGER->addImage("dadName", "image/prologue/dadName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dadOK", "image/prologue/�ƺ��Ϸ�(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("princessName", "image/prologue/princessName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("princessOK", "image/prologue/���Ϸ�(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));

	IMAGEMANAGER->addImage("princessCal", "image/prologue/princessCal(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("princessYellow", "image/prologue/princessYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("dadAgeYellow", "image/prologue/dadAgeYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dadAge", "image/prologue/dadAge(800x600).bmp", 800, 600, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("dadCal", "image/prologue/dadCal2(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dadCalYellow", "image/prologue/dadCalYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("princessBlood", "image/prologue/princessBlood(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("princessBloodYellow", "image/prologue/princessBloodYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("prologue", "image/prologue/prologue(800x2000).bmp", 800, 2000, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("war", "image/prologue/prologue(800x6600,1x11).bmp", 800, 6600, 1, 11, false, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("godFace", "image/prologue/godFace(1200x130,10x1).bmp", 1200, 130, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("frame", "image/prologue/dialogFace(140x150).bmp", 140, 150, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("monFace", "image/prologue/monsterFace(1080x520,9x4).bmp", 1080, 520, 9, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dialogFrame", "image/prologue/dialogFrame(250,150).bmp", 250, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("peopleFace", "image/npc/peopleFace(2040x780,17x6).bmp", 2040, 780, 17, 6, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("princessMaker", "image/prologue/princessMaker(442x227).bmp", 442, 227, true, RGB(255, 0, 255), true);
	

	//==========�����̹���===============
	IMAGEMANAGER->addImage("back", "image/main/main(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flower", "image/main/flower2(850x225,5x1).bmp", 850,255,5,1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mainFrame", "image/main/����(720x130,6x1).bmp", 720,130,6,1,false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cal", "image/main/cal(179x100).bmp", 179, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("schedule", "image/main/scheduleCal(300x299).bmp", 300, 299, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status", "image/main/status(200x218).bmp", 200, 218, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("menu", "image/main/menu(400x120,2x1).bmp", 400, 120, 2, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectMenu", "image/main/selectMenu(200x120).bmp", 200, 120, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("year", "image/main/year(40x200,1x10).bmp", 40, 200, 1, 10, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("month", "image/main/month(60x240,1x12).bmp", 60, 240, 1, 12, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("day", "image/main/day(80x1550,1x31).bmp", 80, 1550, 1, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smallDay", "image/main/smallDay(20x620,1x31).bmp", 20, 620, 1, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("number", "image/main/number2(100x20,10x1).bmp", 100, 20, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dayOfWeek", "image/main/dayOfweek(60x140,1x7).bmp", 40, 140, 1, 7, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("constellation", "image/main/constellation(400x40,10x1).bmp", 400, 40, 10, 1, true, RGB(255, 0, 255));


	//=======�������ͽ��̹���==============
	IMAGEMANAGER->addImage("info1Back", "image/main/infoBack(260x184).bmp", 260, 184, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info2Back", "image/main/info2Back(250x186).bmp", 250, 186, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info3Back", "image/main/info3Back(240x119).bmp", 240, 119, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info4Back", "image/main/info4Back(260x110).bmp", 260, 110, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status1Back", "image/main/status1Back(240x220).bmp", 240, 220, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status2Back", "image/main/status2Back(240x140).bmp", 240, 140, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status3Back", "image/main/status3Back(240x100).bmp", 240, 100, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status4Back", "image/main/status4Back(240x140).bmp", 240, 140, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBack", "image/main/progressBack(110x20).bmp", 110, 20, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressFront", "image/main/progressFront(98x10).bmp", 98, 10, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progress1Back", "image/main/statusSmallBack(240x40).bmp", 240, 40, false, RGB(255, 0, 255));


	//==========���̾�α��̹���==============
	IMAGEMANAGER->addImage("1Back", "image/main/1Back(170x64).bmp", 170, 64, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3Back", "image/main/dadTalkBack(170x112).bmp", 170, 112, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4Back", "image/main/4Back(170x136).bmp", 170, 136, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2Back", "image/main/2Back(140x88).bmp", 140, 88, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("answer", "image/main/answer(310x76).bmp", 310, 76, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wideBack", "image/main/wideBack(390x124).bmp", 390, 124, false, RGB(255, 0, 255));


	//===============�����̹���===============
	IMAGEMANAGER->addImage("storeFrame", "image/main/frame2(290x181).bmp", 290, 181, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("storePicture", "image/main/townPicture(252x163).bmp", 252, 163, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("storeIcon", "image/main/storeIcon(240x40,6x1).bmp", 240, 40, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("storeQuit", "image/main/storeQuit(240x40,2x1).bmp", 240, 40, 2, 1, true, RGB(255, 0, 255));

	//===========�����̹���==============
	IMAGEMANAGER->addFrameImage("princessFace", "image/princess/����(1464x922,12x7).bmp", 1464, 922, 12, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face10", "image/princess/10_face(2040x1228,4x4).bmp", 2040, 1228, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body10", "image/princess/10_clothes(1020x1172,2x4).bmp", 1020, 1172, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face11", "image/princess/11_face(2550x1200,5x4).bmp", 2550, 1200, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body11", "image/princess/11_clothes2(1020x1200,2x4).bmp", 1020, 1200, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sunburn11", "image/princess/11_sunburn(1020x1336,2x4).bmp", 1020, 1336, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face12", "image/princess/12_face(3060x1052,6x4).bmp", 3060, 1052, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body12", "image/princess/12_clothes(1020x1336,2x4).bmp", 1020, 1336, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face13", "image/princess/13_face(2550x1422,5x6).bmp", 2550, 1422, 5, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body13", "image/princess/13_clothes(1020x2178,2x5).bmp", 1020, 2178, 2, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face14", "image/princess/14_face(2550x1616,5x8).bmp", 2550, 1616, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body14", "image/princess/14_clothes(1020x2388,2x6).bmp", 1020, 2388, 2, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face15", "image/princess/15_face(2550x1850,5x10).bmp", 2550, 1850, 5, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body15", "image/princess/15_clothes(510x4150,1x10).bmp", 510, 4150, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face16", "image/princess/16_face(2550x1630,5x10).bmp", 2550, 1630, 5, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body16", "image/princess/16_clothes(510x4370,1x10).bmp", 510, 4370, 1, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("face17", "image/princess/17_face(2550x1490,5x10).bmp", 2550, 1490, 5, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("body17", "image/princess/17_clothes(510x4510,1x10).bmp", 510, 4510, 1, 10, true, RGB(255, 0, 255));


	//===============NPC�̹���====================
	IMAGEMANAGER->addFrameImage("cube", "image/npc/cube(840x260,7x2).bmp", 840, 260, 7, 2, true, RGB(255, 0, 255));

	//===============�������̹���=====================
	IMAGEMANAGER->addFrameImage("weapon", "image/item/weapon(600x40,15x1).bmp", 600, 40, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("itemDialog", "image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("clothes", "image/item/clothes(400x40,10x1).bmp", 400, 40, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cook", "image/item/cook(120x40,3x1).bmp", 120, 40, 3, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goods", "image/item/goods(240x40,6x1).bmp", 240, 40, 6, 1, false, RGB(255, 0, 255));


	//===============���̹���=======================
	IMAGEMANAGER->addImage("castlePicture", "image/main/castlePicture(252x163).bmp", 252, 163, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smallDay", "image/main/smallDay2(20x620,1x31).bmp", 20, 620, 1, 31, true, RGB(255, 0, 255));

	//===============�������̹���===================
	IMAGEMANAGER->addFrameImage("teachImg", "image/schedule/teachImg(400x40,x10x1).bmp", 400, 40, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("workImg", "image/schedule/workImg(600x40,15x1).bmp", 600, 40, 15, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fightImg", "image/schedule/fightImg(160x40,4x1).bmp", 160, 40, 4, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("relaxImg", "image/schedule/relaxImg(80x40,2x1).bmp", 80, 40, 2, 1, false, RGB(255, 0, 255));



	//================�����̹���========================
	IMAGEMANAGER->addImage("��������", "image/education/��������(420x180).bmp", 420, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/education/teachers(1200x130,10x1).bmp", 1200, 130, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goldBack", "image/education/goldBack(200x44).bmp", 200, 44, false, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("�ڿ����й��", "image/education/�ڿ����й��(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�ڿ�����ģ��1", "image/education/�ڿ�����ģ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�ڿ�����ģ��2", "image/education/�ڿ�����ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�ڿ����а���", "image/education/�ڿ����а���(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�ڿ����м���", "image/education/�ڿ����м���(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));

	IMAGEMANAGER->addImage("�ù����", "image/education/�ù����(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�ù�ģ��1", "image/education/�ù�ģ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("�ù�ģ��2", "image/education/�ù�ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�ù�����", "image/education/�ù�����(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�ù�����", "image/education/�ù�����(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));

	IMAGEMANAGER->addImage("���й��", "image/education/���й��(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("����ģ��3", "image/education/����ģ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��2", "image/education/����ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/education/����ģ��3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("���а���", "image/education/���а���(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("���м���", "image/education/���м���(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�����й��", "image/education/�����й��(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("������ģ��1", "image/education/������ģ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("������ģ��2", "image/education/������ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����а���", "image/education/�����а���(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����м���", "image/education/�����м���(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�˼����", "image/education/�˼����(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�˼�ģ��3", "image/education/�˼�ģ��1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�˼�ģ��2", "image/education/�˼�ģ��2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�˼�ģ��1", "image/education/�˼�ģ��3(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�˼�����", "image/education/�˼�����(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�˼�����", "image/education/�˼�����(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("���������", "image/education/���������(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("������ģ��1", "image/education/������ģ��1(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("������ģ��2", "image/education/������ģ��2(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����������", "image/education/����������(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����������", "image/education/����������(50x100).bmp", 50, 100, 1, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addImage("�����������", "image/education/�����������(50x100).bmp", 50, 100, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("������ȶ��", "image/education/������ȶ��(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("�������", "image/education/�������(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/education/����ģ��1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������", "image/education/��������(700x100,14x1).bmp", 700, 100, 14, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������", "image/education/��������(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ȶ��2", "image/education/�ذ�ȶ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ȶ��1", "image/education/�ذ�ȶ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("�������", "image/education/�������(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/education/����ģ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("����ģ��2", "image/education/����ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("����ģ��3", "image/education/����ģ��3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("��������", "image/education/��������(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("��������", "image/education/��������(250x70,5x1).bmp", 250, 70, 5, 1, true, RGB(0, 203, 0));


	IMAGEMANAGER->addImage("������", "image/education/�߷����(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/education/�߷�ģ��1(196x99,4x1).bmp", 196, 99, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��2", "image/education/�߷�ģ��2(196x99,4x1).bmp", 196, 99, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������", "image/education/�߷�����(392x99,8x1).bmp", 392, 99, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("���뼱��", "image/education/�߷�����(98x99,2x1).bmp", 98, 99, 2, 1, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("�̼����", "image/education/�̼����(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("�̼�ģ��1", "image/education/�̼�ģ��1(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("�̼�ģ��2", "image/education/�̼�ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("�̼�����", "image/education/�̼�����(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("�̼�����", "image/education/�̼�����(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 0));

	
	//=====================�Ƹ�����Ʈ �̹���========================
	IMAGEMANAGER->addImage("�˹پ���", "image/education/��������(420x180).bmp", 420, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�˹ټ���", "image/work/�˹ټ���(1800x130,15x1).bmp", 1800, 130, 15, 1, false, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("�����Ϲ��", "image/work/�����Ϲ��(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ϰ���", "image/work/�����ϰ���(500x101,10x1).bmp", 500, 101, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ϼ���", "image/work/�����ϼ���(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������", "image/work/������(400x160).bmp", 400, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "image/work/�������(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/work/����ģ��(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���𼱻�", "image/work/���𼱻�(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�������", "image/work/�������(400x160).bmp", 400, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/work/��������(550x100,11x1).bmp", 550, 100, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/work/��������(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "image/work/������(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̺�", "image/work/�����̺�2(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("������", "image/work/������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "image/work/�������(600x100,12x1).bmp", 600, 100, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���弱��", "image/work/���弱��(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "image/work/�������(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ǳ��1", "image/work/����ǳ��1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ǳ��2", "image/work/����ǳ��2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ӹ�", "image/work/���Ӹ�(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���õ���", "image/work/���õ���(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������", "image/work/������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "image/work/�������(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("���缱��", "image/work/���缱��(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addImage("����å��", "image/work/����å��(150x100).bmp", 150, 100, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("����������", "image/work/����������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����������", "image/work/�����������(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����������", "image/work/�����������(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������ģ��1", "image/work/�������ģ��1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������ģ��2", "image/work/�������ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������ģ��3", "image/work/�������ģ��3(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("���������", "image/work/���������(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�����۹��", "image/work/�����۹��(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����۰���", "image/work/�����۰���(650x100,13x1).bmp", 650, 100, 13, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����ۼ���", "image/work/�����ۼ���(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(67, 203, 237));
	IMAGEMANAGER->addFrameImage("������ģ��1", "image/work/������ģ��1(300x100,2x1).bmp", 300, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("������ģ��2", "image/work/������ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addImage("������Ǯ", "image/work/������Ǯ(400x52).bmp", 400, 52, true, RGB(255, 0, 0));

	IMAGEMANAGER->addImage("�̿�ǹ��", "image/work/�̿�ǹ��(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�̿�ǰ���", "image/work/�̿�ǰ���(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�̿�Ǽ���", "image/work/�̿�Ǽ���(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�̿��ģ��1", "image/work/�̿��ģ��1(200x200,4x2).bmp", 200, 200, 4, 2, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�̿��ģ��2", "image/work/�̿��ģ��2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�̿��ģ��3", "image/work/�̿��ģ��3(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addImage("�̿��ģ��3��", "image/work/�̿��ģ��3��(50x100).bmp", 50, 100, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�����̹��", "image/work/�����̹��(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̰���", "image/work/�����̰���(450x100,9x1).bmp", 450, 100, 9, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����̼���", "image/work/�����̼���(450x70,9x1).bmp", 450, 70, 9, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("������ģ��1", "image/work/������ģ��1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����̰�����", "image/work/�����̰�����(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("��ɲ۹��", "image/work/��ɲ۹��(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ɲ۰���", "image/work/��ɲ۰���(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 207, 0));
	IMAGEMANAGER->addFrameImage("��ɲۼ���", "image/work/��ɲۼ���(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 207, 0));
	IMAGEMANAGER->addFrameImage("��ɲ��䳢", "image/work/��ɲ��䳢(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 207, 0));
	IMAGEMANAGER->addImage("��ɲ�Ǯ", "image/work/��ɲ�Ǯ(400x52).bmp", 400, 52, true, RGB(255, 255, 255));

	IMAGEMANAGER->addImage("��������", "image/work/��������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������", "image/work/���������(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�����⼱��", "image/work/�����⼱��(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������", "image/work/�������(100x45,2x1).bmp", 100, 45, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("����������", "image/work/����������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����������", "image/work/�����������(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������缱��", "image/work/�������缱��(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������ģ��", "image/work/��������ģ��1(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�������", "image/work/�������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/work/��������(1000x75,20x1).bmp", 1000, 75, 20, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������", "image/work/��������(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/work/����ģ��1(200x75,4x1).bmp", 200, 75, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��2", "image/work/����ģ��2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��3", "image/work/����ģ��3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�������", "image/work/�������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/work/��������(1000x75,20x1).bmp", 1000, 75, 20, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������", "image/work/��������(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��1", "image/work/����ģ��1(200x75,4x1).bmp", 200, 75, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��2", "image/work/����ģ��2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("����ģ��3", "image/work/����ģ��3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("�����������", "image/work/�����������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������������", "image/work/������������(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("������������", "image/work/������������(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("��������ģ��5", "image/work/��������ģ��1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("��������ģ��4", "image/work/��������ģ��2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("��������ģ��3", "image/work/��������ģ��3(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("��������ģ��2", "image/work/��������ģ��4(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("��������ģ��1", "image/work/��������ģ��5(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("��������ģ��6", "image/work/��������ģ��6(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("���������к�", "image/work/���������к�(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 1));

	IMAGEMANAGER->addImage("����������", "image/work/����������(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����������", "image/work/�����������(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("�������缱��", "image/work/�������缱��(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������ģ��1", "image/work/��������ģ��1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������ģ��2", "image/work/��������ģ��2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������ģ��3", "image/work/��������ģ��3(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("��������ģ��4", "image/work/��������ģ��4(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	

	//==========================���̹���=====================================
	IMAGEMANAGER->addFrameImage("map", "image/field/e_map(640x3360,16x84).bmp", 640, 3360, 16, 84, true, RGB(255, 0, 255));
	

	//======================��������̹���===================================
	IMAGEMANAGER->addFrameImage("����Ű", "image/field/����Ű(200x80,5x2).bmp", 200, 80, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����������", "image/field/�����������(180x170).bmp", 180, 170, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fieldMap", "image/field/FieldMap(1600x600,2x1).bmp", 1600, 600, 2, 1, false, RGB(255, 0, 255));

	//======================��Ĳ���̹���====================================
	IMAGEMANAGER->addImage("black", "image/main/black(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ൿ����", "image/vacation/�����ൿ����(252x163).bmp", 252, 163, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����", "image/vacation/�����(3200x1424,4x4).bmp", 3200, 1424, 4, 4, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٴٻ���", "image/vacation/�ٴٻ���(3200x1424,4x4).bmp", 3200, 1424, 4, 4, false, RGB(255, 0, 255));

	return S_OK;
}