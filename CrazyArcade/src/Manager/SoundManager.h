#pragma once
#include "fmod.hpp"
#include "Etc/stdafx.h"

class SoundManager
{
public:
	void init();
	void addSound(string str, const string& fileName, int mode = 1);
	void addStream(string str, const string& fileName, int mode = 1);
	void playSound(string str, int channel);

	void release();
	void pauseChannel(int channel);
	void resumeChannel(int channel);
	void update();

private:
	FMOD::System* fmodSystem;
	FMOD::Channel* ch[32];
	void* extradireverdate = nullptr;
	FMOD_RESULT ret;

private:
	map<string, FMOD::Sound*> soundMap;

private:
	DECLARE_SINGLE(SoundManager)
};

