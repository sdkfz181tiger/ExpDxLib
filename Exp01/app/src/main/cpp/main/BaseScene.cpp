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

}

void BaseScene::draw(float delay) {

}