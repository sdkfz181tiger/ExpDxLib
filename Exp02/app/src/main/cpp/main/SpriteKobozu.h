#ifndef _SPRITEKOBOZU_H_
#define _SPRITEKOBOZU_H_

#include "SpriteChara.h"

class SpriteKobozu : public SpriteChara {

public:
	static SpriteKobozu *createSprite(const string &fileName, float x, float y);

	SpriteKobozu(float x, float y);

	virtual ~SpriteKobozu();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITEKOBOZU_H_