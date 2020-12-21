#include "BaseScene.h"

BaseScene::BaseScene(int dWidth, int dHeight) :
		dWidth(dWidth), dHeight(dHeight) {
	LOGD("Main", "BaseScene()\n");
	this->init();// Initialize
}

BaseScene::~BaseScene() {
	LOGD("Main", "~BaseScene()\n");
}

void BaseScene::init() {
	LOGD("Main", "BaseScene::init()\n");
}

void BaseScene::setOnTouchBegan(int id, int x, int y) {
	LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
}

void BaseScene::setOnTouchMoved(int id, int x, int y) {
	LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
}

void BaseScene::setOnTouchEnded(int id, int x, int y) {
	LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
}

void BaseScene::draw(float delay) {

	const int cX = dWidth / 2;
	const int cY = dHeight / 2;

	// Label
	UtilLabel::getInstance()->drawStr("BASE SCENE!!", cX, cY,
	                                  5, UtilAlign::CENTER);
}