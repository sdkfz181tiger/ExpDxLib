#include "SpriteMaze.h"

SpriteMaze *SpriteMaze::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteMaze *sprite = new SpriteMaze(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteMaze::SpriteMaze(float x, float y) : SpriteChara(x, y), mManager(nullptr) {
	//LOGD("Main", "SpriteMaze()\n");
}

SpriteMaze::~SpriteMaze() {
	//LOGD("Main", "~SpriteMaze()\n");
}

bool SpriteMaze::init(const string &fileName) {
	if (!SpriteChara::init(fileName)) return false;
	this->startIdle();// Idle
	return true;
}

void SpriteMaze::setMazeManager(MazeManager *mm) {
	// MazeManager
	if (mManager == nullptr) mManager = mm;
}

void SpriteMaze::showWays() {
	// Ways
	unsigned int cWhite = GetColor(255, 255, 255);
	for (auto way: ways) {
		const int x = way.x;
		const int y = way.y;
		DrawBox(x - 2, y - 2, x + 2, y + 2, cWhite, true);
	}
}

void SpriteMaze::startFollowRdm() {
	// MazeManager
	if (mManager == nullptr) return;
	// Random
	const Vec2 &rdm = mManager->getRdmPos();
	this->startFollowPos(rdm.x, rdm.y);
}

void SpriteMaze::startFollowLeader() {
	// MazeManager
	if (mManager == nullptr) return;
	// Leader
	if (leader == nullptr) return;
	// Leader
	const Vec2 &pos = leader->getPos();
	this->startFollowPos(pos.x, pos.y);
}

void SpriteMaze::startFollowPos(int x, int y) {
	// MazeManager
	if (mManager == nullptr) return;
	// Route
	vector<Vec2> poses = mManager->detectRouteByPos(pos.x, pos.y, x, y);
	// Ways
	if (0 < ways.size()) ways.clear();
	for (auto pos: poses) ways.push_back(pos);
	// Blocking backward
	if (2 < ways.size()) {
		const Vec2 &last1 = ways.at(ways.size() - 1);
		const Vec2 &last3 = ways.at(ways.size() - 3);
		bool flgX = signbit(last1.x - pos.x) != signbit(last3.x - pos.x);
		bool flgY = signbit(last1.y - pos.y) != signbit(last3.y - pos.y);
		if (flgX && flgY) {
			// Do nothing
		} else if (flgX && !flgY) {
			ways.pop_back();
		} else if (!flgX && flgY) {
			ways.pop_back();
		} else {
			// Do nothing
		}
	}
	// State
	this->changeState(StateMaze::FOLLOWWAY);
}

void SpriteMaze::startFollowNext() {
	// MazeManager
	if (mManager == nullptr) return;
	// State
	this->changeState(StateMaze::FOLLOWNEXT);
}

void SpriteMaze::setLeader(SpriteBase *spr) {
	// Leader
	leader = spr;
}

bool SpriteMaze::searchLeaderInsight() {
	// MazeManager
	if (mManager == nullptr) return false;
	// Leader
	if (leader == nullptr) return false;
	// Eyesight
	const int left = mManager->getWallLX(pos.x, pos.y, 30);
	const int right = mManager->getWallRX(pos.x, pos.y, 30);
	const int up = mManager->getWallUY(pos.x, pos.y, 30);
	const int down = mManager->getWallDY(pos.x, pos.y, 30);
	if (leader->getPosX() < left) return false;
	if (right < leader->getPosX()) return false;
	if (minY < leader->getPosY() && leader->getPosY() < maxY) return true;
	if (leader->getPosY() < up) return false;
	if (down < leader->getPosY()) return false;
	if (minX < leader->getPosX() && leader->getPosX() < maxX) return true;
	return false;
}

bool SpriteMaze::checkLeaderOnSameRC() {
	return mManager->isSameRCByPos(pos, leader->getPos());
}

bool SpriteMaze::checkLeaderOnway() {
	// Ways
	if (ways.size() <= 0) return false;
	const Vec2 &way = ways.at(0);
	const int wR = mManager->getRByY(way.y);
	const int wC = mManager->getCByX(way.x);
	const int lR = mManager->getRByY(leader->getPosY());
	const int lC = mManager->getCByX(leader->getPosX());
	return wR == lR && wC == lC;
}