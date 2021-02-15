#include "Firework.h"

Firedot *Firedot::create(float x, float y, float vX, float vY,
						 int s, float gY, float bY) {
	// New
	Firedot *sprite = new Firedot(x, y, vX, vY, s, gY, bY);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

Firedot::Firedot(float x, float y, float vX, float vY,
				 int s, float gY, float bY) :
		pos(Vec2(x, y)), vel(Vec2(vX, vY)), size(s),
		gravityY(gY), borderY(bY),
		color(GetColor(255, 255, 255)) {
	LOGD("Main", "Firedot()\n");
}

Firedot::~Firedot() {
	LOGD("Main", "~Firedot()\n");
}

bool Firedot::init() {
	return true;
}

void Firedot::update(const float delay) {
	// Border
	if (borderY < pos.y) return;
	// Gravity
	vel.y += gravityY;
	pos.x += vel.x * delay;
	pos.y += vel.y * delay;
	// Draw
	DrawBox(pos.x, pos.y, pos.x + size, pos.y + size, color, true);
}

Firework *Firework::create(float x, float y, float gY, float bY) {
	// New
	Firework *sprite = new Firework(x, y);
	if (sprite && sprite->init(gY, bY)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

Firework::Firework(float x, float y) : pos(Vec2(x, y)) {
	LOGD("Main", "Firework()\n");
}

Firework::~Firework() {
	LOGD("Main", "~Firework()\n");
	DX_SAFE_DELETE_VECTOR(dots);
}

bool Firework::init(float gY, float bY) {

	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Dots
	for (int i = 0; i < 20; i++) {
		int deg = UtilMath::getInstance()->getRandom(210, 330);
		int speed = gSize * UtilMath::getInstance()->getRandom(12, 24);
		float vX = speed * UtilMath::getInstance()->getCos(deg);
		float vY = speed * UtilMath::getInstance()->getSin(deg);
		int size = UtilMath::getInstance()->getRandom(gSize / 2, gSize);
		Firedot *dot = Firedot::create(pos.x, pos.y, vX, vY, size, gY, bY);
		dots.push_back(dot);
	}
	return true;
}

void Firework::update(const float delay) {
	// Update
	for (auto dot : dots) dot->update(delay);
}