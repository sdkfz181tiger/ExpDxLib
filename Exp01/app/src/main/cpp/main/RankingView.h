#ifndef _RANKINGVIEW_H_
#define _RANKINGVIEW_H_

#include "Utility.h"
#include "RankingLine.h"

class RankingView {

private:
	Vec2 pos;
	int padX, padY;
	int counter, progress;
	int cntScore, cntHigh;
	int blinkCnt, blinkInterval;
	int blinkTimes;
	bool blinkFlg;
	vector<RankingLine *> lines;

public:
	static RankingView *createRanking(float x, float y, int pX, int pY);

	RankingView(float x, float y, int pX, int pY);

	virtual ~RankingView();

	bool init();

	void sortRanking();

	void update(const float delay);
};

#endif // _RANKINGVIEW_H_