#ifndef _SPRITEDANCER_H_
#define _SPRITEDANCER_H_

#include "SpriteBase.h"

class SpriteDancer : public SpriteBase {

protected:

public:
	static SpriteDancer *createSprite(const string &fileName, float x, float y);

	SpriteDancer(float x, float y);

	virtual ~SpriteDancer();
};

#endif // _SPRITEDANCER_H_