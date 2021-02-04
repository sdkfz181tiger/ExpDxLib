#ifndef _STATUSBAR_H_
#define _STATUSBAR_H_

#include "Utility.h"
#include "BtnBase.h"
#include "TimerCpp.h"

class StatusBar {

protected:
	Vec2 pos, center;
	int width, height, gSize;
	int waitCnt, waitInterval;
	int offsetY;

private:
	vector<BtnBase *> btns;
	int score, high;
	char scoreStr[10], highStr[10];
	unsigned int black;

public:
	static StatusBar *create(float x, float y, int w, int h);

	StatusBar(float x, float y, int w, int h);

	virtual ~StatusBar();

	bool init();

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void pushBtnBase(BtnBase *btn);

	void offsetAdHeight();

	void resetScore();

	void addScore(int num);

	void update(const float delay);
};

#endif // _STATUSBAR_H_