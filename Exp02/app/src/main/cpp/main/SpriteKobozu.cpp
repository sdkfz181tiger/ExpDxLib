#include "SpriteKobozu.h"

SpriteKobozu *SpriteKobozu::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteKobozu *sprite = new SpriteKobozu(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteKobozu::SpriteKobozu(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteKobozu()\n");
}

SpriteKobozu::~SpriteKobozu() {
	LOGD("Main", "~SpriteKobozu()\n");
}

bool SpriteKobozu::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("kobo_f");
	this->pushFrames("kobo_b");
	this->pushFrames("kobo_r");
	this->pushFrames("kobo_l");
	this->pushFrames("kobo_d");

	this->startIdle();// Idle

	return true;
}

void SpriteKobozu::update(float delay) {
	// Stay
	if (state == StateChara::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			//this->startIdle();
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

void SpriteKobozu::changeState(StateChara sta) {
	// State
	state = sta;
	if (state == StateChara::STAY) {
		//LOGD("Main", "Let's stay!!");
		this->stopFrames();
		return;
	}
	if (state == StateChara::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		vector<string> frames = {"kobo_f", "kobo_r", "kobo_l", "kobo_b"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		//LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("kobo_r", -1);
		} else if (deg < 135) {
			this->changeFrames("kobo_f", -1);
		} else if (deg < 225) {
			this->changeFrames("kobo_l", -1);
		} else if (deg < 315) {
			this->changeFrames("kobo_b", -1);
		} else {
			this->changeFrames("kobo_r", -1);
		}
		return;
	}
}