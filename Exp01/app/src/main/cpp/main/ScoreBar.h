#ifndef _SCOREBAR_H_
#define _SCOREBAR_H_

#include "Utility.h"
#include "BtnBase.h"
#include "TimerCpp.h"

class ScoreBar {

protected:
	Vec2 pos, center;
	int width, height, gSize;
	int waitCnt, waitInterval;
	int offsetY;
	unsigned int black;

private:
	vector<BtnBase *> btns;

public:
	static ScoreBar *create(float x, float y, int w, int h);

	ScoreBar(float x, float y, int w, int h);

	virtual ~ScoreBar();

	bool init();

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void pushBtnBase(BtnBase *btn);

	void offsetAdHeight();

	void update(const float delay);
};

#endif // _SCOREBAR_H_