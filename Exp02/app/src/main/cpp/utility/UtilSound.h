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

	string getLocalPath(const string &fileName);

	void toggleMute();

	bool isMute() const;

	void playSE(const string &fileName);

	void stopSE();

	void playBGM(const string &fileName, bool loop, bool top);

	void stopBGM();

	void stopAllSounds();
};

#endif // _UTILSOUND_H_