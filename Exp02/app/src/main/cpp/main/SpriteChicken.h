#ifndef _SPRITECHICKEN_H_
#define _SPRITECHICKEN_H_

#include "SpriteChara.h"

class SpriteChicken : public SpriteChara {

public:
	static SpriteChicken *createSprite(const string &fileName, float x, float y);

	SpriteChicken(float x, float y);

	virtual ~SpriteChicken();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITECHICKEN_H_