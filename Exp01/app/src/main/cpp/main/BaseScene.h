#ifndef _BASESCENE_H_
#define _BASESCENE_H_

#include "Utility.h"

class BaseScene {

private:
	const int dWidth, dHeight;

public:
	BaseScene(int dWidth, int dHeight);

	~BaseScene();

	void init();

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void draw(float delay);
};

#endif // _BASESCENE_H_