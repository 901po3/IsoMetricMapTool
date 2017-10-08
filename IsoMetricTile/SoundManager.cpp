#include"SoundManager.h"

void SoundManager::init()
{
	r = System_Create(&pEngine);
	errorCheck(r);

	r = pEngine->init(0, FMOD_INIT_NORMAL, NULL);
	errorCheck(r);
}

void SoundManager::loading()
{

	r = pEngine->createSound("bgm2.mp3", FMOD_LOOP_NORMAL, NULL, &pSound[SND_BGM]);
	errorCheck(r);
	r = pEngine->createSound("bgm1.mp3", FMOD_LOOP_NORMAL, NULL, &pSound[SND_BGM2]);
	errorCheck(r);
}

void SoundManager::play(int _type)
{
	pEngine->update();
	pEngine->playSound(FMOD_CHANNEL_FREE, pSound[_type], false, &pChannel[_type]);
}

void SoundManager::stop(int _ch)
{
	pChannel[_ch]->stop();
}

void SoundManager::errorCheck(FMOD_RESULT _r)
{
	if(_r != FMOD_OK)
	{
		TCHAR szStr[512] = {0};
		const char* errorMessage = FMOD_ErrorString(_r);
		MultiByteToWideChar(CP_ACP, NULL, errorMessage, 1, szStr,512);
		MessageBox(NULL, szStr, L"FMOD error", MB_OK);
	}
}
