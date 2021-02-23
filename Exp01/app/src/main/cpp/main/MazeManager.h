#ifndef _MAZEMANAGER_H_
#define _MAZEMANAGER_H_

#include "Utility.h"

struct MazeRoute {
	int cR, cC, pR, pC, x, y;
};

class MazeManager {

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

protected:
	Vec2 center, min, max;
	int floorSize, wallSize, gRows, gCols;
	int index, bWidth, bHeight;
	int startR, startC, goalR, goalC;
	unsigned int cBlack, cWhite, cRed, cGreen, cBlue;

private:
	vector<vector<Grid>> board;
	vector<Grid> pillars;

public:
	static MazeManager *createBoard(float x, float y, int fS, int wS);

	MazeManager(float x, float y);

	virtual ~MazeManager();

	bool init(int fS, int wS);

	void loadMaze();

	void createMaze();

	void extendPath(Grid &pillar, vector<Grid> &path);

	bool checkDeadend(Grid &pillar, vector<Grid> &path, int oR, int oC);

	bool checkPathClosed(Grid &pillar, vector<Grid> &path);

	bool checkPathOwn(Grid &pillar, vector<Grid> &path, int oR, int oC);

	void update(const float delay);

	Vec2 &getPos(int r, int c);

	Vec2 &getRdmPos();

	vector<Vec2> detectRouteByRdm(int sX, int sY);

	vector<Vec2> detectRouteByPos(int sX, int sY, int gX, int gY);

	vector<Vec2> detectRouteByRC(int sR, int sC, int gR, int gC);

	void stepRoute(unordered_map<int, MazeRoute> &nodes,
				   int r, int c, int oR, int oC);
};

#endif // _MAZEMANAGER_H_