#ifndef _UTILSOUND_H_
#define _UTILSOUND_H_

#include "Utility.h"

class UtilSound {

private:
	map<string, int> soundSEs;
	map<string, int> soundBGMs;

public:
	UtilSound();

	~UtilSound();

	static UtilSound *getInstance();

	void destroyInstance();

	bool init();

	void playSE(const string &fileName);

	void playBGM(const string &fileName);

	void stopBGM();
};

#endif // _UTILSOUND_H_