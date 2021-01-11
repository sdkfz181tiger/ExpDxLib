#ifndef _BOARDGRID_H_
#define _BOARDGRID_H_

#include "Utility.h"

class BoardGrid {

protected:
	Vec2 pos;
	int gSize, gRows, gCols;
	unsigned int cWhite, cRed, cGreen, cBlue;

public:
	static BoardGrid *createBoard(float x, float y,
								  int size, int rows, int cols);

	BoardGrid(float x, float y);

	virtual ~BoardGrid();

	virtual bool init(int size, int rows, int cols);

	virtual void update(const float delay);

	virtual void draw();
};

#endif // _BOARDGRID_H_