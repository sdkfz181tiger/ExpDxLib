#include "SpriteChara.h"

SpriteChara *SpriteChara::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChara *sprite = new SpriteChara(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChara::SpriteChara(float x, float y) : SpriteFrames(x, y),
											 type(TypeChara::DEFAULT),
											 state(StateChara::DEFAULT),
											 stayCnt(0), stayInterval(10),
											 idleCnt(0), idleInterval(60),
											 walkDst(Vec2(x, y)), walkLen(0.0f),
											 walkFlg(false) {
	//LOGD("Main", "SpriteChara()\n");
}

SpriteChara::~SpriteChara() {
	//LOGD("Main", "~SpriteChara()\n");
}

bool SpriteChara::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;
	// Do something
	return true;
}

void SpriteChara::update(float delay) {
	// Do something
}

void SpriteChara::setType(int typ) {
	type = typ;
}

int SpriteChara::getType() const {
	return type;
}

void SpriteChara::changeState(int sta) {
	// State
	if (state == sta) return;
	state = sta;
	// Do something
}

void SpriteChara::showState() {
	// State
	char c[10];
	sprintf(c, "%d", static_cast<int>(state));
	UtilLabel::getInstance()->drawStr(c, pos.x, pos.y - height / 2,
									  2, UtilAlign::CENTER);
}

void SpriteChara::startStay() {
	// Stay
	stayCnt = stayInterval;
	// Stop
	this->stop();
	walkDst.x = pos.x;
	walkDst.y = pos.y;
	walkLen = 0.0f;
	walkFlg = false;
	// State
	this->changeState(StateChara::STAY);
}

void SpriteChara::startIdle() {
	// Idle
	idleCnt = UtilMath::getInstance()->getRandom(idleInterval / 2, idleInterval);
	// Stop
	this->stop();
	walkDst.x = pos.x;
	walkDst.y = pos.y;
	walkLen = 0.0f;
	walkFlg = false;
	// State
	this->changeState(StateChara::IDLE);
}

void SpriteChara::startWalkDst(int spd, int x, int y, bool flg) {
	// Move
	this->move(spd, UtilMath::getInstance()->calcDeg2D(pos, Vec2(x, y)));
	walkDst.x = x;
	walkDst.y = y;
	walkLen = UtilMath::getInstance()->calcDistance2D(pos, Vec2(x, y));
	walkFlg = flg;
	// State
	this->changeState(StateChara::WALK);
}

void SpriteChara::startWalkDir(int spd, int deg, bool flg) {
	// Move
	this->move(spd, deg);
	walkDst.x = pos.x;
	walkDst.y = pos.y;
	walkLen = 256;
	walkFlg = flg;
	// State
	this->changeState(StateChara::WALK);
}