#ifndef _SPRITEBASE_H_
#define _SPRITEBASE_H_

#include "Utility.h"

class SpriteBase {

protected:
	Vec2 pos, vel;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;
	bool moveFlg;
	int speed, degree;
	unsigned int color;

public:
	static SpriteBase *createSprite(const string &fileName, float x, float y);

	SpriteBase(float x, float y);

	virtual ~SpriteBase();

	virtual bool init(const string &fileName);

	void setPosition(float pX, float pY);

	void setPosX(float pX);

	void setPosY(float pY);

	float getPosX() const { return pos.x; }

	float getPosY() const { return pos.y; }

	const Vec2 &getPos() { return pos; }

	const Vec2 &getVel() { return vel; }

	int getWidth() { return width; }

	int getHeight() { return height; }

	void setScale(int scale);

	float getScale() const { return scale; }

	void move(int spd, int deg);

	void stop();

	void setSpeed(int spd);

	void setDegree(int deg);

	int getSpeed() { return speed; }

	int getDegree() { return degree; }

	bool containsPoint(int x, int y);

	virtual void update(const float delay);

	virtual void draw();
};

#endif // _SPRITEBASE_H_