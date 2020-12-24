#ifndef _BTNBASE_H_
#define _BTNBASE_H_

#include "Utility.h"

class BtnBase {

protected:
	Vec2 pos;
	int graphs[3];
	int width, height, scale;
	int minX, maxX, minY, maxY;
	int touchID;

public:
	static BtnBase *createSprite(const string &fileName, float x, float y,
	                             int xNum, int yNum);

	BtnBase(float x, float y);

	virtual ~BtnBase();

	bool init(const char *fileName, int xNum, int yNum);

	void setPosition(float x, float y);

	void setScale(int scale);

	bool containsPoint(int x, int y);

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void update(const float delay);
};

#endif // _BTNBASE_H_