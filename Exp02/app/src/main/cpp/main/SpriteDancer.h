#ifndef _SPRITEDANCER_H_
#define _SPRITEDANCER_H_

#include "SpriteFrames.h"

class SpriteDancer : public SpriteFrames {

public:
	static SpriteDancer *createSprite(const string &fileName, float x, float y);

	SpriteDancer(float x, float y);

	virtual ~SpriteDancer();

	virtual bool init(const string &fileName) override;
};

#endif // _SPRITEDANCER_H_