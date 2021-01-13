#include "SpriteHiyo.h"

SpriteHiyo *SpriteHiyo::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteHiyo *sprite = new SpriteHiyo(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteHiyo::SpriteHiyo(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteHiyo()\n");
}

SpriteHiyo::~SpriteHiyo() {
	LOGD("Main", "~SpriteHiyo()\n");
}

bool SpriteHiyo::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("hiyo_f");
	this->pushFrames("hiyo_b");
	this->pushFrames("hiyo_r");
	this->pushFrames("hiyo_l");
	this->pushFrames("hiyo_d");

	this->startIdle();// Idle

	return true;
}

void SpriteHiyo::update(float delay) {
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

void SpriteHiyo::changeState(StateChara sta) {
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
		vector<string> frames = {"hiyo_f", "hiyo_b", "hiyo_r", "hiyo_l"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		//LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("hiyo_r", -1);
		} else if (deg < 135) {
			this->changeFrames("hiyo_f", -1);
		} else if (deg < 225) {
			this->changeFrames("hiyo_l", -1);
		} else if (deg < 315) {
			this->changeFrames("hiyo_b", -1);
		} else {
			this->changeFrames("hiyo_r", -1);
		}
		return;
	}
}