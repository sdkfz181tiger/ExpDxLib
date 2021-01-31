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
		waitCnt(0), waitInterval(16), offsetY(0),
		black(GetColor(0, 0, 0)) {
	LOGD("Main", "ScoreBar()\n");
}

ScoreBar::~ScoreBar() {
	LOGD("Main", "~ScoreBar()\n");
	DX_SAFE_DELETE_VECTOR(btns);
}

bool ScoreBar::init() {
	return true;
}

void ScoreBar::setOnTouchBegan(int id, int x, int y) {
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);// Buttons
}

void ScoreBar::setOnTouchMoved(int id, int x, int y) {
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);// Buttons
}

void ScoreBar::setOnTouchEnded(int id, int x, int y) {
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);// Buttons
}

void ScoreBar::pushBtnBase(BtnBase *btn) {
	btns.push_back(btn);
}

void ScoreBar::offsetAdHeight() {
	// AdMob
	const int adHeight = UtilJNI::getInstance()->getAdHeight();
	const int sHeight = UtilJNI::getInstance()->getScreenHeight();
	const int dHeight = UtilDx::getInstance()->getDispHeight();
	offsetY = dHeight * adHeight / sHeight;
	if (offsetY <= 0) return;
	for (auto btn : btns) btn->offsetPos(0, offsetY);
}

void ScoreBar::update(const float delay) {

	if (offsetY <= 0) {
		if (waitCnt < waitInterval) {
			waitCnt++;
		} else {
			waitCnt = 0;
			this->offsetAdHeight();
		}
	}

	// Background
	DrawBox(pos.x, 0, pos.x + width, pos.y + offsetY + height,
			black, true);

	// Labels
	UtilLabel::getInstance()->drawStr("SCORE:12345",
									  gSize / 2, center.y + offsetY,
									  2, UtilAlign::LEFT);

	// Buttons
	for (auto btn : btns) btn->update(delay);
}