#include "SpriteBase.h"

SpriteBase *SpriteBase::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteBase *sprite = new SpriteBase(x, y);
	if (sprite && sprite->init(fileName.c_str())) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteBase::SpriteBase(float x, float y) :
		pos(Vec2(x, y)), vel(Vec2(0, 0)),
		graph(0), width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0) {
	LOGD("Main", "SpriteBase()\n");
}

SpriteBase::~SpriteBase() {
	LOGD("Main", "~SpriteBase()\n");
}

bool SpriteBase::init(const char *fileName) {
	// Load graph
	graph = LoadGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	return true;
}

void SpriteBase::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void SpriteBase::setVelocity(float x, float y) {
	vel.x = x;
	vel.y = y;
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
	// Velocity
	pos.x += vel.x * delay;
	pos.y += vel.y * delay;
	// Rect
	minX = pos.x - width * 0.5f;
	maxX = pos.x + width * 0.5f;
	minY = pos.y - height * 0.5f;
	maxY = pos.y + height * 0.5f;
	// Draw
	int color = GetColor(255, 255, 255);
	DrawBox(minX, minY, maxX, maxY, color, false);
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
}