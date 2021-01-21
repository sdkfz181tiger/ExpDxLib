#include "SpriteTanu.h"

SpriteTanu *SpriteTanu::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteTanu *sprite = new SpriteTanu(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteTanu::SpriteTanu(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteTanu()\n");
}

SpriteTanu::~SpriteTanu() {
	LOGD("Main", "~SpriteTanu()\n");
}

bool SpriteTanu::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("tanu_f");
	this->pushFrames("tanu_b");
	this->pushFrames("tanu_r");
	this->pushFrames("tanu_l");
	this->pushFrames("tanu_d");

	this->startIdle();// Idle

	return true;
}

void SpriteTanu::update(float delay) {
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

void SpriteTanu::changeState(StateChara sta) {
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
		vector<string> frames = {"tanu_f", "tanu_r", "tanu_l", "tanu_b"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChara::WALK) {
		//LOGD("Main", "Let's walk!!");
		// Frames
		int deg = this->getDegree();
		if (deg < 45) {
			this->changeFrames("tanu_r", -1);
		} else if (deg < 135) {
			this->changeFrames("tanu_f", -1);
		} else if (deg < 225) {
			this->changeFrames("tanu_l", -1);
		} else if (deg < 315) {
			this->changeFrames("tanu_b", -1);
		} else {
			this->changeFrames("tanu_r", -1);
		}
		return;
	}
}