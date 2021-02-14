#include "MsgHopper.h"

MsgHopper *MsgHopper::createNum(float x, float y, int s, int n) {
	// New
	MsgHopper *sprite = new MsgHopper(x, y, s);
	if (sprite && sprite->init(n)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

MsgHopper *MsgHopper::createStr(float x, float y, int s, const string &msg) {
	// New
	MsgHopper *sprite = new MsgHopper(x, y, s);
	if (sprite && sprite->init(msg)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

MsgHopper::MsgHopper(float x, float y, int s) :
		pos(Vec2(x, y)), scale(s),
		vY(UtilDebug::getInstance()->getGridSize() * -10),
		waitCnt(0), waitInterval(20),
		groundY(y), gravityY(UtilDebug::getInstance()->getGridSize()), msg("") {
	LOGD("Main", "MsgHopper()\n");
}

MsgHopper::~MsgHopper() {
	LOGD("Main", "~MsgHopper()\n");
}

bool MsgHopper::init(int n) {
	msg = to_string(n);
	return true;
}

bool MsgHopper::init(const string &m) {
	msg = m;
	return true;
}

void MsgHopper::update(const float delay) {

	if (pos.y <= groundY) {
		vY += gravityY;
		pos.y += vY * delay;
	} else {
		if (waitCnt < waitInterval) {
			waitCnt++;
		}
	}

	// Label
	UtilLabel::getInstance()->drawStr(msg, pos.x, pos.y,
									  scale, UtilAlign::CENTER);
}

bool MsgHopper::isWaiting() {
	return waitCnt < waitInterval;
}