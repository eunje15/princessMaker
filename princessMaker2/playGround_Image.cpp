#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::image_init()
{
	//==================프롤로그=======================
	IMAGEMANAGER->addImage("dadName", "image/prologue/dadName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dadOK", "image/prologue/아빠완료(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("princessName", "image/prologue/princessName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("princessOK", "image/prologue/딸완료(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));

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
	

	//==========메인이미지===============
	IMAGEMANAGER->addImage("back", "image/main/main(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flower", "image/main/flower2(850x225,5x1).bmp", 850,255,5,1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mainFrame", "image/main/액자(720x130,6x1).bmp", 720,130,6,1,false, RGB(255, 0, 255));
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


	//=======스테이터스이미지==============
	IMAGEMANAGER->addImage("info1Back", "image/main/infoBack(260x184).bmp", 260, 184, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info2Back", "image/main/info2Back(250x186).bmp", 250, 186, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info3Back", "image/main/info3Back(240x119).bmp", 240, 119, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info3Back2", "image/main/info3Back(270x119).bmp", 270, 119, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info4Back", "image/main/info4Back(260x110).bmp", 260, 110, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status1Back", "image/main/status1Back(240x220).bmp", 240, 220, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status2Back", "image/main/status2Back(240x140).bmp", 240, 140, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status3Back", "image/main/status3Back(240x100).bmp", 240, 100, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status4Back", "image/main/status4Back(240x140).bmp", 240, 140, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressBack", "image/main/progressBack(110x20).bmp", 110, 20, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progressFront", "image/main/progressFront(98x10).bmp", 98, 10, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progress1Back", "image/main/statusSmallBack(240x40).bmp", 240, 40, false, RGB(255, 0, 255));


	//==========다이얼로그이미지==============
	IMAGEMANAGER->addImage("1Back", "image/main/1Back(170x64).bmp", 170, 64, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3Back", "image/main/dadTalkBack(170x112).bmp", 170, 112, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4Back", "image/main/4Back(170x136).bmp", 170, 136, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2Back", "image/main/2Back(140x88).bmp", 140, 88, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("answer", "image/main/answer(310x76).bmp", 310, 76, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wideBack", "image/main/wideBack(390x124).bmp", 390, 124, false, RGB(255, 0, 255));


	//===============상점이미지===============
	IMAGEMANAGER->addImage("storeFrame", "image/main/frame2(290x181).bmp", 290, 181, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("storePicture", "image/main/townPicture(252x163).bmp", 252, 163, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("storeIcon", "image/main/storeIcon(240x40,6x1).bmp", 240, 40, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("storeQuit", "image/main/storeQuit(240x40,2x1).bmp", 240, 40, 2, 1, true, RGB(255, 0, 255));

	//===========공주이미지==============
	IMAGEMANAGER->addFrameImage("princessFace", "image/princess/딸얼굴(1464x922,12x7).bmp", 1464, 922, 12, 7, true, RGB(255, 0, 255));
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


	//===============NPC이미지====================
	IMAGEMANAGER->addFrameImage("cube", "image/npc/cube(840x260,7x2).bmp", 840, 260, 7, 2, true, RGB(255, 0, 255));

	//===============아이템이미지=====================
	IMAGEMANAGER->addFrameImage("weapon", "image/item/weapon(600x40,15x1).bmp", 600, 40, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("itemDialog", "image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("clothes", "image/item/clothes(400x40,10x1).bmp", 400, 40, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cook", "image/item/cook(120x40,3x1).bmp", 120, 40, 3, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("goods", "image/item/goods(240x40,6x1).bmp", 240, 40, 6, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("statusImg", "image/main/statusImage(120x40,3x1).bmp", 120, 40, 3, 1, false, RGB(255, 0, 255));

	//===============성이미지=======================
	IMAGEMANAGER->addImage("castlePicture", "image/main/castlePicture(252x163).bmp", 252, 163, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smallDay", "image/main/smallDay2(20x620,1x31).bmp", 20, 620, 1, 31, true, RGB(255, 0, 255));

	//===============스케줄이미지===================
	IMAGEMANAGER->addFrameImage("teachImg", "image/schedule/teachImg(400x40,x10x1).bmp", 400, 40, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("workImg", "image/schedule/workImg(600x40,15x1).bmp", 600, 40, 15, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fightImg", "image/schedule/fightImg(160x40,4x1).bmp", 160, 40, 4, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("relaxImg", "image/schedule/relaxImg(80x40,2x1).bmp", 80, 40, 2, 1, false, RGB(255, 0, 255));



	//================교육이미지========================
	IMAGEMANAGER->addImage("교육액자", "image/education/교육액자(420x180).bmp", 420, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("교육선생", "image/education/teachers(1200x130,10x1).bmp", 1200, 130, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goldBack", "image/education/goldBack(200x44).bmp", 200, 44, false, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("자연과학배경", "image/education/자연과학배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("자연과학친구1", "image/education/자연과학친구1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("자연과학친구2", "image/education/자연과학친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("자연과학공주", "image/education/자연과학공주(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("자연과학선생", "image/education/자연과학선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));

	IMAGEMANAGER->addImage("시문배경", "image/education/시문배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("시문친구1", "image/education/시문친구1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("시문친구2", "image/education/시문친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("시문공주", "image/education/시문공주(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("시문선생", "image/education/시문선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));

	IMAGEMANAGER->addImage("신학배경", "image/education/신학배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("신학친구3", "image/education/신학친구1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("신학친구2", "image/education/신학친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("신학친구1", "image/education/신학친구3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("신학공주", "image/education/신학공주(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("신학선생", "image/education/신학선생(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("군사학배경", "image/education/군사학배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("군사학친구1", "image/education/군사학친구1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("군사학친구2", "image/education/군사학친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("군사학공주", "image/education/군사학공주(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("군사학선생", "image/education/군사학선생(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("검술배경", "image/education/검술배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("검술친구3", "image/education/검술친구1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("검술친구2", "image/education/검술친구2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("검술친구1", "image/education/검술친구3(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("검술공주", "image/education/검술공주(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("검술선생", "image/education/검술선생(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("격투술배경", "image/education/격투술배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("격투술친구1", "image/education/격투술친구1(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("격투술친구2", "image/education/격투술친구2(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("격투술공주", "image/education/격투술공주(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("격투술선생", "image/education/격투술선생(50x100).bmp", 50, 100, 1, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addImage("격투술막대기", "image/education/격투술막대기(50x100).bmp", 50, 100, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("격투술횃불", "image/education/격투술횃불(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("마법배경", "image/education/마법배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("마법친구1", "image/education/마법친구1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("마법공주", "image/education/마법공주(700x100,14x1).bmp", 700, 100, 14, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("마법선생", "image/education/마법선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("마법횃불2", "image/education/해골횃불1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("마법횃불1", "image/education/해골횃불2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("예법배경", "image/education/예법배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("예법친구1", "image/education/예법친구1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("예법친구2", "image/education/예법친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("예법친구3", "image/education/예법친구3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("예법공주", "image/education/예법공주(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("예법선생", "image/education/예법선생(250x70,5x1).bmp", 250, 70, 5, 1, true, RGB(0, 203, 0));


	IMAGEMANAGER->addImage("무용배경", "image/education/발레배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("무용친구1", "image/education/발레친구1(196x99,4x1).bmp", 196, 99, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("무용친구2", "image/education/발레친구2(196x99,4x1).bmp", 196, 99, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("무용공주", "image/education/발레공주(392x99,8x1).bmp", 392, 99, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("무용선생", "image/education/발레선생(98x99,2x1).bmp", 98, 99, 2, 1, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("미술배경", "image/education/미술배경(400x160).bmp", 400, 160, false, RGB(0, 203, 0));
	IMAGEMANAGER->addFrameImage("미술친구1", "image/education/미술친구1(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("미술친구2", "image/education/미술친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("미술공주", "image/education/미술공주(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(1, 202, 0));
	IMAGEMANAGER->addFrameImage("미술선생", "image/education/미술선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 0));

	
	//=====================아르바이트 이미지========================
	IMAGEMANAGER->addImage("알바액자", "image/education/교육액자(420x180).bmp", 420, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("알바선생", "image/work/알바선생(1800x130,15x1).bmp", 1800, 130, 15, 1, false, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("집안일배경", "image/work/집안일배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("집안일공주", "image/work/집안일공주(500x101,10x1).bmp", 500, 101, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("집안일선생", "image/work/집안일선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보모배경", "image/work/보모배경(400x160).bmp", 400, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보모공주", "image/work/보모공주(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보모친구1", "image/work/보모친구(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보모선생", "image/work/보모선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("여관배경", "image/work/여관배경(400x160).bmp", 400, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("여관공주", "image/work/여관공주(550x100,11x1).bmp", 550, 100, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("여관선생", "image/work/여관선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("여관닭", "image/work/여관닭(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("여관이불", "image/work/여관이불2(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("농장배경", "image/work/농장배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("농장공주", "image/work/농장공주(600x100,12x1).bmp", 600, 100, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("농장선생", "image/work/농장선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("농장오리", "image/work/농장오리(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("농장풍차1", "image/work/농장풍차1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("농장풍차2", "image/work/농장풍차2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("말머리", "image/work/말머리(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("말궁둥이", "image/work/말궁둥이(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("성당배경", "image/work/성당배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("성당공주", "image/work/성당공주(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("성당선생", "image/work/성당선생(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addImage("성당책상", "image/work/성당책상(150x100).bmp", 150, 100, true, RGB(0, 204, 0));


	IMAGEMANAGER->addImage("레스토랑배경", "image/work/레스토랑배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("레스토랑공주", "image/work/레스토랑공주(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("레스토랑선생", "image/work/레스토랑선생(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("레스토랑친구1", "image/work/레스토랑친구1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("레스토랑친구2", "image/work/레스토랑친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("레스토랑친구3", "image/work/레스토랑친구3(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("레스토랑불", "image/work/레스토랑불(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("나무꾼배경", "image/work/나무꾼배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무꾼공주", "image/work/나무꾼공주(650x100,13x1).bmp", 650, 100, 13, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("나무꾼선생", "image/work/나무꾼선생(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(67, 203, 237));
	IMAGEMANAGER->addFrameImage("나무꾼친구1", "image/work/나무꾼친구1(300x100,2x1).bmp", 300, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("나무꾼친구2", "image/work/나무꾼친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addImage("나무꾼풀", "image/work/나무꾼풀(400x52).bmp", 400, 52, true, RGB(255, 0, 0));

	IMAGEMANAGER->addImage("미용실배경", "image/work/미용실배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미용실공주", "image/work/미용실공주(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미용실선생", "image/work/미용실선생(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미용실친구1", "image/work/미용실친구1(200x200,4x2).bmp", 200, 200, 4, 2, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미용실친구2", "image/work/미용실친구2(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미용실친구3", "image/work/미용실친구3(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addImage("미용실친구3팔", "image/work/미용실친구3팔(50x100).bmp", 50, 100, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("미장이배경", "image/work/미장이배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("미장이공주", "image/work/미장이공주(450x100,9x1).bmp", 450, 100, 9, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미장이선생", "image/work/미장이선생(450x70,9x1).bmp", 450, 70, 9, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미장이친구1", "image/work/미장이친구1(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("미장이강아지", "image/work/미장이강아지(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("사냥꾼배경", "image/work/사냥꾼배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사냥꾼공주", "image/work/사냥꾼공주(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 207, 0));
	IMAGEMANAGER->addFrameImage("사냥꾼선생", "image/work/사냥꾼선생(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 207, 0));
	IMAGEMANAGER->addFrameImage("사냥꾼토끼", "image/work/사냥꾼토끼(250x100,5x1).bmp", 250, 100, 5, 1, true, RGB(0, 207, 0));
	IMAGEMANAGER->addImage("사냥꾼풀", "image/work/사냥꾼풀(400x52).bmp", 400, 52, true, RGB(255, 255, 255));

	IMAGEMANAGER->addImage("묘지기배경", "image/work/묘지기배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("묘지기공주", "image/work/묘지기공주(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("묘지기선생", "image/work/묘지기선생(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("묘지기불", "image/work/묘지기불(100x45,2x1).bmp", 100, 45, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("가정교사배경", "image/work/가정교사배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("가정교사공주", "image/work/가정교사공주(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("가정교사선생", "image/work/가정교사선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("가정교사친구", "image/work/가정교사친구1(350x100,7x1).bmp", 350, 100, 7, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("주점배경", "image/work/주점배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("주점공주", "image/work/주점공주(1000x75,20x1).bmp", 1000, 75, 20, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점선생", "image/work/주점선생(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점친구1", "image/work/주점친구1(200x75,4x1).bmp", 200, 75, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점친구2", "image/work/주점친구2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점친구3", "image/work/주점친구3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("주점배경", "image/work/주점배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("주점공주", "image/work/주점공주(1000x75,20x1).bmp", 1000, 75, 20, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점선생", "image/work/주점선생(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점친구1", "image/work/주점친구1(200x75,4x1).bmp", 200, 75, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점친구2", "image/work/주점친구2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("주점친구3", "image/work/주점친구3(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));

	IMAGEMANAGER->addImage("밤의주점배경", "image/work/밤의주점배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("밤의주점공주", "image/work/밤의주점공주(400x100,8x1).bmp", 400, 100, 8, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점선생", "image/work/밤의주점선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점친구5", "image/work/밤의주점친구1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점친구4", "image/work/밤의주점친구2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점친구3", "image/work/밤의주점친구3(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점친구2", "image/work/밤의주점친구4(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점친구1", "image/work/밤의주점친구5(300x100,6x1).bmp", 300, 100, 6, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점친구6", "image/work/밤의주점친구6(150x100,3x1).bmp", 150, 100, 3, 1, true, RGB(1, 202, 1));
	IMAGEMANAGER->addFrameImage("밤의주점촛불", "image/work/밤의주점촛불(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(1, 202, 1));

	IMAGEMANAGER->addImage("밤의전당배경", "image/work/밤의전당배경(400x160).bmp", 400, 160, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("밤의전당공주", "image/work/밤의전당공주(500x100,10x1).bmp", 500, 100, 10, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("밤의전당선생", "image/work/밤의전당선생(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("밤의전당친구1", "image/work/밤의전당친구1(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("밤의전당친구2", "image/work/밤의전당친구2(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("밤의전당친구3", "image/work/밤의전당친구3(200x100,4x1).bmp", 200, 100, 4, 1, true, RGB(0, 204, 0));
	IMAGEMANAGER->addFrameImage("밤의전당친구4", "image/work/밤의전당친구4(100x100,2x1).bmp", 100, 100, 2, 1, true, RGB(0, 204, 0));
	

	//==========================맵이미지=====================================
	IMAGEMANAGER->addFrameImage("map", "image/field/e_map(640x3360,16x84).bmp", 640, 3360, 16, 84, true, RGB(255, 0, 255));
	

	//======================무사수행이미지===================================
	IMAGEMANAGER->addFrameImage("조작키", "image/field/조작키(200x80,5x2).bmp", 200, 80, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무사수행정보", "image/field/무사수행정보(180x170).bmp", 180, 170, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fieldMap", "image/field/FieldMap(1600x600,2x1).bmp", 1600, 600, 2, 1, false, RGB(255, 0, 255));

	//======================바캉스이미지====================================
	IMAGEMANAGER->addImage("black", "image/main/black(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("자유행동사진", "image/vacation/자유행동사진(252x163).bmp", 252, 163, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("산사진", "image/vacation/산사진(3200x1424,4x4).bmp", 3200, 1424, 4, 4, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("바다사진", "image/vacation/바다사진(3200x1424,4x4).bmp", 3200, 1424, 4, 4, false, RGB(255, 0, 255));

	return S_OK;
}