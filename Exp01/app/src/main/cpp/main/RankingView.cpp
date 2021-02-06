#include "RankingView.h"

RankingView *RankingView::createRanking(float x, float y, int pX, int pY) {
	// New
	RankingView *sprite = new RankingView(x, y, pX, pY);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

RankingView::RankingView(float x, float y, int pX, int pY) :
		pos(Vec2(x, y)), padX(pX), padY(pY), counter(0), progress(0),
		cntScore(UtilLocalSave::getInstance()->getNum("score", 0)),
		cntHigh(UtilLocalSave::getInstance()->getNum("high", 0)),
		blinkCnt(0), blinkInterval(8), blinkTimes(8), blinkFlg(false) {
	LOGD("Main", "RankingView()\n");
}

RankingView::~RankingView() {
	LOGD("Main", "~RankingView()\n");
	DX_SAFE_DELETE_VECTOR(lines);
}

bool RankingView::init() {

	const int fps = UtilDx::getInstance()->getFPS();
	if (cntScore < fps) {
		progress = 1;
	} else {
		progress = (cntScore / fps) * 2;
	}

	// Test
	bool flg = UtilMath::getInstance()->getRandom(0, 10) < 5;
	int score = UtilMath::getInstance()->getRandom(100, 3000);
	int hiyoko = UtilMath::getInstance()->getRandom(1, 99);
	json obj1 = {{"flg",    flg},
				 {"num",    1},
				 {"score",  score},
				 {"hiyoko", hiyoko},
				 {"name",   "SMJ"}};
	UtilLocalSave::getInstance()->pushArray("ranking", obj1);

	json &ranking = UtilLocalSave::getInstance()->getArray("ranking");
	const int total = ranking.size();
	for (int i = 0; i < total; i++) {
		lines.push_back(RankingLine::createLine(pos.x, pos.y + padY * (i + 4),
												padX, (total - i) * 5,
												ranking.at(i)));
	}

	return true;
}

void RankingView::update(const float delay) {

	UtilLabel::getInstance()->drawStr("SCORE", pos.x, pos.y - padY * 1, 3,
									  UtilAlign::CENTER);

	// Score
	char str[30];
	counter += progress;
	if (cntScore < counter) counter = cntScore;

	if (cntScore <= counter && 0 < blinkTimes) {
		blinkCnt++;
		if (blinkInterval < blinkCnt) {
			blinkCnt = 0;
			blinkTimes--;
			blinkFlg = !blinkFlg;
		}
	}

	if (!blinkFlg) {
		sprintf(str, "%d", counter);
		UtilLabel::getInstance()->drawStr(str, pos.x, pos.y, 8,
										  UtilAlign::CENTER);
	}

	// TOP
	sprintf(str, "= TOP %d =", lines.size());
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y + padY * 3, 3,
									  UtilAlign::CENTER);

	// Line
	for (auto line:lines) line->update(delay);
}