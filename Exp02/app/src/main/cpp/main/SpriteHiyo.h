#ifndef _SPRITEHIYO_H_
#define _SPRITEHIYO_H_

#include "SpriteChara.h"

class SpriteHiyo : public SpriteChara {

public:
	static SpriteHiyo *createSprite(const string &fileName, float x, float y);

	SpriteHiyo(float x, float y);

	virtual ~SpriteHiyo();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITEHIYO_H_