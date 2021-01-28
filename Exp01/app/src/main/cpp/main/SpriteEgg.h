#ifndef _SPRITEEGG_H_
#define _SPRITEEGG_H_

#include "SpriteChara.h"

class SpriteEgg : public SpriteChara {

public:
	static SpriteEgg *createSprite(const string &fileName, float x, float y);

	SpriteEgg(float x, float y);

	virtual ~SpriteEgg();

	bool init(const string &fileName) override;

	void update(const float delay) override;
};

#endif // _SPRITEEGG_H_