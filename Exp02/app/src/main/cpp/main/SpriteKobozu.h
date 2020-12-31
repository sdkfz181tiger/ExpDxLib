#ifndef _SPRITEKOBOZU_H_
#define _SPRITEKOBOZU_H_

#include "SpriteFrames.h"

class SpriteKobozu : public SpriteFrames {

public:
	static SpriteKobozu *createSprite(const string &fileName, float x, float y);

	SpriteKobozu(float x, float y);

	virtual ~SpriteKobozu();

	virtual bool init(const string &fileName) override;
};

#endif // _SPRITEKOBOZU_H_