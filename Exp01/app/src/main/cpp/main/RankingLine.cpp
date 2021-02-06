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
	if(0 < waitCnt) return;

	// Marker
	if(rank.flg){
		mkL->update(delay);
		mkR->update(delay);
	}

	// Rank
	char str[30];
	sprintf(str, "%d", rank.rank);
	UtilLabel::getInstance()->drawStr(str, pos.x - padX * 14, pos.y, 3,
									  UtilAlign::LEFT);
	// Score
	sprintf(str, "%05d", rank.score);
	UtilLabel::getInstance()->drawStr(str, pos.x - padX * 10, pos.y, 3,
									  UtilAlign::LEFT);
	// Hiyoko
	sprintf(str, "%02d", rank.hiyoko);
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 2, pos.y, 3,
									  UtilAlign::LEFT);
	// Name
	sprintf(str, "%s", rank.name.c_str());
	UtilLabel::getInstance()->drawStr(str, pos.x + padX * 8, pos.y, 3,
									  UtilAlign::LEFT);
}