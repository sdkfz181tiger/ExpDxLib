#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Utility.h"
#include "SceneTitle.h"

class GameManager {

private:
	const int dWidth, dHeight, cDepth;
	bool quitFlg;

	vector<bool> touchFlgs;
	vector<Vec2> touchPositions;
	vector<SceneBase *> scenes;

public:
	GameManager(int dWidth, int dHeight, int cDepth);

	~GameManager();

	void init();

	bool getQuitFlg();

	void setQuitFlg(bool flg);

	void touchInput();

	void update(const float delay);
};

#endif // _GAMEMANAGER_H_