#ifndef _SPRITEBASE_H_
#define _SPRITEBASE_H_

#include "Utility.h"

class SpriteBase {

protected:
	Vec2 pos, vel;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;

private:
	bool moveFlg;
	int moveSpd, moveDeg;

public:
	static SpriteBase *createSprite(const string &fileName, float x, float y);

	SpriteBase(float x, float y);

	virtual ~SpriteBase();

	virtual bool init(const string &fileName);

	void setPos(const Vec2 &p);

	void setPosX(float x);

	void setPosY(float y);

	Vec2 &getPos() { return pos; }

	float getPosX() const { return pos.x; }

	float getPosY() const { return pos.y; }

	float getVX() const { return vel.x; }

	float getVY() const { return vel.y; }

	int getMinX() const { return minX; }

	int getMaxX() const { return maxX; }

	int getMinY() const { return minY; }

	int getMaxY() const { return maxY; }

	int getWidth() { return width; }

	int getHeight() { return height; }

	void setScale(int scl);

	int getScale() { return scale; }

	void move(int spd, int deg);

	void stop();

	void setMoveFlg(bool flg);

	bool getMoveFlg() { return moveFlg; }

	void setSpeed(int spd);

	int getSpeed() { return moveSpd; }

	void setDegree(int deg);

	int getDegree() { return moveDeg; }

	bool containsPos(const SpriteBase *tgt);

	virtual void update(const float delay);

	virtual void draw();
};

#endif // _SPRITEBASE_H_