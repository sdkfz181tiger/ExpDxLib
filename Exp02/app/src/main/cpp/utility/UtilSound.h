#ifndef _UTILSOUND_H_
#define _UTILSOUND_H_

#include "Utility.h"

class UtilSound {

private:
	bool muteFlg;
	map<string, int> soundSEs;
	map<string, int> soundBGMs;

public:
	UtilSound();

	~UtilSound();

	static UtilSound *getInstance();

	void destroyInstance();

	bool init();

	void toggleMute();

	bool isMute();

	void playSE(const string &fileName);

	void playBGM(const string &fileName, bool loop);

	void stopSE();

	void stopBGM();

	void stopAllSounds();
};

#endif // _UTILSOUND_H_