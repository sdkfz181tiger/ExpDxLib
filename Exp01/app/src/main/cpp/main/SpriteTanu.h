#ifndef _SPRITETANU_H_
#define _SPRITETANU_H_

#include "SpriteMaze.h"
#include "SpriteChick.h"
#include "SpriteEgg.h"

class StateTanu : public StateMaze {
public:
	const static int WANDER = 101;
	const static int CAPTURED = 102;
	const static int ESCAPE = 103;
	const static int RELEASE = 104;
	const static int SLEEP = 105;
};

class SpriteTanu : public SpriteMaze {

private:
	int wanCnt, wanInterval;
	int capCnt, capInterval;
	int escCnt, escInterval;
	int relCnt, relInterval;
	int slpCnt, slpInterval;
	bool eggFlg, chickFlg;
	SpriteEgg *egg;
	SpriteChick *chick;

public:
	static SpriteTanu *createSprite(const string &fileName, float x, float y);

	SpriteTanu(float x, float y);

	virtual ~SpriteTanu();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;

	void startWander();

	void startCapture(bool egg, bool chick);

	void startEscape();

	void startRelease();

	void startSleep();

	bool getItemFlg();
};

#endif // _SPRITETANU_H_