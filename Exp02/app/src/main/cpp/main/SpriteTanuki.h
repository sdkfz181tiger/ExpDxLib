#ifndef _SPRITETANUKI_H_
#define _SPRITETANUKI_H_

#include "SpriteFrames.h"

class SpriteTanuki : public SpriteFrames {

public:
	static SpriteTanuki *createSprite(const string &fileName, float x, float y);

	SpriteTanuki(float x, float y);

	virtual ~SpriteTanuki();

	virtual bool init(const string &fileName) override;
};

#endif // _SPRITETANUKI_H_