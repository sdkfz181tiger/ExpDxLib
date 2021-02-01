#include "ScoreHopper.h"

ScoreHopper *ScoreHopper::createHopper(float x, float y, int n) {
	// New
	ScoreHopper *sprite = new ScoreHopper(x, y, n);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

ScoreHopper::ScoreHopper(float x, float y, int n) :
		pos(Vec2(x, y)), vel(Vec2(0, UtilDebug::getInstance()->getGridSize() * -10)),
		num(n), waitCnt(0), waitInterval(20),
		groundY(y), gravityY(UtilDebug::getInstance()->getGridSize()), str("") {
	LOGD("Main", "ScoreHopper()\n");
}

ScoreHopper::~ScoreHopper() {
	LOGD("Main", "~ScoreHopper()\n");
}

bool ScoreHopper::init() {
	return true;
}

void ScoreHopper::update(const float delay) {

	if (pos.y <= groundY) {
		vel.y += gravityY;
		pos.y += vel.y * delay;
	} else {
		if (waitCnt < waitInterval) {
			waitCnt++;
		}
	}

	// Label
	sprintf(str, "%d", num);
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y,
									  2, UtilAlign::CENTER);
}

bool ScoreHopper::isWaiting() {
	return waitCnt < waitInterval;
}