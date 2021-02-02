#ifndef _BOARDGRID_H_
#define _BOARDGRID_H_

#include "Utility.h"

class BoardGrid {

protected:
	Vec2 center;
	int gSize, gRows, gCols;
	int minX, maxX, minY, maxY;
	unsigned int cBlack, cWhite, cRed, cGreen, cBlue;

private:
	vector<Vec2> positions;

public:
	static BoardGrid *createBoard(float x, float y,
								  int size, int rows, int cols);

	BoardGrid(float x, float y);

	virtual ~BoardGrid();

	bool init(int size, int rows, int cols);

	void update(const float delay);

	Vec2 &getPos(int r, int c);

	Vec2 &getRdmPos();
};

#endif // _BOARDGRID_H_