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
											 idleCnt(0), idleInterval(300),
											 walkDst(Vec2(x, y)), walkLen(0.0f) {
	LOGD("Main", "SpriteChara()\n");
}

SpriteChara::~SpriteChara() {
	LOGD("Main", "~SpriteChara()\n");
}

bool SpriteChara::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("chi_f");
	this->pushFrames("chi_b");
	this->pushFrames("chi_r");
	this->pushFrames("chi_l");
	this->pushFrames("chi_d");

	this->startIdle();// Idle

	return true;
}

void SpriteChara::update(float delay) {
	// Idle
	if (state == StateChara::IDLE) {
		if (0 < idleCnt) {
			idleCnt--;
		} else {
			this->startIdle();
		}
	}
	// Walk
	if (state == StateChara::WALK) {
		if (this->getMoveFlg()) {
			pos.x += vel.x * delay;
			pos.y += vel.y * delay;
			walkLen -= this->getSpeed() * delay;
			if (walkLen <= 0.0f) this->startIdle();
		}
	}
	// Draw
	this->draw();
}

void SpriteChara::changeState(StateChara sta) {
	// State
	state = sta;
	if (state == StateChara::IDLE) {
		LOGD("Main", "Let's idle!!");
		idleCnt = idleInterval;
		// Frames
		vector<string> frames = {"chi_f", "chi_r", "chi_l", "chi_b"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("chi_r", -1);
		} else if (deg < 135) {
			this->changeFrames("chi_f", -1);
		} else if (deg < 225) {
			this->changeFrames("chi_l", -1);
		} else if (deg < 315) {
			this->changeFrames("chi_b", -1);
		} else {
			this->changeFrames("chi_r", -1);
		}
		return;
	}
}

void SpriteChara::startIdle() {
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