#include "GameManager.h"

GameManager::GameManager(int dWidth, int dHeight, int cDepth) :
		dWidth(dWidth), dHeight(dHeight), cDepth(cDepth) {
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