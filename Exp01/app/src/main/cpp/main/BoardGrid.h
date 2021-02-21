#ifndef _BOARDGRID_H_
#define _BOARDGRID_H_

#include "Utility.h"

class BoardGrid {

public:
	enum Type {
		FLOOR, WALL, PILLAR
	};

	enum Dir {
		LEFT, RIGHT, UP, DOWN
	};

	struct Grid {
		Type type;
		int r, c;
		int minX, maxX;
		int minY, maxY;
		Vec2 pos;
	};

	struct Node {
		int r, c, pR, pC;
		int cost, hue, score;
	};

protected:
	Vec2 center, start;
	int floorSize, wallSize, gRows, gCols;
	int index, bWidth, bHeight;
	int startR, startC, goalR, goalC;
	unsigned int cBlack, cWhite, cRed, cGreen, cBlue;

private:
	vector<vector<Grid>> board;
	vector<Grid> pillars;

public:
	static BoardGrid *createBoard(float x, float y, int fS, int wS);

	BoardGrid(float x, float y);

	virtual ~BoardGrid();

	bool init(int fS, int wS);

	void loadBoard();

	void createMaze();

	void extendPath(Grid &pillar, vector<Grid> &path, int d);

	bool checkDeadend(Grid &pillar, vector<Grid> &path, int oR, int oC);

	bool checkPath(Grid &pillar, vector<Grid> &path, int oR, int oC);

	void update(const float delay);

	Vec2 &getPos(int r, int c);

	Vec2 &getRdmPos();

	void detectRoute(int sR, int sC, int gR, int gC);

	void stepRoute(unordered_map<int, Node> &nodes, int cost,
				   int r, int c, int oR, int oC);
};

#endif // _BOARDGRID_H_