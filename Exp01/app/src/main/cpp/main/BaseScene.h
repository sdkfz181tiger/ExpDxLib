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

	void draw(float delay);
};

#endif // _BASESCENE_H_