#include "SpriteChara.h"

SpriteChara *SpriteChara::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChara *sprite = new SpriteChara(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChara::SpriteChara(float x, float y) : SpriteFrames(x, y),
											 state(StateChara::DEFAULT),
											 stayCnt(0), stayInterval(50),
											 idleCnt(0), idleInterval(300),
											 walkDst(Vec2(x, y)), walkLen(0.0f) {
	LOGD("Main", "SpriteChara()\n");
}

SpriteChara::~SpriteChara() {
	LOGD("Main", "~SpriteChara()\n");
}

bool SpriteChara::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Do something

	return true;
}

void SpriteChara::update(float delay) {
	// Do something
}

void SpriteChara::changeState(StateChara sta) {
	// Do something
}

void SpriteChara::startStay(){
	// Stay
	stayCnt = stayInterval;
	// Stop
	this->stop();
	walkDst.x = pos.x;
	walkDst.y = pos.y;
	walkLen = 0.0f;
	// State
	this->changeState(StateChara::STAY);
}

void SpriteChara::startIdle() {
	// Idle
	idleCnt = UtilMath::getInstance()->getRandom(idleInterval/2, idleInterval);
	// Stop
	this->stop();
	walkDst.x = pos.x;
	walkDst.y = pos.y;
	walkLen = 0.0f;
	// State
	this->changeState(StateChara::IDLE);
}

void SpriteChara::startWalk(int spd, int x, int y) {
	// Move
	this->move(spd, UtilMath::getInstance()->calcDeg2D(pos, Vec2(x, y)));
	walkDst.x = x;
	walkDst.y = y;
	walkLen = UtilMath::getInstance()->calcDistance2D(pos, Vec2(x, y));
	// State
	this->changeState(StateChara::WALK);
}