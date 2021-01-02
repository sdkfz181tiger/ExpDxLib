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
		moveFlg(false), moveSpd(0), moveDeg(0),
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

void SpriteBase::setScale(int scale) {
	this->width *= scale;
	this->height *= scale;
	this->scale = scale;
}

void SpriteBase::move(int spd, int deg) {
	moveFlg = true;
	this->setSpeed(spd);
	this->setDegree(deg);
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

void SpriteBase::setSpeed(int spd) {
	moveSpd = spd;
}

void SpriteBase::setDegree(int deg) {
	moveDeg = deg;
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