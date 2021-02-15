#ifndef _RANKINGVIEW_H_
#define _RANKINGVIEW_H_

#include "Utility.h"
#include "SpriteChick.h"
#include "RankingLine.h"
#include "Firework.h"

class RankingView {

private:
	enum UpdateMode {
		SCORE, BONUS, BLINK
	};
	UpdateMode updateMode;

private:
	Vec2 pos;
	int padX, padY;
	bool rankinFlg;
	int counter;
	int score, bonus, high;
	int stpA, stpIntervalA;
	int stpB, stpIntervalB;
	int stpC, stpIntervalC;
	int rateBonus, blinkTimes;
	bool blinkFlg, replaceFlg;
	int fireCnt, fireInterval;
	vector<RankingLine *> lines;
	vector<SpriteChick *> chicks;
	vector<Firework *> fireworks;

public:
	static RankingView *createRanking(float x, float y, int pX, int pY);

	RankingView(float x, float y, int pX, int pY);

	virtual ~RankingView();

	bool init();

	void sortRanking();

	void stepScore(const float delay);

	void stepBonus(const float delay);

	void stepBlink(const float delay);

	void stepRanking(const float delay);

	void stepFireworks(const float delay);

	void replaceScore();

	void startRankinEffect();

	void update(const float delay);
};

#endif // _RANKINGVIEW_H_