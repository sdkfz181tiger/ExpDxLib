#ifndef _SPRITEITEM_H_
#define _SPRITEITEM_H_

#include "SpriteChara.h"

class SpriteItem : public SpriteChara {

public:
	static SpriteItem *createSprite(const string &fileName, float x, float y);

	SpriteItem(float x, float y);

	virtual ~SpriteItem();

	bool init(const string &fileName) override;

	void update(const float delay) override;
};

#endif // _SPRITEITEM_H_