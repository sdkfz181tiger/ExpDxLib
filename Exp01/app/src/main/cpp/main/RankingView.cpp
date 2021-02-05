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
		blinkCnt(0), blinkInterval(8), blinkTimes(10), blinkFlg(false) {
	LOGD("Main", "RankingView()\n");
}

RankingView::~RankingView() {
	LOGD("Main", "~RankingView()\n");
}

bool RankingView::init() {

	const int fps = UtilDx::getInstance()->getFPS();
	if (cntScore < fps) {
		progress = 1;
	} else {
		progress = (cntScore / fps) * 2;
	}

	// Test
	ranking.push_back(Rank{99999, 999, "SMJ"});
	ranking.push_back(Rank{8888, 888, "ABC"});
	ranking.push_back(Rank{777, 77, "DEF"});
	ranking.push_back(Rank{66, 66, "DEF"});
	ranking.push_back(Rank{5, 5, "GHI"});

	return true;
}

void RankingView::update(const float delay) {

	char str[30];

	// Score
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
	sprintf(str, "= TOP %d =", ranking.size());
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y + padY * 3, 3,
									  UtilAlign::CENTER);

	for (int i = 0; i < ranking.size(); i++) {
		const int x = pos.x;
		const int y = pos.y + padY * (i + 4);
		Rank &rank = ranking.at(i);
		// Rank
		sprintf(str, "%d", i + 1);
		UtilLabel::getInstance()->drawStr(str, x - padX * 16, y, 3,
										  UtilAlign::LEFT);
		// Score
		sprintf(str, "%06d", rank.score);
		UtilLabel::getInstance()->drawStr(str, x - padX * 12, y, 3,
										  UtilAlign::LEFT);
		// Hiyoko
		sprintf(str, "%03d", rank.hiyoko);
		UtilLabel::getInstance()->drawStr(str, x + padX * 2, y, 3,
										  UtilAlign::LEFT);
		// Name
		sprintf(str, "%s", rank.name.c_str());
		UtilLabel::getInstance()->drawStr(str, x + padX * 10, y, 3,
										  UtilAlign::LEFT);
	}
}