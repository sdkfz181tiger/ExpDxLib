#ifndef _UTILMATH_H_
#define _UTILMATH_H_

#include "Utility.h"

class UtilMath {

private:
	// Sin, Cos
	float sinTable[360];
	float cosTable[360];

	// Random
	random_device seed_gen;
	default_random_engine engine{seed_gen()};

public:
	UtilMath();

	~UtilMath();

	static UtilMath *getInstance();

	void destroyInstance();

	bool init();

	float calcDistance2D(const Vec2 &pointA, const Vec2 &pointB);

	float getSin(int num);

	float getCos(int num);

	// Degree(1Point)
	float calcDeg2D(const Vec2 &pivot, const Vec2 &pointA);

	// Degree(2Point)
	float calcDeg2P2D(const Vec2 &pivot, const Vec2 &pointA, const Vec2 &pointB);

	// Cross(A->B, C->D)
	Vec2 calcCross2Line(const Vec2 &vA, const Vec2 &vB, const Vec2 &vC, const Vec2 &vD);

	// Cross(A->B, C->D)
	bool checkCross2Line(const Vec2 &vA, const Vec2 &vB, const Vec2 &vC, const Vec2 &vD);

	// Is left side?
	bool isLeftSide(const Vec2 &pivot, const Vec2 &vA, const Vec2 &vB);

	// Is right side?
	bool isRightSide(const Vec2 &pivot, const Vec2 &vA, const Vec2 &vB);

	// Get reflection angle on lineA(vFrom <-> vTo) and lineB(wFrom <-> wTo)
	float calcDegReflection(const Vec2 &vFrom, const Vec2 &vTo,
	                        const Vec2 &wFrom, const Vec2 &wTo);

	// Random
	int getRandom(int min, int max);

	// Round
	int getRound(double num);
};

#endif // _UTILMATH_H_