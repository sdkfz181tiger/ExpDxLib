#include "GameManager.h"

GameManager::GameManager(int dWidth, int dHeight, int cDepth) :
		dWidth(dWidth), dHeight(dHeight), cDepth(cDepth), quitFlg(false),
		touchFlgs(5, false), touchPositions(5, Vec2()) {
	LOGD("Main", "GameManager()\n");
	this->init();// Initialize
}

GameManager::~GameManager() {
	LOGD("Main", "~GameManager()\n");
}

void GameManager::init() {
	// GraphMode
	SetGraphMode(dWidth, dHeight, cDepth);
	SetOutApplicationLogValidFlag(true);
}

int GameManager::getDispWidth() {
	return dWidth;
}

int GameManager::getDispHeight() {
	return dHeight;
}

bool GameManager::getQuitFlg() {
	return this->quitFlg;
}

void GameManager::touchInput() {

	int x, y, id;
	vector<bool> touches(5, false);
	for (int i = 0; i < GetTouchInputNum(); i++) {
		GetTouchInput(i, &x, &y, &id, nullptr);
		if (touchFlgs.size() <= id) continue;
		if (touchPositions.size() <= id) continue;
		if (!touchFlgs.at(id)) {
			LOGD("Touch", "Began[%d]: %d, %d", id, x, y);
		} else {
			if (touchPositions.at(id).x != x || touchPositions.at(id).y != y) {
				//LOGD("Touch", "Move[%d]: %d, %d", id, x, y);
			}
		}
		touches.at(id) = true;
		touchFlgs.at(id) = true;
		touchPositions.at(id).x = x;
		touchPositions.at(id).y = y;
	}

	for (int i = 0; i < touches.size(); i++) {
		if (touches.at(i)) continue;
		if (!touchFlgs.at(i)) continue;
		touchFlgs.at(i) = false;
		int x = int(touchPositions.at(i).x);
		int y = int(touchPositions.at(i).y);
		LOGD("Touch", "Ended[%d]: %d, %d", i, x, y);
	}
}

void GameManager::update(const float delay) {

	const int cX = dWidth / 2;
	const int cY = dHeight / 2;

	// Label
	UtilLabel::getInstance()->drawStr("HELLO DXLIB!!", cX, cY,
	                                  5, UtilAlign::CENTER);

	// Debug
	UtilDebug::getInstance()->drawGrid();
	UtilDebug::getInstance()->drawFPS(delay);
}

