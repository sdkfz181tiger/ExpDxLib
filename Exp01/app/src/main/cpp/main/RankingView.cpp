#include "RankingView.h"

RankingView *RankingView::createRanking(float x, float y, int pX, int pY) {
	// New
	RankingView *sprite = new RankingView(x, y, pX, pY);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

RankingView::RankingView(float x, float y, int pX, int pY) :
		pos(Vec2(x, y)), padX(pX), padY(pY), counter(0),
		cntScore(UtilLocalSave::getInstance()->getNum("score", 0)),
		cntBonus(UtilLocalSave::getInstance()->getNum("bonus", 0)),
		cntHigh(UtilLocalSave::getInstance()->getNum("high", 0)),
		stpA(0), stpIntervalA(2),
		stpB(0), stpIntervalB(10),
		stpC(0), stpIntervalC(10),
		blinkTimes(7), blinkFlg(false) {
	LOGD("Main", "RankingView()\n");
}

RankingView::~RankingView() {
	LOGD("Main", "~RankingView()\n");
	DX_SAFE_DELETE_VECTOR(lines);
}

bool RankingView::init() {

	// Rank
	json rank = {{"rankin", false},
				 {"num",    0},
				 {"score",  cntScore},
				 {"bonus",  cntBonus},
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
	ranking.erase(ranking.begin() + 3, ranking.end());
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
												padX, (ranking.size() - i) * 5,
												rank));
	}
}

void RankingView::stepScore(const float delay) {

	// Score
	stpA++;
	if (stpIntervalA < stpA) {
		stpA = 0;
		counter += 1;
		if (cntScore < counter) counter = cntScore;
		UtilSound::getInstance()->playSE("sounds/se_cnt_score.wav");
	}

	char str[30];
	sprintf(str, "%d", counter);
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y, 8,
									  UtilAlign::CENTER);
}

void RankingView::stepBonus(const float delay) {

	// Bonus
	stpB++;
	if (stpIntervalB < stpB) {
		stpB = 0;
		counter += 5;
		if (cntScore + cntBonus < counter) counter = cntScore + cntBonus;
		UtilSound::getInstance()->playSE("sounds/se_cnt_bonus.wav");
	}

	char str[30];
	sprintf(str, "%d", counter);
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y, 8,
									  UtilAlign::CENTER);
}

void RankingView::stepBlink(const float delay) {

	// Blink
	if (0 < blinkTimes) {
		stpC++;
		if (stpIntervalC < stpC) {
			stpC = 0;
			blinkTimes--;
			blinkFlg = !blinkFlg;
		}
	}

	if (!blinkFlg) return;
	char str[30];
	sprintf(str, "%d", counter);
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y, 8,
									  UtilAlign::CENTER);
}

void RankingView::progressRanking(const float delay) {

	// Ranking
	char str[20];
	sprintf(str, "= TOP %lu =", lines.size());
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y + padY * 3, 3,
									  UtilAlign::CENTER);

	// Line
	for (auto line:lines) line->update(delay);
}

void RankingView::update(const float delay) {

	UtilLabel::getInstance()->drawStr("SCORE", pos.x, pos.y - padY * 1, 3,
									  UtilAlign::CENTER);

	// Score
	if (counter < cntScore) {
		this->stepScore(delay);
	} else if (counter < cntScore + cntBonus) {
		this->stepBonus(delay);
	} else {
		this->stepBlink(delay);
	}

	this->progressRanking(delay);
}