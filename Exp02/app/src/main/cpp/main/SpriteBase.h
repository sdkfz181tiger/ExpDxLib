#ifndef _SPRITEBASE_H_
#define _SPRITEBASE_H_

#include "Utility.h"

class SpriteBase {

protected:
	Vec2 pos, vel;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;

public:
	static SpriteBase *createSprite(const string &fileName, float x, float y);

	SpriteBase(float x, float y);

	virtual ~SpriteBase();

	bool init(const char *fileName);

	void setPosition(float x, float y);

	void setVelocity(float x, float y);

	void setScale(int scale);

	bool containsPoint(int x, int y);

	void update(const float delay);

	void draw();
};

#endif // _SPRITEBASE_H_