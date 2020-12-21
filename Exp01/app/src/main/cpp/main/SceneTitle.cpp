#include "SceneTitle.h"

SceneTitle::SceneTitle(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
				tSprite(nullptr) {
	LOGD("Main", "SceneTitle()\n");
	this->init();// Initialize
}

SceneTitle::~SceneTitle() {
	LOGD("Main", "~SceneTitle()\n");
	// Test
	if (tSprite) delete (tSprite);
}

void SceneTitle::init() {
	LOGD("Main", "SceneTitle::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	// Test
	tSprite = SpriteBase::createSprite("images/y_reimu_x1.png", cX, cY);
	tSprite->setScale(5);
}

void SceneTitle::setOnTouchBegan(int id, int x, int y) {
	LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
}

void SceneTitle::setOnTouchMoved(int id, int x, int y) {
	LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
}

void SceneTitle::setOnTouchEnded(int id, int x, int y) {
	LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
}

void SceneTitle::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	// Label
	UtilLabel::getInstance()->drawStr("TITLE!!", cX, cY,
	                                  5, UtilAlign::CENTER);

	// Test
	if(tSprite) tSprite->update(delay);
}