#include "BoardGrid.h"

BoardGrid *BoardGrid::createBoard(float x, float y, int fS, int wS) {
	// New
	BoardGrid *board = new BoardGrid(x, y);
	if (board && board->init(fS, wS)) return board;
	DX_SAFE_DELETE(board);
	return nullptr;
}

BoardGrid::BoardGrid(float x, float y) :
		center(Vec2(x, y)), start(Vec2(0, 0)),
		floorSize(0), wallSize(0), gRows(0), gCols(0),
		index(0), bWidth(0), bHeight(0),
		startR(-1), startC(-1), goalR(-1), goalC(-1),
		cBlack(GetColor(0, 0, 0)),
		cWhite(GetColor(255, 255, 255)),
		cRed(GetColor(225, 65, 100)),
		cGreen(GetColor(110, 140, 50)),
		cBlue(GetColor(75, 60, 155)) {
	LOGD("Main", "BoardGrid()\n");
}

BoardGrid::~BoardGrid() {
	LOGD("Main", "~BoardGrid()\n");
}

bool BoardGrid::init(int fS, int wS) {
	floorSize = fS;
	wallSize = wS;
	this->loadBoard();// Load
	this->createMaze();// Maze
	this->detectRoute(1, 1, 3, 3);
	return true;
}

void BoardGrid::loadBoard() {

	// Clear
	for (auto line:board) line.clear();
	board.clear();

	// JSON
	const string fullPath = UtilJNI::getInstance()->getFilePath() + "index.json";
	const json jObj = UtilJson::getInstance()->loadJson(fullPath.c_str());
	const json maze = jObj["mazes"].at(index);
	gRows = maze["rows"].get<int>();
	gCols = maze["cols"].get<int>();
	bWidth = (floorSize + wallSize) * (gCols / 2);
	bWidth += (gCols % 2 == 0) ? 0 : wallSize;
	bHeight = (floorSize + wallSize) * (gRows / 2);
	bHeight += (gRows % 2 == 2) ? 0 : wallSize;
	start.x = center.x - bWidth / 2;
	start.y = center.y - bHeight / 2;

	int oY = start.y;
	for (int r = 0; r < gRows; r++) {
		int oX = start.x;// Reset
		const int h = (r % 2 == 0) ? wallSize : floorSize;
		vector<Grid> line = {};
		for (int c = 0; c < gCols; c++) {
			const int w = (c % 2 == 0) ? wallSize : floorSize;
			const int i = c + gCols * r;
			Grid grid{};
			grid.type = static_cast<Type>(maze["board"].at(i).get<int>());
			grid.r = r;
			grid.c = c;
			grid.minX = oX;
			grid.maxX = oX + w;
			grid.minY = oY;
			grid.maxY = oY + h;
			grid.pos.x = oX + w / 2;
			grid.pos.y = oY + h / 2;
			line.push_back(grid);
			oX += w;
		}
		board.push_back(line);
		oY += h;
	}
}

void BoardGrid::createMaze() {

	// Pillars
	for (int r = 0; r < gRows; r++) {
		for (int c = 0; c < gCols; c++) {
			Grid &grid = board[r][c];
			if (grid.type == PILLAR) pillars.push_back(grid);
		}
	}

	for (auto &pillar : pillars) {
		if (board[pillar.r][pillar.c].type == WALL) continue;
		vector<Grid> path = {pillar};
		const int d = UtilMath::getInstance()->getRandom(0, 3);
		this->extendPath(pillar, path, d);

		for (int i = 0; i < path.size() - 1; i++) {
			Grid &from = path.at(i);
			board[from.r][from.c].type = WALL;
			Grid &to = path.at(i + 1);
			board[to.r][to.c].type = WALL;
			int mR = from.r + (to.r - from.r) / 2;
			int mC = from.c + (to.c - from.c) / 2;
			board[mR][mC].type = WALL;
		}
	}
}

void BoardGrid::extendPath(Grid &pillar, vector<Grid> &path, int d) {
	const Dir dir = static_cast<Dir>(d);
	int oR = 0;
	int oC = 0;
	if (dir == LEFT) oC = -2;
	if (dir == RIGHT) oC = 2;
	if (dir == UP) oR = -2;
	if (dir == DOWN) oR = 2;
	if (this->checkDeadend(pillar, path, oR, oC)) return;

	const int n = UtilMath::getInstance()->getRandom(0, 3);
	if (this->checkPath(pillar, path, oR, oC)) {// Retry
		this->extendPath(pillar, path, n);
		return;
	} else {
		Grid &next = board[pillar.r + oR][pillar.c + oC];// Next
		path.push_back(next);
		this->extendPath(next, path, n);
	}
}

bool BoardGrid::checkDeadend(Grid &pillar, vector<Grid> &path, int oR, int oC) {

	const int r = pillar.r + oR;
	const int c = pillar.c + oC;
	if (board[r][c].type == WALL) {
		path.push_back(board[r][c]);
		return true;
	}
	return false;
}

bool BoardGrid::checkPath(Grid &pillar, vector<Grid> &path, int oR, int oC) {

	const int r = pillar.r + oR;
	const int c = pillar.c + oC;
	for (auto p : path) if (p.r == r && p.c == c) return true;
	return false;
}

void BoardGrid::update(const float delay) {

	for (int r = 0; r < gRows; r++) {
		for (int c = 0; c < gCols; c++) {
			Grid &grid = board[r][c];
			if (grid.type == FLOOR) continue;
			DrawBox(grid.minX, grid.minY,
					grid.maxX, grid.maxY,
					cWhite, true);
		}
	}
}

Vec2 &BoardGrid::getPos(int r, int c) {
	if (r < 0 || c < 0) return board[0][0].pos;
	if (gRows <= r || gCols <= c) return board[gRows - 1][gCols - 1].pos;
	return board[r][c].pos;
}

Vec2 &BoardGrid::getRdmPos() {
	const int rdmR = UtilMath::getInstance()->getRandom(0, (gRows - 2) / 2);
	const int rdmC = UtilMath::getInstance()->getRandom(0, (gCols - 2) / 2);
	const int r = rdmR * 2 + 1;
	const int c = rdmC * 2 + 1;
	return getPos(r, c);
}

void BoardGrid::detectRoute(int sR, int sC, int gR, int gC) {

	startR = sR;
	startC = sC;
	goalR = gR;
	goalC = gC;
	if (startR < 0 || gRows <= startR) return;
	if (startC < 0 || gCols <= startC) return;
	if (goalR < 0 || gRows <= goalR) return;
	if (goalC < 0 || gCols <= goalC) return;

	int cost = 0;
	int hue = abs(goalR - startR) + abs(goalC - startC);
	int score = hue;

	map<int, Node> nodes;
	// Start
	const int kStart = startR * gCols + startC;
	Node nStart = {startR, startC, -1, -1, cost, hue, score};
	nodes.insert(make_pair(kStart, nStart));

	// 4 directions
	this->stepRoute(nodes, 0, startR, startC, 0, -1);
	this->stepRoute(nodes, 0, startR, startC, 0, 1);
	this->stepRoute(nodes, 0, startR, startC, -1, 0);
	this->stepRoute(nodes, 0, startR, startC, 1, 0);

	for (auto node : nodes) {
		LOGD("Maze", "Route[%d]: %d, %d <- %d, %d",
			 node.first, node.second.r, node.second.c,
			 node.second.pR, node.second.pC);
	}

	// Check
	auto kPair = nodes.find(goalR * gCols + goalC);
	int kPrev = kPair->second.pR * gCols + kPair->second.pC;
	while (kPrev != kStart) {
		kPair = nodes.find(kPrev);
		LOGD("Maze", "Backward: %d, %d", kPair->second.r, kPair->second.c);
		kPrev = kPair->second.pR * gCols + kPair->second.pC;
	}
}

void BoardGrid::stepRoute(map<int, Node> &nodes, int cost,
						  int cR, int cC, int oR, int oC) {
	const int r = cR + oR;
	const int c = cC + oC;
	if (r < 0 || c < 0 || gRows <= r || gCols <= c) return;
	if (board[r][c].type != FLOOR) return;

	const int key = r * gCols + c;
	if (nodes.count(key)) return;// 探索済

	const int kGoal = goalR * gCols + goalC;
	if (nodes.count(kGoal)) {
		LOGD("Maze", "Goal: %d, %d", r, c);
		return;
	}

	const int hue = abs(goalR - r) + abs(goalC - c);
	const int score = cost + hue;
	Node next = {r, c, cR, cC, cost + 1, hue, score};
	nodes.insert(make_pair(key, next));
	LOGD("Maze", "[%d] %d, %d <- %d, %d", key, r, c, cR, cC);

	// TODO: A*っぽく優先順位をつける

	// 4 directions
	this->stepRoute(nodes, cost + 1, r, c, 0, -1);
	this->stepRoute(nodes, cost + 1, r, c, 0, 1);
	this->stepRoute(nodes, cost + 1, r, c, -1, 0);
	this->stepRoute(nodes, cost + 1, r, c, 1, 0);
}