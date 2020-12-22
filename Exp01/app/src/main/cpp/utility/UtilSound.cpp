#include "UtilSound.h"

// Singleton Object
static UtilSound *selfUtilSound = nullptr;

UtilSound::UtilSound() {
	LOGD("Util", "UtilSound()\n");
}

UtilSound::~UtilSound() {
	LOGD("Util", "~UtilSound()\n");
}

UtilSound *UtilSound::getInstance() {

	if (!selfUtilSound) {
		selfUtilSound = new UtilSound();
		if (selfUtilSound && selfUtilSound->init()) {
			return selfUtilSound;
		} else {
			delete (selfUtilSound);
			selfUtilSound = nullptr;
		}
	}
	return selfUtilSound;
}

void UtilSound::destroyInstance() {
	if (!selfUtilSound) return;

	delete (selfUtilSound);
	selfUtilSound = nullptr;
}

bool UtilSound::init() {
	LOGD("Util", "UtilSound::init()\n");

	vector<string> fileNames = {
			"se_coin_01.wav",
			"se_coin_02.wav",
			"se_coin_03.wav"
	};

	auto it = fileNames.end();
	while (it-- != fileNames.begin()) {
		const string &fileName = static_cast<string>(*it);
		const string path = "sounds/" + fileName;
		int handle = LoadSoundMem(path.c_str());
		if (handle < 0) continue;
		sounds.insert(make_pair(fileName, handle));
	}

	return true;
}

void UtilSound::playSE(const string &fileName) {
	if (!sounds.count(fileName)) return;
	auto sound = sounds.find(fileName);
	LOGD("Main", "playSE:%s, %d", sound->first.c_str(), sound->second);
	if (CheckSoundMem(sound->second)) StopSoundMem(sound->second);
	PlaySoundMem(sound->second, DX_PLAYTYPE_NORMAL, true);
}

void UtilSound::playBGM(const string &fileName) {
	if (!sounds.count(fileName)) return;
	auto sound = sounds.find(fileName);
	LOGD("Main", "playBGM:%s, %d", sound->first.c_str(), sound->second);
	if (CheckSoundMem(sound->second)) StopSoundMem(sound->second);
	PlaySoundMem(sound->second, DX_PLAYTYPE_LOOPBIT, true);
}