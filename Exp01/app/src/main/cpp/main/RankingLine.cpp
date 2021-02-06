#include "RankingLine.h"

#include <utility>

RankingLine *RankingLine::createLine(float x, float y, int pX, int wC, Rank &r) {
	// New
	RankingLine *sprite = new RankingLine(x, y, pX, wC, r);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

RankingLine::RankingLine(float x, float y, int pX, int wC, Rank &r) :
		pos(Vec2(x, y)), padX(pX), waitCnt(wC), rank(r) {
	LOGD("Main", "RankingLine()\n");
}

RankingLine::~RankingLine() {
	LOGD("Main", "~RankingLine()\n");
}

bool RankingLine::init() {
	return true;
}

void RankingLine::update(const float delay) {

	// Wait
	waitCnt--;
	if(0 < waitCnt) return;

	// Rank
	char str[30];
	sprintf(str, "%d", rank.num);
	UtilLabel::getInstance()->drawStr(str, pos.x - padX * 16, pos.y, 3,
									  UtilAlign::LEFT);
	// Score
	sprintf(str, "%06d", rank.score);
	UtilLabel::getInstance()->drawStr(str, pos.x - padX * 12, pos.y, 3,
									  UtilAlign::LEFT);
	// Hiyoko
	sprintf(str, "%03d", rank.hiyoko);
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 2, pos.y, 3,
									  UtilAlign::LEFT);
	// Name
	sprintf(str, "%s", rank.name.c_str());
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 10, pos.y, 3,
									  UtilAlign::LEFT);
}