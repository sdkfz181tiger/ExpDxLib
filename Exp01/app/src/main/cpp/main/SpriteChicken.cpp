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
	this->pushFrames("chicken_f_f");
	this->pushFrames("chicken_f_b");
	this->pushFrames("chicken_f_r");
	this->pushFrames("chicken_f_l");
	this->pushFrames("chicken_f_d");
	this->pushFrames("chicken_f_i1");
	this->pushFrames("chicken_f_i2");
	this->pushFrames("chicken_f_i3");
	this->pushFrames("chicken_f_i4");

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
			this->startStay();
		}
	}
	// Walk
	if (state == StateChara::WALK) {
		if (this->getMoveFlg()) {
			pos.x += vel.x * delay;
			pos.y += vel.y * delay;
			if (!walkFlg) {
				walkLen -= this->getSpeed() * delay;
				if (walkLen <= 0.0f) this->startStay();
			}
		}
	}
	// Draw
	this->draw();
}

void SpriteChicken::changeState(int sta) {
	// State
	if (state == sta) return;
	state = sta;

	if (state == StateChara::STAY) {
		//LOGD("Main", "Let's stay!!");
		// Frames
		this->pauseFrames();
		return;
	}
	if (state == StateChara::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		vector <string> frames = {"chicken_f_i1", "chicken_f_i2", "chicken_f_i3", "chicken_f_i4"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		//LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("chicken_f_r", -1);
		} else if (deg < 135) {
			this->changeFrames("chicken_f_f", -1);
		} else if (deg < 225) {
			this->changeFrames("chicken_f_l", -1);
		} else if (deg < 315) {
			this->changeFrames("chicken_f_b", -1);
		} else {
			this->changeFrames("chicken_f_r", -1);
		}
		return;
	}
}