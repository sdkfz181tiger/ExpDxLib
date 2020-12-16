#include "GameManager.h"

GameManager::GameManager(int dWidth, int dHeight, int cDepth) :
		dWidth(dWidth), dHeight(dHeight), cDepth(cDepth), quitFlg(false) {
	LOGD("Main", "GameManager()\n");
	this->init();// Initialize
}

GameManager::~GameManager() {
	LOGD("Main", "~GameManager()\n");
}

void GameManager::init() {

	SetGraphMode(dWidth, dHeight, cDepth);
	SetOutApplicationLogValidFlag(false);
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

void GameManager::setQuitFlg(bool quitFlg) {
	this->quitFlg = quitFlg;
}

void GameManager::draw(float delay) {

	const int cX = dWidth / 2;
	const int cY = dHeight / 2;

	// Label
	UtilLabel::getInstance()->drawStr("HELLO DXLIB!!", cX, cY,
	                                  5, UtilAlign::CENTER);

	// Debug
	UtilDebug::getInstance()->drawGrid();
	UtilDebug::getInstance()->drawFPS(delay);
}