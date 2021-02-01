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
	unsigned int black;

private:
	vector<BtnBase *> btns;

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

	void update(const float delay);
};

#endif // _STATUSBAR_H_