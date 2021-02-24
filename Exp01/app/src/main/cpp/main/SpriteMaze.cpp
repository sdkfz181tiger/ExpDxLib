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
	Vec2 &rdm =	mManager->getRdmPos();
	this->startFollowPos(rdm.x, rdm.y);
}

void SpriteMaze::startFollowPos(int x, int y) {
	// MazeManager
	if (mManager == nullptr) return;
	// Route
	vector<Vec2> poses = mManager->detectRouteByPos(pos.x, pos.y, x, y);
	// Ways
	if (0 < ways.size()) ways.clear();
	for (auto pos: poses) ways.push_back(pos);
	// State
	this->changeState(StateMaze::FOLLOWWAY);
}

void SpriteMaze::startFollowNext() {
	// State
	this->changeState(StateMaze::FOLLOWNEXT);
}