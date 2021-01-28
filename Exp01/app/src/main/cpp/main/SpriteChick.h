#ifndef _SPRITECHICK_H_
#define _SPRITECHICK_H_

#include "SpriteChara.h"

class SpriteChick : public SpriteChara {

private:
	SpriteBase *target;
	list<Vec2> footprints;

public:
	static SpriteChick *createSprite(const string &fileName, float x, float y);

	SpriteChick(float x, float y);

	virtual ~SpriteChick();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void checkFootprints();

	void setTarget(SpriteBase *tgt);
};

#endif // _SPRITECHICK_H_