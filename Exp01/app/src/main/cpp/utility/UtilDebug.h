#ifndef _UTILDEBUG_H_
#define _UTILDEBUG_H_

#include "Utility.h"

class UtilDebug {

private:

	int dWidth, dHeight, dColor;
	int gSize, gRows, gCols, gColor;
	int fWidth, fHeight, fColor;
	int sSize, sColor, pCnt;

public:
	UtilDebug();

	~UtilDebug();

	static UtilDebug *getInstance();

	void destroyInstance();

	bool init();

	void drawGrid();

	void drawFPS();
};

#endif // _UTILDEBUG_H_