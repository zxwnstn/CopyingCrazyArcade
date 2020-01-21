#include "SoundManager.h"
DEFINITION_SINGLE(SoundManager)

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::init() {
	ret = FMOD::System_Create(&fmodSystem);
	ret = fmodSystem->init(32, FMOD_INIT_NORMAL, extradireverdate);
}

void SoundManager::addSound(string str, const string & fileName, int mode) {
	auto findIter = soundMap.find(str);
	if (findIter != soundMap.end())
		return;

	FMOD::Sound* sound;
	if (mode == 0)
		ret = fmodSystem->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	else {
		ret = fmodSystem->createSound(fileName.c_str(), FMOD_LOOP_OFF, 0, &sound);
	}
	soundMap.insert(make_pair(str, sound));
}

void SoundManager::addStream(string str, const string & fileName, int mode)
{
	auto findIter = soundMap.find(str);
	if (findIter != soundMap.end())
		return;
	FMOD::Sound* sound;

	if (mode == 0)
		ret = fmodSystem->createStream(fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	else {
		ret = fmodSystem->createStream(fileName.c_str(), FMOD_LOOP_OFF, 0, &sound);
	}
	soundMap.insert(make_pair(str, sound));
}


void SoundManager::playSound(string str, int channel) {
	auto findIter = soundMap.find(str);
	if (findIter == soundMap.end()) {
		return;
	}
	fmodSystem->playSound(findIter->second, 0, false, &ch[channel]);
}

void SoundManager::release() {
	fmodSystem->release();
	fmodSystem->close();
}

void SoundManager::pauseChannel(int channel) {
	ch[channel]->setPaused(true);
}

void SoundManager::resumeChannel(int channel) {
	ch[channel]->setPaused(false);
}

void SoundManager::stopChannel(int channel)
{
	ch[channel]->stop();
}

void SoundManager::update()
{
	ch[0]->setVolume(0.2f);
	fmodSystem->update();
}
