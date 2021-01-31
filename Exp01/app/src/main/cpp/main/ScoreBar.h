#ifndef _SCOREBAR_H_
#define _SCOREBAR_H_

#include "Utility.h"
#include "TimerCpp.h"

class ScoreBar {

protected:
	Vec2 pos, center;
	int width, height, gSize;
	bool waitFlg;
	int waitCnt, waitInterval;
	unsigned int black;

public:
	static ScoreBar *create(float x, float y, int w, int h);

	ScoreBar(float x, float y, int w, int h);

	virtual ~ScoreBar();

	bool init();

	bool offsetAdHeight();

	void update(const float delay);
};

#endif // _SCOREBAR_H_