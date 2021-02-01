#ifndef _SCOREHOPPER_H_
#define _SCOREHOPPER_H_

#include "Utility.h"

class ScoreHopper {

private:
	Vec2 pos, vel;
	int num;
	int waitCnt, waitInterval;
	float groundY, gravityY;
	char str[8];

public:
	static ScoreHopper *createHopper(float x, float y, int n);

	ScoreHopper(float x, float y, int n);

	virtual ~ScoreHopper();

	bool init();

	void update(const float delay);

	bool isWaiting();
};

#endif // _SCOREHOPPER_H_