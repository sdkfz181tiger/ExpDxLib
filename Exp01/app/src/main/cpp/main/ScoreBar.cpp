#include "ScoreBar.h"

ScoreBar *ScoreBar::create(float x, float y, int w, int h) {
	// New
	ScoreBar *sprite = new ScoreBar(x, y, w, h);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

ScoreBar::ScoreBar(float x, float y, int w, int h) :
		pos(Vec2(x, y)), center(Vec2(x + w / 2, y + h / 2)),
		width(w), height(h), gSize(UtilDebug::getInstance()->getGridSize()),
		waitFlg(true), waitCnt(0), waitInterval(16),
		black(GetColor(0, 0, 0)) {
	LOGD("Main", "ScoreBar()\n");
}

ScoreBar::~ScoreBar() {
	LOGD("Main", "~ScoreBar()\n");
}

bool ScoreBar::init() {
	return true;
}

bool ScoreBar::offsetAdHeight() {

	const int adHeight = UtilJNI::getInstance()->getAdHeight();
	const int sHeight = UtilJNI::getInstance()->getScreenHeight();
	const int dHeight = UtilDx::getInstance()->getDispHeight();
	pos.y = dHeight * adHeight / sHeight;
	center.y = pos.y + height / 2;
	return 0 < pos.y;
}

void ScoreBar::update(const float delay) {

	if (waitFlg) {
		if (waitCnt < waitInterval) {
			waitCnt++;
		} else {
			waitCnt = 0;
			if (this->offsetAdHeight()) waitFlg = false;
		}
	}

	// Background
	DrawBox(pos.x, 0, pos.x + width, pos.y + height, black, true);

	// Labels
	UtilLabel::getInstance()->drawStr("SCORE:12345", gSize / 2, center.y,
									  2, UtilAlign::LEFT);
}