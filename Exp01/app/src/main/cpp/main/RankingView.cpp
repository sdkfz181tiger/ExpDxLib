#include "RankingView.h"

RankingView *RankingView::createRanking(float x, float y, int pX, int pY) {
	// New
	RankingView *sprite = new RankingView(x, y, pX, pY);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

RankingView::RankingView(float x, float y, int pX, int pY) :
		pos(Vec2(x, y)), padX(pX), padY(pY), rankinFlg(false), counter(0),
		score(UtilLocalSave::getInstance()->getNum("score", 0)),
		bonus(UtilLocalSave::getInstance()->getNum("bonus", 0)),
		high(UtilLocalSave::getInstance()->getNum("high", 0)),
		stpA(0), stpIntervalA(2),
		stpB(0), stpIntervalB(12),
		stpC(0), stpIntervalC(5),
		rateBonus(30), blinkTimes(15),
		blinkFlg(false), replaceFlg(false),
		fireCnt(0), fireInterval(30),
		updateMode(SCORE) {
	LOGD("Main", "RankingView()\n");
}

RankingView::~RankingView() {
	LOGD("Main", "~RankingView()\n");
	DX_SAFE_DELETE_VECTOR(lines);
	DX_SAFE_DELETE_VECTOR(fireworks);
}

bool RankingView::init() {

	// Rank
	json rank = {{"rankin", false},
				 {"num",    0},
				 {"score",  score + bonus * rateBonus},
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
	if (3 < ranking.size()) ranking.erase(ranking.begin() + 3, ranking.end());
	// Number
	rankinFlg = false;// Rankin or not
	for (int i = 0; i < ranking.size(); i++) {
		json &rank = ranking.at(i);
		if (!rankinFlg && rank["score"].get<int>() <= score + bonus * rateBonus) {
			rank["rankin"] = true;
			rankinFlg = true;// Rankin!!
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

	if (score <= 0) {
		updateMode = BLINK;// Next
		this->startRankinEffect();// Effect
		return;
	}

	// Score
	stpA++;
	if (stpIntervalA < stpA) {
		stpA = 0;
		counter += (score < 30) ? 1 : score / 10;
		if (score < counter) {
			counter = score;
			updateMode = BONUS;// Next
			return;
		}
		// SE
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
		counter += rateBonus;
		if (score + bonus * rateBonus < counter) {
			counter = score + bonus * rateBonus;
			updateMode = BLINK;// Next
			this->startRankinEffect();// Effect
			return;
		}
		// SE
		UtilSound::getInstance()->playSE("sounds/se_cnt_bonus.wav");
		// Chicks
		int cols = 12;
		if (bonus < 13) cols = 6;
		// Chicks
		const int r = chicks.size() / cols;
		const int c = chicks.size() % cols;
		const int padH = padX * 3;
		const int padV = padY * 2 / 3;
		int startX = pos.x - padH / 2 * (cols - 1);
		if (bonus < cols) {
			startX = pos.x - padH / 2 * (bonus - 1);
		}
		const int startY = pos.y + padV * 2;
		const int x = startX + padH * c;
		const int y = startY + padV * r;
		auto chick = SpriteChick::createSprite("images/c_chick.png", x, y);
		chicks.push_back(chick);
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

void RankingView::stepRanking(const float delay) {

	// Ranking
	char str[20];
	sprintf(str, "= TOP %lu =", lines.size());
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y + padY * 3, 3,
									  UtilAlign::CENTER);

	// Line
	for (auto line:lines) line->update(delay);
}

void RankingView::stepFireworks(const float delay) {

	// Fireworks
	if (fireInterval < fireCnt++) {
		fireCnt = 0;
		const int gSize = UtilDebug::getInstance()->getGridSize();
		int padX = gSize * 10;
		int x = pos.x - padX + UtilMath::getInstance()->getRandom(0, padX * 2);
		int y = pos.y - UtilMath::getInstance()->getRandom(gSize * 5, gSize * 10);
		float gY = gSize * 2;
		float bY = y + gSize * 20;
		Firework *fWork = Firework::create(x, y, gY, bY);
		fireworks.push_back(fWork);
	}
	for (auto firework : fireworks) firework->update(delay);// Fireworks
}

void RankingView::replaceScore() {
	if (replaceFlg) return;
	replaceFlg = true;
	// Score
	score += bonus * rateBonus;
	UtilLocalSave::getInstance()->setNum("score", score);
	// High
	if (high < score) {
		high = score;
		UtilLocalSave::getInstance()->setNum("high", high);
	}
}

void RankingView::startRankinEffect() {
	// Rankin or not
	if (rankinFlg) {
		// BGM
		UtilSound::getInstance()->stopBGM();
		UtilSound::getInstance()->playBGM("sounds/bgm_result_01.wav",
										  false, true);
	} else {
		// BGM
		UtilSound::getInstance()->stopBGM();
		UtilSound::getInstance()->playBGM("sounds/bgm_result_02.wav",
										  false, true);
	}
}

void RankingView::update(const float delay) {

	UtilLabel::getInstance()->drawStr("SCORE", pos.x, pos.y - padY * 1, 3,
									  UtilAlign::CENTER);

	// Score
	if (updateMode == SCORE) {
		this->stepScore(delay);
	}

	if (updateMode == BONUS) {
		this->stepBonus(delay);
	}

	if (updateMode == BLINK) {
		this->stepBlink(delay);
		this->stepRanking(delay);
		if (rankinFlg) this->stepFireworks(delay);
		this->replaceScore();// Replace
	}

	// Chicks
	for (auto chick:chicks) chick->update(delay);
}