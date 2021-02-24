#ifndef _SPRITEOSHO_H_
#define _SPRITEOSHO_H_

#include "SpriteMaze.h"

class StateOsho : public StateMaze {
public:
	const static int FOLLOWWAY = 2021;
	const static int FOLLOWNEXT = 2022;
};

class SpriteOsho : public SpriteMaze {

public:
	static SpriteOsho *createSprite(const string &fileName, float x, float y);

	SpriteOsho(float x, float y);

	virtual ~SpriteOsho();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;
};

#endif // _SPRITEOSHO_H_