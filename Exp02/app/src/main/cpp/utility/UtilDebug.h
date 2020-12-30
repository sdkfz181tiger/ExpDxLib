#ifndef _UTILDEBUG_H_
#define _UTILDEBUG_H_

#include "Utility.h"

class UtilDebug {

private:
	int dispWidth, dispHeight, dispColor;
	int gridSize, gridRows, gridCols;
	unsigned int gridColor;
	char fpsStr[20];

public:
	UtilDebug();

	~UtilDebug();

	static UtilDebug *getInstance();

	void destroyInstance();

	bool init();

	void drawGrid();

	void drawFPS(float delay);
};

#endif // _UTILDEBUG_H_