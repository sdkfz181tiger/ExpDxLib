#ifndef _SPRITEENEMY_H_
#define _SPRITEENEMY_H_

#include "SpriteBase.h"

class SpriteEnemy : public SpriteBase {

protected:

public:
	static SpriteEnemy *createSprite(const string &fileName, float x, float y);

	SpriteEnemy(float x, float y);

	virtual ~SpriteEnemy();

	bool init(const string &fileName) override;
};

#endif // _SPRITEENEMY_H_