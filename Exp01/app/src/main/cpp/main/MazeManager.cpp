#include "MazeManager.h"

MazeManager *MazeManager::createBoard(float x, float y, int fS, int wS) {
	// New
	MazeManager *board = new MazeManager(x, y);
	if (board && board->init(fS, wS)) return board;
	DX_SAFE_DELETE(board);
	return nullptr;
}

MazeManager::MazeManager(float x, float y) :
		center(Vec2(x, y)), min(Vec2(0, 0)), max(Vec2(0, 0)),
		floorSize(0), wallSize(0), gRows(0), gCols(0),
		index(0), bWidth(0), bHeight(0),
		startR(-1), startC(-1), goalR(-1), goalC(-1),
		cBlack(GetColor(0, 0, 0)),
		cWhite(GetColor(255, 255, 255)),
		cRed(GetColor(225, 65, 100)),
		cGreen(GetColor(110, 140, 50)),
		cBlue(GetColor(75, 60, 155)) {
	LOGD("Main", "MazeManager()\n");
}

MazeManager::~MazeManager() {
	LOGD("Main", "~MazeManager()\n");
}

bool MazeManager::init(int fS, int wS) {
	floorSize = fS;
	wallSize = wS;
	this->loadMaze();// Load
	this->createMaze();// Maze
	return true;
}

void MazeManager::loadMaze() {
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
	min.x = center.x - bWidth / 2;
	min.y = center.y - bHeight / 2;
	max.x = min.x + bWidth;
	max.y = min.y + bHeight;

	int oY = min.y;
	for (int r = 0; r < gRows; r++) {
		int oX = min.x;// Reset
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

void MazeManager::createMaze() {
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
		this->extendPath(pillar, path);

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

void MazeManager::extendPath(Grid &pillar, vector<Grid> &path) {
	const int dir = UtilMath::getInstance()->getRandom(0, 3);
	int oR = 0;
	int oC = 0;
	if (dir == LEFT) oC = -2;
	if (dir == RIGHT) oC = 2;
	if (dir == UP) oR = -2;
	if (dir == DOWN) oR = 2;
	if (this->checkDeadend(pillar, path, oR, oC)) return;
	if (this->checkPathClosed(pillar, path)) return;
	if (this->checkPathOwn(pillar, path, oR, oC)) {// Retry
		this->extendPath(pillar, path);
		return;
	} else {
		Grid &next = board[pillar.r + oR][pillar.c + oC];// Next
		path.push_back(next);
		this->extendPath(next, path);
	}
}

bool MazeManager::checkDeadend(Grid &pillar, vector<Grid> &path, int oR, int oC) {
	const int r = pillar.r + oR;
	const int c = pillar.c + oC;
	if (board[r][c].type == WALL) {
		path.push_back(board[r][c]);
		return true;
	}
	return false;
}

bool MazeManager::checkPathClosed(Grid &pillar, vector<Grid> &path) {
	return (this->checkPathOwn(pillar, path, 0, -2) &&
			this->checkPathOwn(pillar, path, 0, 2) &&
			this->checkPathOwn(pillar, path, -2, 0) &&
			this->checkPathOwn(pillar, path, 2, 0));
}

bool MazeManager::checkPathOwn(Grid &pillar, vector<Grid> &path, int oR, int oC) {
	const int r = pillar.r + oR;
	const int c = pillar.c + oC;
	for (auto p : path) if (p.r == r && p.c == c) return true;
	return false;
}

void MazeManager::update(const float delay) {

	DrawBox(min.x, min.y, max.x, max.y, cGreen, true);

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

Vec2 &MazeManager::getPos(int r, int c) {
	if (r < 0 || c < 0) return board[0][0].pos;
	if (gRows <= r || gCols <= c) return board[gRows - 1][gCols - 1].pos;
	return board[r][c].pos;
}

Vec2 &MazeManager::getRdmPos() {
	const int rdmR = UtilMath::getInstance()->getRandom(0, (gRows - 2) / 2);
	const int rdmC = UtilMath::getInstance()->getRandom(0, (gCols - 2) / 2);
	const int r = rdmR * 2 + 1;
	const int c = rdmC * 2 + 1;
	return getPos(r, c);
}

vector<Vec2> MazeManager::detectRouteByRdm(int sX, int sY) {
	const int gX = UtilMath::getInstance()->getRandom(min.x, max.x);
	const int gY = UtilMath::getInstance()->getRandom(min.y, max.y);
	return this->detectRouteByPos(sX, sY, gX, gY);
}

vector<Vec2> MazeManager::detectRouteByPos(int sX, int sY, int gX, int gY) {
	// Start
	int sR = 0;
	if (sY < min.y) {
		sR = 1;
	} else if (max.y < sY) {
		sR = gRows - 2;
	} else {
		for (int r = 1; r < gRows; r += 2) {
			if (sY < board[r][0].maxY) {
				sR = r;
				break;
			}
		}
	}
	int sC = 0;
	if (sX < min.x) {
		sC = 1;
	} else if (max.x < sX) {
		sC = gCols - 2;
	} else {
		for (int c = 1; c < gCols; c += 2) {
			if (sX < board[0][c].maxX) {
				sC = c;
				break;
			}
		}
	}
	// Goal
	int gR = 0;
	if (gY < min.y) {
		gR = 1;
	} else if (max.y < gY) {
		gR = gRows - 2;
	} else {
		for (int r = 1; r < gRows; r += 2) {
			if (gY < board[r][0].maxY) {
				gR = r;
				break;
			}
		}
	}
	int gC = 0;
	if (gX < min.x) {
		gC = 1;
	} else if (max.x < gX) {
		gC = gCols - 2;
	} else {
		for (int c = 1; c < gCols; c += 2) {
			if (gX < board[0][c].maxX) {
				gC = c;
				break;
			}
		}
	}
	return this->detectRouteByRC(sR, sC, gR, gC);
}

vector<Vec2> MazeManager::detectRouteByRC(int sR, int sC, int gR, int gC) {

	vector<Vec2> routes;
	if (sR == gR && sC == gC) return routes;

	startR = sR;
	startC = sC;
	goalR = gR;
	goalC = gC;
	if (startR < 0 || gRows <= startR) return routes;
	if (startC < 0 || gCols <= startC) return routes;
	if (goalR < 0 || gRows <= goalR) return routes;
	if (goalC < 0 || gCols <= goalC) return routes;

	// Start
	const int kStart = startR * gCols + startC;
	const Vec2 &pStart = board[startR][startC].pos;

	// Nodes
	unordered_map<int, MazeNode> nodes;
	this->insertRout(nodes, startR, startC, 0, 0, 0);// Center
	this->insertRout(nodes, startR, startC, 0, -1, 1);
	this->insertRout(nodes, startR, startC, 0, 1, 1);
	this->insertRout(nodes, startR, startC, 1, 0, 1);
	this->insertRout(nodes, startR, startC, -1, 0, 1);
	this->stepRoute(nodes, startR, startC, 0);// Step

	// Routes
	auto kPair = nodes.find(goalR * gCols + goalC);// Goal
	int kPrev = kPair->second.pR * gCols + kPair->second.pC;
	routes.emplace_back(kPair->second.x, kPair->second.y);
	while (kPrev != kStart) {
		kPair = nodes.find(kPrev);
		kPrev = kPair->second.pR * gCols + kPair->second.pC;
		routes.emplace_back(kPair->second.x, kPair->second.y);
	}
	routes.push_back(pStart);// Start
	return routes;
}

void MazeManager::stepRoute(unordered_map<int, MazeNode> &nodes,
							int cR, int cC, int cost) {
	const int r = cR;
	const int c = cC;
	if (r < 0 || c < 0 || gRows <= r || gCols <= c) return;

	// Already goaled
	const int kGoal = goalR * gCols + goalC;
	if (nodes.count(kGoal)) return;

	// Already exist
	const int key = r * gCols + c;
	if (nodes.count(key) <= 0) return;

	// Already closed
	auto node = nodes.find(key);
	if (node->second.closed) return;
	node->second.closed = true;// Close

	// Insert 4 directions
	this->insertRout(nodes, r, c, 0, -1, cost + 1);
	this->insertRout(nodes, r, c, 0, 1, cost + 1);
	this->insertRout(nodes, r, c, 1, 0, cost + 1);
	this->insertRout(nodes, r, c, -1, 0, cost + 1);

	// Recursive
	int score = 9999;
	int kRec = -1;
	for (auto node : nodes) {
		if (node.second.closed) continue;
		if (score < node.second.score) continue;
		score = node.second.score;
		kRec = node.first;
	}
	if (kRec < 0) return;
	auto nRec = nodes.find(kRec);
	this->stepRoute(nodes, nRec->second.cR, nRec->second.cC, nRec->second.cost);
}

void MazeManager::insertRout(unordered_map<int, MazeNode> &nodes,
							 int cR, int cC, int oR, int oC, int cost) {
	const int r = cR + oR;
	const int c = cC + oC;
	if (r < 0 || c < 0 || gRows <= r || gCols <= c) return;

	if (board[r][c].type != FLOOR) return;// Floor

	const int key = r * gCols + c;
	const int x = board[r][c].pos.x;
	const int y = board[r][c].pos.y;
	const int hue = abs(goalR - r) + abs(goalC - c);
	const int score = cost + 1 + hue;
	MazeNode node = {r, c, cR, cC, x, y, cost + 1, hue, score, false};
	nodes.insert(make_pair(key, node));
}