#pragma once
#include"Header.h"
#include"fmod.hpp"
#include"fmod_errors.h"
#pragma comment(lib, "fmodex_vc.lib")
using namespace FMOD;

enum SOUNDINDEX
{
	SND_BGM, SND_BGM2
};

class SoundManager
{
public:
	System*		pEngine;
	Sound*		pSound[10];
	Channel*		pChannel[10];
	FMOD_RESULT	r;

	void init();
	void loading();
	void play(int _type);
	void stop(int _ch);
	void errorCheck(FMOD_RESULT _r);
};