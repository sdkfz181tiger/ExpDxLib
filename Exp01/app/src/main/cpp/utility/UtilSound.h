#ifndef _UTILSOUND_H_
#define _UTILSOUND_H_

#include "Utility.h"

class UtilSound {

private:
	map<string, int> sounds;

public:
	UtilSound();

	~UtilSound();

	static UtilSound *getInstance();

	void destroyInstance();

	bool init();

	void playSE(const string &fileName);

	void playBGM(const string &fileName);
};

#endif // _UTILSOUND_H_