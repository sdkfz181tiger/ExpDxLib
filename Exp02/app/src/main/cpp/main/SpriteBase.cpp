#include "SpriteBase.h"

SpriteBase *SpriteBase::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteBase *sprite = new SpriteBase(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteBase::SpriteBase(float x, float y) :
		pos(Vec2(x, y)), vel(Vec2(0, 0)),
		graph(0), width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0),
		moveFlg(false), moveSpd(0), moveDeg(0) {
	LOGD("Main", "SpriteBase()\n");
}

SpriteBase::~SpriteBase() {
	LOGD("Main", "~SpriteBase()\n");
}

bool SpriteBase::init(const string &fileName) {
	// Load graph
	graph = UtilGraph::getInstance()->getGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	return true;
}

void SpriteBase::setPosX(float x) {
	pos.x = x;
}

void SpriteBase::setPosY(float y) {
	pos.y = y;
}

void SpriteBase::setScale(int scl) {
	width *= scl;
	height *= scl;
	scale = scl;
}

void SpriteBase::move(int spd, int deg) {
	moveFlg = true;
	moveSpd = spd;
	moveDeg = deg;
	vel.x = moveSpd * UtilMath::getInstance()->getCos(moveDeg);
	vel.y = moveSpd * UtilMath::getInstance()->getSin(moveDeg);
}

void SpriteBase::stop() {
	moveFlg = false;
	moveSpd = 0;
	moveDeg = 0;
	vel.x = 0.0f;
	vel.y = 0.0f;
}

bool SpriteBase::containsPoint(int x, int y) {
	if (x < minX) return false;
	if (maxX < x) return false;
	if (y < minY) return false;
	if (maxY < y) return false;
	return true;
}

void SpriteBase::update(const float delay) {
	// Move
	if (moveFlg) {
		pos.x += vel.x * delay;
		pos.y += vel.y * delay;
	}
	// Draw
	this->draw();
}

void SpriteBase::draw() {
	// Rect
	minX = pos.x - width / 2;
	maxX = pos.x + width / 2;
	minY = pos.y - height / 2;
	maxY = pos.y + height / 2;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
}