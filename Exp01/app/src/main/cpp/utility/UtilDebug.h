#ifndef _UTILDEBUG_H_
#define _UTILDEBUG_H_

#include "Utility.h"

class UtilDebug {

private:

	int dispWidth, dispHeight, dispColor;
	unsigned int gridSize, gridRows, gridCols, gridColor;
	unsigned int fpsWidth, fpsHeight, fpsColor, delayCnt;

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