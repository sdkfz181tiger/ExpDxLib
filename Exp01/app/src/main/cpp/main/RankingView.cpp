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

	// Score
	int hiyoko = UtilMath::getInstance()->getRandom(1, 30);
	json rank = {{"rankin", false},
				 {"num",    0},
				 {"score",  cntScore},
				 {"hiyoko", hiyoko},
				 {"name",   "YOU"}};
	UtilLocalSave::getInstance()->pushArray("ranking", rank);

	this->sortRanking();

	return true;
}

void RankingView::sortRanking() {

	// Ranking
	json &ranking = UtilLocalSave::getInstance()->getArray("ranking");
	// Sort
	for (int a = ranking.size() - 1; 0 <= a; a--) {
		json &objA = ranking.at(a);
		for (int b = a - 1; 0 <= b; b--) {
			json &objB = ranking.at(b);
			if (objA["score"].get<int>() < objB["score"].get<int>()) continue;
			objA.swap(objB);// Swap
		}
	}
	// Top 3
	ranking.erase(ranking.begin()+3, ranking.end());
	// Number
	bool flg = false;
	for (int i = 0; i < ranking.size(); i++) {
		json &rank = ranking.at(i);
		int score = rank["score"].get<int>();
		if (!flg && score <= cntScore) {
			rank["rankin"] = true;
			flg = true;
		} else {
			rank["rankin"] = false;
		}
		rank["num"] = i + 1;
		lines.push_back(RankingLine::createLine(pos.x, pos.y + padY * (i + 4),
												padX, (ranking.size() - i) * 5, rank));
	}
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