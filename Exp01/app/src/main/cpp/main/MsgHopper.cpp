#include "MsgHopper.h"

MsgHopper *MsgHopper::createNum(float x, float y, int n) {
	// New
	MsgHopper *sprite = new MsgHopper(x, y);
	if (sprite && sprite->init(n)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

MsgHopper *MsgHopper::createStr(float x, float y, const string &s) {
	// New
	MsgHopper *sprite = new MsgHopper(x, y);
	if (sprite && sprite->init(s)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

MsgHopper::MsgHopper(float x, float y) :
		pos(Vec2(x, y)), vel(Vec2(0, UtilDebug::getInstance()->getGridSize() * -10)),
		waitCnt(0), waitInterval(20),
		groundY(y), gravityY(UtilDebug::getInstance()->getGridSize()), str("") {
	LOGD("Main", "MsgHopper()\n");
}

MsgHopper::~MsgHopper() {
	LOGD("Main", "~MsgHopper()\n");
}

bool MsgHopper::init(int n) {
	str = to_string(n);
	return true;
}

bool MsgHopper::init(const string &s) {
	str = s;
	return true;
}

void MsgHopper::update(const float delay) {

	if (pos.y <= groundY) {
		vel.y += gravityY;
		pos.y += vel.y * delay;
	} else {
		if (waitCnt < waitInterval) {
			waitCnt++;
		}
	}

	// Label
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y,
									  2, UtilAlign::CENTER);
}

bool MsgHopper::isWaiting() {
	return waitCnt < waitInterval;
}