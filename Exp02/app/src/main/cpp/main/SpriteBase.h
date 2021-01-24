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

	void setPosX(float x);

	void setPosY(float y);

	float getPosX() const { return pos.x; }

	float getPosY() const { return pos.y; }

	int getWidth() { return width; }

	int getHeight() { return height; }

	void setScale(int scl);

	void move(int spd, int deg);

	void stop();

	void setMoveFlg(bool flg);

	bool getMoveFlg() { return moveFlg; }

	void setSpeed(int spd);

	int getSpeed() { return moveSpd; }

	void setDegree(int deg);

	int getDegree() { return moveDeg; }

	bool containsPoint(int x, int y);

	virtual void update(const float delay);

	virtual void draw();
};

#endif // _SPRITEBASE_H_