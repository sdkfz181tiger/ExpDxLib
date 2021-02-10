#ifndef _MSGHOPPER_H_
#define _MSGHOPPER_H_

#include "Utility.h"

class MsgHopper {

private:
	Vec2 pos, vel;
	int waitCnt, waitInterval;
	float groundY, gravityY;
	string str;

public:
	static MsgHopper *createNum(float x, float y, int n);

	static MsgHopper *createStr(float x, float y, const string &s);

	MsgHopper(float x, float y);

	virtual ~MsgHopper();

	bool init(int n);

	bool init(const string &s);

	void update(const float delay);

	bool isWaiting();
};

#endif // _MSGHOPPER_H_