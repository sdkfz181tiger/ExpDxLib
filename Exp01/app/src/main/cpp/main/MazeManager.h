#ifndef _MAZEMANAGER_H_
#define _MAZEMANAGER_H_

#include "Utility.h"

enum MazeType {
	FLOOR, WALL, PILLAR
};

struct MazeGrid {
	MazeType type;
	int r, c;
	int minX, maxX;
	int minY, maxY;
	Vec2 pos;
};

struct MazeNode {
	int cR, cC, pR, pC;
	int x, y;
	int cost, hue, score;
	bool closed;
};

class MazeManager {

public:

	enum Dir {
		LEFT, RIGHT, UP, DOWN
	};

protected:
	Vec2 center, min, max;
	int floorSize, wallSize, gRows, gCols;
	int index, bWidth, bHeight;
	int startR, startC, goalR, goalC;
	unsigned int cBlack, cWhite, cRed, cGreen, cBlue;

private:
	vector<vector<MazeGrid>> board;
	vector<MazeGrid> pillars;

public:
	static MazeManager *createBoard(float x, float y, int fS, int wS);

	MazeManager(float x, float y);

	virtual ~MazeManager();

	bool init(int fS, int wS);

	void loadMaze();

	void createMaze();

	void extendPath(MazeGrid &pillar, vector<MazeGrid> &path);

	bool checkDeadend(MazeGrid &pillar, vector<MazeGrid> &path, int oR, int oC);

	bool checkPathClosed(MazeGrid &pillar, vector<MazeGrid> &path);

	bool checkPathOwn(MazeGrid &pillar, vector<MazeGrid> &path, int oR, int oC);

	void update(const float delay);

	int getMinX() const { return min.x; }

	int getMaxX() const { return max.x; }

	int getMinY() const { return min.y; }

	int getMaxY() const { return max.y; }

	int getRByY(int y);

	int getCByX(int x);

	bool isSameRCByPos(const Vec2 &posA, const Vec2 &posB);

	Vec2 &getPosByRC(int r, int c);

	Vec2 &getRdmPos();

	MazeGrid &getGridByRC(int r, int c);

	MazeGrid &getGridByPos(int x, int y);

	vector<Vec2> detectRouteByRdm(int sX, int sY);

	vector<Vec2> detectRouteByPos(int sX, int sY, int gX, int gY);

	vector<Vec2> detectRouteByRC(int sR, int sC, int gR, int gC);

	void stepRoute(unordered_map<int, MazeNode> &nodes,
				   int cR, int cC, int cost);

	void insertRout(unordered_map<int, MazeNode> &nodes,
					int cR, int cC, int oR, int oC, int cost);

	int getEyesightL(int x, int y, int cols);

	int getEyesightR(int x, int y, int cols);

	int getEyesightU(int x, int y, int rows);

	int getEyesightD(int x, int y, int rows);
};

#endif // _MAZEMANAGER_H_