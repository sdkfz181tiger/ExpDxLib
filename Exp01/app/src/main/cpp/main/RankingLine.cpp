#include "RankingLine.h"

#include <utility>

RankingLine *RankingLine::createLine(float x, float y, int pX, int wC, json &r) {
	// New
	RankingLine *sprite = new RankingLine(x, y, pX, wC, r);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

RankingLine::RankingLine(float x, float y, int pX, int wC, json &r) :
		pos(Vec2(x, y)), padX(pX), waitCnt(wC), rank(r) {
	LOGD("Main", "RankingLine()\n");
}

RankingLine::~RankingLine() {
	LOGD("Main", "~RankingLine()\n");
	DX_SAFE_DELETE(mkL);
	DX_SAFE_DELETE(mkR);
}

bool RankingLine::init() {

	// Marker
	mkL = SpriteChick::createSprite("images/c_chick.png", pos.x - padX * 16, pos.y);
	mkR = SpriteChick::createSprite("images/c_chick.png", pos.x + padX * 16, pos.y);

	return true;
}

void RankingLine::update(const float delay) {

	// Wait
	waitCnt--;
	if (0 < waitCnt) return;

	bool rankin = rank["rankin"].get<bool>();
	int num = rank["num"].get<int>();
	int score = rank["score"].get<int>();
	string name = rank["name"].get<string>();

	// Marker
	if (rankin) {
		mkL->update(delay);
		mkR->update(delay);
	}

	// Rank
	char str[30];
	sprintf(str, "%d.", num);
	UtilLabel::getInstance()->drawStr(str, pos.x - padX * 14, pos.y, 2,
									  UtilAlign::LEFT);
	// Score
	sprintf(str, "%d", score);
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 5, pos.y, 2,
									  UtilAlign::RIGHT);
	// Name
	sprintf(str, "%s", name.c_str());
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 8, pos.y, 2,
									  UtilAlign::LEFT);
}