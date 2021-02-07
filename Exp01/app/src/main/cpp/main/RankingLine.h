#ifndef _RANKINGLINE_H_
#define _RANKINGLINE_H_

#include "Utility.h"
#include "SpriteChick.h"

class RankingLine {

private:
	Vec2 pos;
	int padX, waitCnt;
	json rank;
	SpriteChick *mkL;
	SpriteChick *mkR;

public:
	static RankingLine *createLine(float x, float y, int pX, int wC, json &r);

	RankingLine(float x, float y, int pX, int wC, json &r);

	virtual ~RankingLine();

	bool init();

	void update(const float delay);
};

#endif // _RANKINGLINE_H_