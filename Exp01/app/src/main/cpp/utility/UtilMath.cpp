#include "UtilMath.h"

// Singleton Object
static UtilMath *selfUtilMath = nullptr;

UtilMath::UtilMath() {
	LOGD("Util", "UtiliMath()\n");
}

UtilMath::~UtilMath() {
	LOGD("Util", "~UtiliMath()\n");
}

UtilMath *UtilMath::getInstance() {

	if (!selfUtilMath) {
		selfUtilMath = new UtilMath();
		if (selfUtilMath && selfUtilMath->init()) {
			return selfUtilMath;
		} else {
			delete (selfUtilMath);
			selfUtilMath = nullptr;
		}
	}
	return selfUtilMath;
}

void UtilMath::destroyInstance() {
	if (!selfUtilMath) return;

	delete (selfUtilMath);
	selfUtilMath = nullptr;
}

bool UtilMath::init() {
	LOGD("Util", "UtilMath::init()\n");

	// Sin table
	for (int i = 0; i < 360; ++i) {
		float rad = sinf(i * DEG_TO_RAD);
		sinTable[i] = rad;
	}

	// Cos table
	for (int i = 0; i < 360; ++i) {
		float rad = cosf(i * DEG_TO_RAD);
		cosTable[i] = rad;
	}

	return true;
}

// distance
float UtilMath::calcDistance2D(const Vec2 &pointA, const Vec2 &pointB) {

	float distance = sqrt(powf(pointA.x - pointB.x, 2) + powf(pointA.y - pointB.y, 2));
	return distance;
}

float UtilMath::getSin(int num) {

	if (num >= 360) {
		num -= 360;
	}
	if (num < 0) {
		num += 360;
	}
	return sinTable[num];
}

float UtilMath::getCos(int num) {

	if (num >= 360) {
		num -= 360;
	}
	if (num < 0) {
		num += 360;
	}
	return cosTable[num];
}

float UtilMath::calcDeg2D(const Vec2 &pivot, const Vec2 &pointA) {

	// SamePoint
	if (pivot.x == pointA.x && pivot.y == pointA.y) {
		return 0.0f;
	}

	// Horizontal
	if (pivot.x == pointA.x) {
		if (pivot.y < pointA.y) {
			return 90.0f;
		} else {
			return 270.0f;
		}
	}

	// Vertical
	if (pivot.y == pointA.y) {
		if (pivot.x < pointA.x) {
			return 0.0f;
		} else {
			return 180.0f;
		}
	}

	float deg = atanf((pointA.y - pivot.y) / (pointA.x - pivot.x)) * RAD_TO_DEG;

	if (pointA.y > pivot.y && pointA.x > pivot.x) {
		// 1div
		// Do nothing
	} else if (pointA.y > pivot.y && pointA.x < pivot.x) {
		// 2div
		deg += 180.0f;
	} else if (pointA.y < pivot.y && pointA.x < pivot.x) {
		// 3div
		deg += 180.0f;
	} else {
		// 4div
		deg += 360.0f;
	}
	return deg;
}

float UtilMath::calcDeg2P2D(const Vec2 &pivot, const Vec2 &pointA, const Vec2 &pointB) {

	float degA = calcDeg2D(pivot, pointA);
	float degB = calcDeg2D(pivot, pointB);

	float deg = fabs(degA - degB);
	if (deg > 180.0f) {
		deg = 360.0f - deg;
	}
	return deg;
}

Vec2 UtilMath::calcCross2Line(const Vec2 &vA, const Vec2 &vB,
                              const Vec2 &vC, const Vec2 &vD) {

	if (!checkCross2Line(vA, vB, vC, vD)) return Vec2(0.0f, 0.0f);

	// C->A
	float radA = UtilMath::getInstance()->calcDistance2D(vC, vA);
	float degA = UtilMath::getInstance()->calcDeg2P2D(vC, vD, vA);
	float sinA = sinf(degA * DEG_TO_RAD);
	float distA = radA * sinA;

	// C->B
	float radB = UtilMath::getInstance()->calcDistance2D(vC, vB);
	float degB = UtilMath::getInstance()->calcDeg2P2D(vC, vD, vB);
	float sinB = sinf(degB * DEG_TO_RAD);
	float distB = radB * sinB;

	// Cross
	float x = vA.x + (vB.x - vA.x) * distA / (distA + distB);
	float y = vA.y + (vB.y - vA.y) * distA / (distA + distB);

	return Vec2(x, y);
}

bool UtilMath::checkCross2Line(const Vec2 &vA, const Vec2 &vB,
                               const Vec2 &vC, const Vec2 &vD) {

	float a = (vC.x - vD.x) * (vA.y - vC.y) + (vC.y - vD.y) * (vC.x - vA.x);
	float b = (vC.x - vD.x) * (vB.y - vC.y) + (vC.y - vD.y) * (vC.x - vB.x);
	float c = (vA.x - vB.x) * (vC.y - vA.y) + (vA.y - vB.y) * (vA.x - vC.x);
	float d = (vA.x - vB.x) * (vD.y - vA.y) + (vA.y - vB.y) * (vA.x - vD.x);
	return a * b < 0 && c * d < 0;
}

bool UtilMath::isLeftSide(const Vec2 &pivot, const Vec2 &vA, const Vec2 &vB) {

	const Vec2 w = vA - pivot;
	float radV = atan2f(w.y, w.x) + PI * 0.5f;
	const Vec2 v = Vec2(pivot.x + cosf(radV),
	                    pivot.y + sinf(radV)) - pivot;
	const Vec2 l = vB - pivot;
	float dot = v.x * l.x + v.y * l.y;
	if (0 < dot) return true;
	return false;
}

bool UtilMath::isRightSide(const Vec2 &pivot, const Vec2 &vA, const Vec2 &vB) {

	const Vec2 w = vA - pivot;
	float radV = atan2f(w.y, w.x) + PI * 0.5f;
	const Vec2 v = Vec2(pivot.x + cosf(radV),
	                    pivot.y + sinf(radV)) - pivot;
	const Vec2 l = vB - pivot;
	float dot = v.x * l.x + v.y * l.y;
	if (dot < 0) return true;
	return false;
}

float UtilMath::calcDegReflection(const Vec2 &vFrom, const Vec2 &vTo,
                                  const Vec2 &wFrom, const Vec2 &wTo) {

	const Vec2 c = calcCross2Line(wFrom, wTo, vFrom, vTo);
	float distance = calcDistance2D(vTo, c);
	const Vec2 w = wTo - wFrom;
	float radV = atan2f(w.y, w.x) + PI * 0.5f;
	const Vec2 v = Vec2(c.x + distance * cosf(radV), c.y + distance * sinf(radV)) - c;
	const Vec2 p = vFrom - c;
	float radD = v.radian(p);
	float radR = radV - radD;
	return radR * RAD_TO_DEG;
}

int UtilMath::getRandom(int min, int max) {

	uniform_int_distribution<int> dist(min, max);
	int rdm = dist(engine);
	return rdm;
}

int UtilMath::getRound(double num) {
	return round(num);
}