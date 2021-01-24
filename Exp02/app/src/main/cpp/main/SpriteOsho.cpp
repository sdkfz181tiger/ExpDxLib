#include "SpriteOsho.h"

SpriteOsho *SpriteOsho::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteOsho *sprite = new SpriteOsho(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteOsho::SpriteOsho(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteOsho()\n");
}

SpriteOsho::~SpriteOsho() {
	LOGD("Main", "~SpriteOsho()\n");
}

bool SpriteOsho::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("osho_f");
	this->pushFrames("osho_b");
	this->pushFrames("osho_r");
	this->pushFrames("osho_l");
	this->pushFrames("osho_d");

	this->startIdle();// Idle

	return true;
}

void SpriteOsho::update(float delay) {
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
			if (!walkFlg) {
				walkLen -= this->getSpeed() * delay;
				if (walkLen <= 0.0f) this->startStay();
			}
		}
	}
	// Draw
	this->draw();
}

void SpriteOsho::changeState(StateChara sta) {
	// State
	state = sta;
	if (state == StateChara::STAY) {
		//LOGD("Main", "Let's stay!!");
		this->pauseFrames();
		return;
	}
	if (state == StateChara::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		vector<string> frames = {"osho_f", "osho_r", "osho_l", "osho_b"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		//LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("osho_r", -1);
		} else if (deg < 135) {
			this->changeFrames("osho_f", -1);
		} else if (deg < 225) {
			this->changeFrames("osho_l", -1);
		} else if (deg < 315) {
			this->changeFrames("osho_b", -1);
		} else {
			this->changeFrames("osho_r", -1);
		}
		return;
	}
}