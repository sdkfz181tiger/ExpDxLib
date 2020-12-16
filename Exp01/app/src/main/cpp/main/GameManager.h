#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Utility.h"

class GameManager {

private:
	const int dWidth, dHeight, cDepth;

public:
	GameManager(int dWidth, int dHeight, int cDepth);

	~GameManager();

	void init();

	int getDispWidth();

	int getDispHeight();
};

#endif // _GAMEMANAGER_H_