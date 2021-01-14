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
	this->pushFrames("chi_m_f");
	this->pushFrames("chi_m_b");
	this->pushFrames("chi_m_r");
	this->pushFrames("chi_m_l");
	this->pushFrames("chi_m_d");
	this->pushFrames("chi_m_i1");
	this->pushFrames("chi_m_i2");
	this->pushFrames("chi_m_i3");
	this->pushFrames("chi_m_i4");

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
			if (!walkFlg) {
				walkLen -= this->getSpeed() * delay;
				if (walkLen <= 0.0f) this->startStay();
			}
		}
	}
	// Draw
	this->draw();
}

void SpriteChicken::changeState(StateChara sta) {
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
		vector<string> frames = {"chi_m_i1", "chi_m_i2", "chi_m_i3", "chi_m_i4"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		//LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("chi_m_r", -1);
		} else if (deg < 135) {
			this->changeFrames("chi_m_f", -1);
		} else if (deg < 225) {
			this->changeFrames("chi_m_l", -1);
		} else if (deg < 315) {
			this->changeFrames("chi_m_b", -1);
		} else {
			this->changeFrames("chi_m_r", -1);
		}
		return;
	}
}