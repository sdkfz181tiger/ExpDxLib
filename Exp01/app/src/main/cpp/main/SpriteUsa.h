#ifndef _SPRITEUSA_H_
#define _SPRITEUSA_H_

#include "SpriteMaze.h"

class StateUsa : public StateMaze {
public:
	const static int WANDER = 101;
};

enum class Stick {
	DEFAULT, LEFT, RIGHT, UP, DOWN
};

class SpriteUsa : public SpriteMaze {

private:
	int wanCnt, wanInterval;
	Stick stkNow, stkNext;

public:
	static SpriteUsa *createSprite(const string &fileName, float x, float y);

	SpriteUsa(float x, float y);

	virtual ~SpriteUsa();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;

	void flickL();

	void flickR();

	void flickU();

	void flickD();

	void checkStick();

	void showStick();
};

#endif // _SPRITEUSA_H_