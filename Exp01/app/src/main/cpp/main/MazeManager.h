#ifndef _MAZEMANAGER_H_
#define _MAZEMANAGER_H_

#include "Utility.h"

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

	struct Route {
		int r, c, pR, pC, x, y;
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

	vector<Route> detectRoute(int sR, int sC, int gR, int gC);

	void stepRoute(unordered_map<int, Route> &nodes, int cost,
				   int r, int c, int oR, int oC);
};

#endif // _MAZEMANAGER_H_