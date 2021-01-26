#ifndef _SPRITEKOBO_H_
#define _SPRITEKOBO_H_

#include "SpriteChara.h"

class SpriteKobo : public SpriteChara {

public:
	static SpriteKobo *createSprite(const string &fileName, float x, float y);

	SpriteKobo(float x, float y);

	virtual ~SpriteKobo();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;
};

#endif // _SPRITEKOBO_H_