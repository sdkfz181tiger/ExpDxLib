#ifndef _SPRITEPLAYER_H_
#define _SPRITEPLAYER_H_

#include "SpriteMaze.h"

class StatePlayer : public StateMaze {
public:
	const static int DEAD = 999;
};

enum class StickPlayer {
	DEFAULT, LEFT, RIGHT, UP, DOWN
};

class SpritePlayer : public SpriteMaze {

private:
	int wanCnt, wanInterval;
	StickPlayer stkNow, stkNext;

public:
	static SpritePlayer *createSprite(const string &fileName, float x, float y);

	SpritePlayer(float x, float y);

	virtual ~SpritePlayer();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;

	void flickL();

	void flickR();

	void flickU();

	void flickD();

	void checkStick();

	void showStick();

	bool isDead();

	void startDead();
};

#endif // _SPRITEPLAYER_H_