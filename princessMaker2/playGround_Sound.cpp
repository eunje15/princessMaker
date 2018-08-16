#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::sound_add()
{
	SOUNDMANAGER->addSound("prologue0", "sound/prologue0.mp3", true, true);
	SOUNDMANAGER->addSound("prologue1", "sound/prologue1.mp3", true, true);
	SOUNDMANAGER->addSound("prologue2", "sound/prologue2.mp3", true, true);
	SOUNDMANAGER->addSound("spring", "sound/spring.mp3", true, true);
	SOUNDMANAGER->addSound("summer", "sound/summer.mp3", true, true);
	SOUNDMANAGER->addSound("autumn", "sound/autumn.mp3", true, true);
	SOUNDMANAGER->addSound("winter", "sound/winter.mp3", true, true);
	SOUNDMANAGER->addSound("study", "sound/study.mp3", true, true);
	SOUNDMANAGER->addSound("arbeit", "sound/arbeit.mp3", true, true);
	SOUNDMANAGER->addSound("free", "sound/free.mp3", true, true);
	SOUNDMANAGER->addSound("mountain", "sound/mountain.mp3", true, true);
	SOUNDMANAGER->addSound("beach", "sound/beach.mp3", true, true);
	SOUNDMANAGER->addSound("town", "sound/town.mp3", true, true);
	SOUNDMANAGER->addSound("castle", "sound/castle.mp3", true, true);

	return S_OK;
}