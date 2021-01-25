#include "LoadingMarker.h"

LoadingMarker *LoadingMarker::createMarker(float x, float y, int w, int h) {
	// New
	LoadingMarker *sprite = new LoadingMarker(x, y, w, h);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

LoadingMarker::LoadingMarker(float x, float y, int w, int h) :
		pos(Vec2(x, y)), width(w), height(h),
		loadCnt(0), loadTotal(100), loadMsg("***"),
		white(GetColor(255, 255, 255)),
		gray(GetColor(99, 99, 99)) {
	LOGD("Main", "LoadingMarker()\n");
}

LoadingMarker::~LoadingMarker() {
	LOGD("Main", "~LoadingMarker()\n");
}

bool LoadingMarker::init() {
	return true;
}

void LoadingMarker::setMsg(const char *msg) {
	loadMsg = msg;
}

void LoadingMarker::setCnt(int cnt) {
	loadCnt = cnt;
}

int LoadingMarker::getCnt() {
	return loadCnt;
}

void LoadingMarker::setTotal(int total) {
	loadTotal = total;
}

void LoadingMarker::progress(int progress) {
	loadCnt += progress;
	if (loadTotal < loadCnt) loadCnt = loadTotal;
}

void LoadingMarker::update() {

	const int gSize = UtilDebug::getInstance()->getGridSize();
	const float percent = (float) loadCnt / (float) loadTotal;

	// Message
	UtilLabel::getInstance()->drawStr(loadMsg, pos.x, pos.y - gSize,
									  2, UtilAlign::CENTER);
	// Background
	DrawBox(pos.x - width / 2, pos.y - height / 2,
			pos.x + width / 2, pos.y + height / 2,
			gray, true);
	// Bar
	const int bar = width * percent;
	DrawBox(pos.x - bar / 2, pos.y - height / 2,
			pos.x + bar / 2, pos.y + height / 2,
			white, true);
	// Percent
	stringstream ss;
	ss << floor(percent * 100.0f) << "%";
	UtilLabel::getInstance()->drawStr(ss.str(), pos.x, pos.y + gSize,
									  2, UtilAlign::CENTER);
}