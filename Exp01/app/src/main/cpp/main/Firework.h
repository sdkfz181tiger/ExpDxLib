#ifndef _FIREWORK_H_
#define _FIREWORK_H_

#include "Utility.h"

class Firedot {

private:
	Vec2 pos, vel;
	int size;
	float gravityY, borderY;
	size_t color;

public:
	static Firedot *create(float x, float y, float vX, float vY,
						   int s, float gY, float bY);

	Firedot(float x, float y, float vX, float vY,
			int s, float gY, float bY);

	virtual ~Firedot();

	bool init();

	void update(const float delay);
};

class Firework {

private:
	Vec2 pos;
	vector<Firedot *> dots;

public:
	static Firework *create(float x, float y, float gY, float bY);

	Firework(float x, float y);

	virtual ~Firework();

	bool init(float gY, float bY);

	void update(const float delay);
};

#endif // _FIREWORK_H_