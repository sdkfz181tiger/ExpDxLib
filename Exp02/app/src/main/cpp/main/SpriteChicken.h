#ifndef _SPRITECHICKEN_H_
#define _SPRITECHICKEN_H_

#include "SpriteFrames.h"

class SpriteChicken : public SpriteFrames {

public:
	static SpriteChicken *createSprite(const string &fileName, float x, float y);

	SpriteChicken(float x, float y);

	virtual ~SpriteChicken();

	virtual bool init(const string &fileName) override;
};

#endif // _SPRITECHICKEN_H_