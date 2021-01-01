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
		color(GetColor(255, 255, 255)) {
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

void SpriteBase::setPosition(float pX, float pY) {
	pos.x = pX;
	pos.y = pY;
}

void SpriteBase::setPosX(float pX) {
	pos.x = pX;
}

void SpriteBase::setPosY(float pY) {
	pos.y = pY;
}

void SpriteBase::setVelocity(float vX, float vY) {
	vel.x = vX;
	vel.y = vY;
}

void SpriteBase::setVelX(float vX) {
	vel.x = vX;
}

void SpriteBase::setVelY(float vY) {
	vel.y = vY;
}

void SpriteBase::setScale(int scale) {
	this->scale = scale;
	this->width *= scale;
	this->height *= scale;
}

bool SpriteBase::containsPoint(int x, int y) {
	if (x < minX) return false;
	if (maxX < x) return false;
	if (y < minY) return false;
	if (maxY < y) return false;
	return true;
}

void SpriteBase::update(const float delay) {
	// Rect
	minX = pos.x - width / 2;
	maxX = pos.x + width / 2;
	minY = pos.y - height / 2;
	maxY = pos.y + height / 2;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
}