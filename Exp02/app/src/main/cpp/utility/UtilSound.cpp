#include "UtilSound.h"

// Singleton Object
static UtilSound *selfUtilSound = nullptr;

UtilSound::UtilSound() : muteFlg(false) {
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

	// Mute
	muteFlg = UtilLocalSave::getInstance()->getBool("mute_flg");

	vector<string> fileSEs = {
			"sounds/se_coin_01.wav",
			"sounds/se_coin_02.wav",
			"sounds/se_coin_03.wav"
	};

	vector<string> fileBGMs = {
			"sounds/bgm_game.wav",
			"sounds/bgm_result_ng.wav",
			"sounds/bgm_result_ok.wav",
			"sounds/bgm_title.wav",
			"sounds/bgm_walk_01.wav",
			"sounds/bgm_walk_02.wav"
	};

	auto itS = fileSEs.end();
	while (itS-- != fileSEs.begin()) {
		const string &fileName = static_cast<string>(*itS);
		int handle = LoadSoundMem(this->getLocalPath(fileName).c_str());
		if (handle < 0) continue;
		soundSEs.insert(make_pair(fileName, handle));
	}

	auto itB = fileBGMs.end();
	while (itB-- != fileBGMs.begin()) {
		const string &fileName = static_cast<string>(*itB);
		int handle = LoadSoundMem(this->getLocalPath(fileName).c_str());
		if (handle < 0) continue;
		soundBGMs.insert(make_pair(fileName, handle));
	}

	return true;
}

string UtilSound::getLocalPath(const string &fileName) {
	return UtilJNI::getInstance()->getFilePath() + fileName;
}

void UtilSound::toggleMute() {
	muteFlg = !muteFlg;
	UtilLocalSave::getInstance()->setBool("mute_flg", muteFlg);
	if (muteFlg) this->stopAllSounds();
}

bool UtilSound::isMute() const {
	return muteFlg;
}

void UtilSound::playSE(const string &fileName) {
	if (muteFlg) return;
	if (!soundSEs.count(fileName)) return;
	auto sound = soundSEs.find(fileName);
	if (CheckSoundMem(sound->second)) StopSoundMem(sound->second);
	PlaySoundMem(sound->second, DX_SOUNDTYPE_STREAMSTYLE, true);
}

void UtilSound::stopSE() {
	for (pair<string, int> sound : soundSEs) StopSoundMem(sound.second);
}

void UtilSound::playBGM(const string &fileName, bool loop, bool top) {
	if (muteFlg) return;
	if (!soundBGMs.count(fileName)) return;
	auto sound = soundBGMs.find(fileName);
	if (CheckSoundMem(sound->second)) StopSoundMem(sound->second);
	if (loop) {
		PlaySoundMem(sound->second, DX_PLAYTYPE_LOOP, top);
	} else {
		PlaySoundMem(sound->second, DX_SOUNDTYPE_STREAMSTYLE, top);
	}
}

void UtilSound::stopBGM() {
	for (pair<string, int> sound : soundBGMs) StopSoundMem(sound.second);
}

void UtilSound::stopAllSounds() {
	this->stopSE();
	this->stopBGM();
}