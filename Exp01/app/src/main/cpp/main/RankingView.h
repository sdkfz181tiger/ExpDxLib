#ifndef _RANKINGVIEW_H_
#define _RANKINGVIEW_H_

#include "Utility.h"
#include "SpriteChick.h"
#include "RankingLine.h"

class RankingView {

private:
	Vec2 pos;
	int padX, padY;
	int counter;
	int cntScore, cntBonus, cntHigh;
	int stpA, stpIntervalA;
	int stpB, stpIntervalB;
	int stpC, stpIntervalC;
	int blinkTimes;
	bool blinkFlg;
	vector<SpriteChick *> chicks;
	vector<RankingLine *> lines;

public:
	static RankingView *createRanking(float x, float y, int pX, int pY);

	RankingView(float x, float y, int pX, int pY);

	virtual ~RankingView();

	bool init();

	void sortRanking();

	void stepScore(const float delay);

	void stepBonus(const float delay);

	void stepBlink(const float delay);

	void progressRanking(const float delay);

	void update(const float delay);
};

#endif // _RANKINGVIEW_H_