#ifndef _SPRITETANUKI_H_
#define _SPRITETANUKI_H_

#include "SpriteChara.h"

class SpriteTanuki : public SpriteChara {

public:
	static SpriteTanuki *createSprite(const string &fileName, float x, float y);

	SpriteTanuki(float x, float y);

	virtual ~SpriteTanuki();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITETANUKI_H_