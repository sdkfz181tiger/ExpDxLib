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
	if (selfUtilSound) return selfUtilSound;
	selfUtilSound = new UtilSound();
	if (selfUtilSound && selfUtilSound->init()) return selfUtilSound;
	DX_SAFE_DELETE(selfUtilSound);
	return nullptr;
}

void UtilSound::destroyInstance() {
	if (!selfUtilSound) return;

	delete (selfUtilSound);
	selfUtilSound = nullptr;
}

bool UtilSound::init() {
	LOGD("Util", "UtilSound::init()\n");

	vector<string> fileSEs = {
			"sounds/jing_title.wav",
			"sounds/jing_result_ng.wav",
			"sounds/jing_result_ok.wav",
			"sounds/se_coin_01.wav",
			"sounds/se_coin_02.wav",
			"sounds/se_coin_03.wav"
	};

	vector<string> fileBGMs = {
			"sounds/bgm_game.wav"
	};

	auto itS = fileSEs.end();
	while (itS-- != fileSEs.begin()) {
		const string &fileName = static_cast<string>(*itS);
		int handle = LoadSoundMem(fileName.c_str());
		if (handle < 0) continue;
		soundSEs.insert(make_pair(fileName, handle));
	}

	auto itB = fileBGMs.end();
	while (itB-- != fileBGMs.begin()) {
		const string &fileName = static_cast<string>(*itB);
		int handle = LoadSoundMem(fileName.c_str());
		if (handle < 0) continue;
		soundBGMs.insert(make_pair(fileName, handle));
	}

	return true;
}

void UtilSound::playSE(const string &fileName) {
	if (!soundSEs.count(fileName)) return;
	auto sound = soundSEs.find(fileName);
	if (CheckSoundMem(sound->second)) StopSoundMem(sound->second);
	PlaySoundMem(sound->second, DX_SOUNDTYPE_STREAMSTYLE, true);
}

void UtilSound::playBGM(const string &fileName) {
	if (!soundBGMs.count(fileName)) return;
	auto sound = soundBGMs.find(fileName);
	if (CheckSoundMem(sound->second)) StopSoundMem(sound->second);
	PlaySoundMem(sound->second, DX_PLAYTYPE_LOOP, true);
}

void UtilSound::stopBGM() {
	for (pair<string, int> sound : soundBGMs) StopSoundMem(sound.second);
}