#ifndef _RANKINGVIEW_H_
#define _RANKINGVIEW_H_

#include "Utility.h"
#include "SpriteChick.h"
#include "RankingLine.h"

class RankingView {

private:
	enum UpdateMode {
		SCORE, BONUS, BLINK
	};
	UpdateMode updateMode;

private:
	Vec2 pos;
	int padX, padY;
	int counter;
	int cntScore, cntBonus, cntHigh;
	int stpA, stpIntervalA;
	int stpB, stpIntervalB;
	int stpC, stpIntervalC;
	int rateBonus, blinkTimes;
	bool blinkFlg, replaceFlg;
	vector<RankingLine *> lines;
	vector<SpriteChick *> chicks;

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

	void replaceScore();

	void update(const float delay);
};

#endif // _RANKINGVIEW_H_