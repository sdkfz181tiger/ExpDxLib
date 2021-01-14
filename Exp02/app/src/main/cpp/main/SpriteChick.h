#ifndef _SPRITECHICK_H_
#define _SPRITECHICK_H_

#include "SpriteChara.h"

class SpriteChick : public SpriteChara {

public:
	static SpriteChick *createSprite(const string &fileName, float x, float y);

	SpriteChick(float x, float y);

	virtual ~SpriteChick();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITECHICK_H_