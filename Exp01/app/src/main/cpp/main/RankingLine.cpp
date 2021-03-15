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
	if (num == 1) {
		sprintf(str, "1ST.", num);
	} else if (num == 2) {
		sprintf(str, "2ND.", num);
	} else if (num == 3) {
		sprintf(str, "3RD.", num);
	} else if (num == 4) {
		sprintf(str, "4TH.", num);
	} else if (num == 5) {
		sprintf(str, "5TH.", num);
	} else {
		sprintf(str, "ERR.", num);
	}

	UtilLabel::getInstance()->drawStr(str, pos.x - padX * 14, pos.y, 2,
									  UtilAlign::LEFT);
	// Score
	sprintf(str, "%d", score);
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 6, pos.y, 2,
									  UtilAlign::RIGHT);
	// Name
	sprintf(str, "%s", name.c_str());
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 9, pos.y, 2,
									  UtilAlign::LEFT);
}