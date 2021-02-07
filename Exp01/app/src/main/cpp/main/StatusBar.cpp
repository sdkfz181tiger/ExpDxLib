#include "StatusBar.h"

StatusBar *StatusBar::create(float x, float y, int w, int h) {
	// New
	StatusBar *sprite = new StatusBar(x, y, w, h);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

StatusBar::StatusBar(float x, float y, int w, int h) :
		pos(Vec2(x, y)), center(Vec2(x + w / 2, y + h / 2)),
		width(w), height(h), gSize(UtilDebug::getInstance()->getGridSize()),
		waitCnt(0), waitInterval(8), offsetY(0),
		score(UtilLocalSave::getInstance()->getNum("score", 0)),
		bonus(UtilLocalSave::getInstance()->getNum("bonus", 0)),
		high(UtilLocalSave::getInstance()->getNum("high", 0)),
		scoreStr(""), highStr(""),
		black(GetColor(0, 0, 0)) {
	LOGD("Main", "StatusBar()\n");
}

StatusBar::~StatusBar() {
	LOGD("Main", "~StatusBar()\n");
	DX_SAFE_DELETE_VECTOR(btns);
}

bool StatusBar::init() {
	return true;
}

void StatusBar::setOnTouchBegan(int id, int x, int y) {
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);// Buttons
}

void StatusBar::setOnTouchMoved(int id, int x, int y) {
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);// Buttons
}

void StatusBar::setOnTouchEnded(int id, int x, int y) {
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);// Buttons
}

void StatusBar::pushBtnBase(BtnBase *btn) {
	btns.push_back(btn);
}

void StatusBar::offsetAdHeight() {
	// AdMob
	const int adHeight = UtilJNI::getInstance()->getAdHeight();
	const int sHeight = UtilJNI::getInstance()->getScreenHeight();
	const int dHeight = UtilDx::getInstance()->getDispHeight();
	offsetY = dHeight * adHeight / sHeight;
	if (offsetY <= 0) return;
	for (auto btn : btns) btn->offsetPos(0, offsetY);
}

void StatusBar::resetScore() {
	// Score
	score = 0;
	UtilLocalSave::getInstance()->setNum("score", score);
}

void StatusBar::addScore(int num) {
	// Score
	score += num;
	UtilLocalSave::getInstance()->setNum("score", score);
	// High
	if (high < score) {
		high = score;
		UtilLocalSave::getInstance()->setNum("high", high);
	}
}

void StatusBar::resetBonus() {
	// Bonus
	bonus = 0;
	UtilLocalSave::getInstance()->setNum("bonus", score);
}

void StatusBar::setBonus(int num) {
	// Bonus
	bonus = num;
	UtilLocalSave::getInstance()->setNum("bonus", bonus);
}

void StatusBar::update(const float delay) {

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
	sprintf(scoreStr, "SC:%d", score);
	UtilLabel::getInstance()->drawStr(scoreStr,
									  gSize / 2, center.y + offsetY,
									  2, UtilAlign::LEFT);
	sprintf(highStr, "HI:%d", high);
	UtilLabel::getInstance()->drawStr(highStr,
									  center.x, center.y + offsetY,
									  2, UtilAlign::CENTER);

	// Buttons
	for (auto btn : btns) btn->update(delay);
}