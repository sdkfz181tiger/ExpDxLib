#ifndef _SPRITEBASE_H_
#define _SPRITEBASE_H_

#include "Utility.h"

class SpriteBase {

protected:
	Vec2 pos, vel;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;
	unsigned int color;

public:
	SpriteBase(float x, float y);

	virtual ~SpriteBase();

	bool initGraph(const string &fileName);

	bool initDivGraph(const string &fileName);

	void setPosition(float pX, float pY);

	void setPosX(float pX);

	void setPosY(float pY);

	float getPosX() const { return pos.x; }

	float getPosY() const { return pos.y; }

	void setVelocity(float vX, float vY);

	void setVelX(float vX);

	void setVelY(float vY);

	float getVelX() const { return vel.x; }

	float getVelY() const { return vel.y; }

	void setScale(int scale);

	float getScale() const { return scale; }

	bool containsPoint(int x, int y);

	void update(const float delay);
};

#endif // _SPRITEBASE_H_