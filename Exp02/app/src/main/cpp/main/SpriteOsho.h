#ifndef _SPRITEOSHO_H_
#define _SPRITEOSHO_H_

#include "SpriteChara.h"

class SpriteOsho : public SpriteChara {

public:
	static SpriteOsho *createSprite(const string &fileName, float x, float y);

	SpriteOsho(float x, float y);

	virtual ~SpriteOsho();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(StateChara sta) override;
};

#endif // _SPRITEOSHO_H_