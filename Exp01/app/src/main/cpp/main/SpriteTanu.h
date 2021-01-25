#ifndef _SPRITETANU_H_
#define _SPRITETANU_H_

#include "SpriteChara.h"

class SpriteTanu : public SpriteChara {

public:
	static SpriteTanu *createSprite(const string &fileName, float x, float y);

	SpriteTanu(float x, float y);

	virtual ~SpriteTanu();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITETANU_H_