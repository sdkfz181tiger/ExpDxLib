#ifndef _SPRITEBOZU_H_
#define _SPRITEBOZU_H_

#include "SpriteFrames.h"

class SpriteBozu : public SpriteFrames {

public:
	static SpriteBozu *createSprite(const string &fileName, float x, float y);

	SpriteBozu(float x, float y);

	virtual ~SpriteBozu();

	virtual bool init(const string &fileName) override;
};

#endif // _SPRITEBOZU_H_