#ifndef _UTILDEBUG_H_
#define _UTILDEBUG_H_

#include "Utility.h"

class UtilDebug {

private:
	int dWidth, dHeight, dColor;
	int gSize, gRows, gCols;
	unsigned int gColor;
	char fpsStr[20];

public:
	UtilDebug();

	~UtilDebug();

	static UtilDebug *getInstance();

	void destroyInstance();

	bool init();

	int getGridSize() { return gSize; }

	int getGridRows() { return gRows; }

	int getGridCols() { return gCols; }

	void drawGrid();

	void drawFPS(float delay);
};

#endif // _UTILDEBUG_H_