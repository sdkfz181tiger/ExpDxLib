#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Utility.h"

class GameManager {

private:
	const int dWidth, dHeight, cDepth;
	bool quitFlg;
	vector<bool> touchFlgs;
	vector<Vec2> touchPositions;

public:
	GameManager(int dWidth, int dHeight, int cDepth);

	~GameManager();

	void init();

	int getDispWidth();

	int getDispHeight();

	bool getQuitFlg();

	void touchInput();

	void update(const float delay);
};

#endif // _GAMEMANAGER_H_