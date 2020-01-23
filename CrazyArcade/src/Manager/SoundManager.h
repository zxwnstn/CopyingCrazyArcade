#pragma once
#include "fmod.hpp"
#include "Etc/stdafx.h"

//define your sound game channel
enum class Channel {
	bgm,
	object,
	character,
	effects
};

class SoundManager
{
public:
	void init();
	void addSound(string str, const string& fileName, bool loop = false);
	void addStream(string str, const string& fileName, bool loop = false);
	void playSound(string str, int channel);
	void playSound(string str, Channel channel);

	void release();
	void pauseChannel(int channel);
	void resumeChannel(int channel);
	void stopChannel(int channel);
	void update();

private:
	FMOD::System* fmodSystem;
	FMOD::Channel* ch[40];
	FMOD_RESULT ret;
	void* extradireverdate = nullptr;

private:
	map<string, FMOD::Sound*> soundMap;

private:
	DECLARE_SINGLE(SoundManager)
};


