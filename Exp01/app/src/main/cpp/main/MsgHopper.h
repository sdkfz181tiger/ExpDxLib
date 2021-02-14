#ifndef _MSGHOPPER_H_
#define _MSGHOPPER_H_

#include "Utility.h"

class MsgHopper {

private:
	Vec2 pos;
	int scale;
	float vY;
	int waitCnt, waitInterval;
	float groundY, gravityY;
	string msg;

public:
	static MsgHopper *createNum(float x, float y, int s, int n);

	static MsgHopper *createStr(float x, float y, int s, const string &m);

	MsgHopper(float x, float y, int s);

	virtual ~MsgHopper();

	bool init(int n);

	bool init(const string &m);

	void update(const float delay);

	bool isWaiting();
};

#endif // _MSGHOPPER_H_