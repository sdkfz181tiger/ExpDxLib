#include "Firework.h"

Firedot *Firedot::create(float x, float y, float vX, float vY,
						 float gY, float bY) {
	// New
	Firedot *sprite = new Firedot(x, y, vX, vY, gY, bY);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

Firedot::Firedot(float x, float y, float vX, float vY,
				 float gY, float bY) :
		pos(Vec2(x, y)), vel(Vec2(vX, vY)),
		gravityY(gY), borderY(bY),
		graph(-1), width(0), height(0),
		scale(UtilMath::getInstance()->getRandom(2, 4)) {
	//LOGD("Main", "Firedot()\n");
}

Firedot::~Firedot() {
	//LOGD("Main", "~Firedot()\n");
}

bool Firedot::init() {
	// Graph
	const vector<int> graphs = UtilGraph::getInstance()->getDivGraph("fc_01");
	const int index = UtilMath::getInstance()->getRandom(0, graphs.size() - 1);
	graph = graphs.at(index);
	GetGraphSize(graph, &width, &height);
	// Scale
	width *= scale;
	height *= scale;
	return true;
}

bool Firedot::isFinished() {
	return borderY < pos.y;
}

void Firedot::update(const float delay) {
	// Border
	if (this->isFinished()) return;
	// Gravity
	vel.y += gravityY;
	pos.x += vel.x * delay;
	pos.y += vel.y * delay;
	// Draw
	DrawExtendGraph(pos.x, pos.y, pos.x + width, pos.y + height,
					graph, true);
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
	for (int i = 0; i < 10; i++) {
		int deg = UtilMath::getInstance()->getRandom(210, 330);
		int speed = gSize * UtilMath::getInstance()->getRandom(12, 24);
		float vX = speed * UtilMath::getInstance()->getCos(deg);
		float vY = speed * UtilMath::getInstance()->getSin(deg);
		Firedot *dot = Firedot::create(pos.x, pos.y, vX, vY, gY, bY);
		dots.push_back(dot);
	}
	return true;
}

void Firework::update(const float delay) {
	// Update
	vector<Firedot *>::iterator it = dots.end();
	while (it-- != dots.begin()) {
		Firedot *dot = static_cast<Firedot *>(*it);
		dot->update(delay);
		if (!dot->isFinished()) continue;
		dots.erase(it);
		DX_SAFE_DELETE(dot);
	}
}