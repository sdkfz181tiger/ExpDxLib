#include "SpriteChicken.h"

SpriteChicken *SpriteChicken::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChicken *sprite = new SpriteChicken(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChicken::SpriteChicken(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteChicken()\n");
}

SpriteChicken::~SpriteChicken() {
	LOGD("Main", "~SpriteChicken()\n");
}

bool SpriteChicken::init(const string &fileName) {
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
void SpriteChicken::update(float delay) {
	// Stay
	if (state == StateChara::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			this->startIdle();
		}
	}
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
			if (walkLen <= 0.0f) this->startStay();
		}
	}
	// Draw
	this->draw();
}

void SpriteChicken::changeState(StateChara sta) {
	// State
	state = sta;
	if (state == StateChara::STAY) {
		LOGD("Main", "Let's stay!!");
		this->stopFrames();
		return;
	}
	if (state == StateChara::IDLE) {
		LOGD("Main", "Let's idle!!");
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