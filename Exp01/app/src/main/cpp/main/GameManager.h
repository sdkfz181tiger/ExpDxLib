#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Utility.h"

class GameManager {

private:
	const int dWidth, dHeight, cDepth;
	bool quitFlg;

public:
	GameManager(int dWidth, int dHeight, int cDepth);

	~GameManager();

	void init();

	int getDispWidth();

	int getDispHeight();

	bool getQuitFlg();

	void setQuitFlg(bool quitFlg);

	void draw(float delay);
};

#endif // _GAMEMANAGER_H_