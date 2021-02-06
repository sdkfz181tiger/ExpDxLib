#ifndef _RANKINGLINE_H_
#define _RANKINGLINE_H_

#include "Utility.h"

struct Rank {
	bool icon;
	int num;
	int score;
	int hiyoko;
	string name;
};

class RankingLine {

private:
	Vec2 pos;
	int padX, waitCnt;
	Rank rank;

public:
	static RankingLine *createLine(float x, float y, int pX, int wC, Rank &r);

	RankingLine(float x, float y, int pX, int wC, Rank &r);

	virtual ~RankingLine();

	bool init();

	void update(const float delay);
};

#endif // _RANKINGLINE_H_