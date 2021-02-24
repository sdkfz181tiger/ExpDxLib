#include "SpriteKobo.h"

SpriteKobo *SpriteKobo::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteKobo *sprite = new SpriteKobo(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteKobo::SpriteKobo(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteKobo()\n");
}

SpriteKobo::~SpriteKobo() {
	LOGD("Main", "~SpriteKobo()\n");
}

bool SpriteKobo::init(const string &fileName) {
	if (!SpriteChara::init(fileName)) return false;
	this->startIdle();// Idle
	return true;
}

void SpriteKobo::update(float delay) {
	// Stay
	if (state == StateKobo::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			//this->startIdle();
		}
	}
	// Idle
	if (state == StateKobo::IDLE) {
		if (0 < idleCnt) {
			idleCnt--;
		} else {
			this->startIdle();
		}
	}
	// Walk
	if (state == StateKobo::WALK) {
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

void SpriteKobo::changeState(int sta) {
	// State
	if (state == sta) return;
	state = sta;

	if (state == StateKobo::STAY) {
		//LOGD("Main", "Let's stay!!");
		// Frames
		this->pauseFrames();
		return;
	}
	if (state == StateKobo::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		this->changeFrames("kobo_f", 2);
		return;
	}
	if (state == StateKobo::WALK) {
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
	if (state == StateKobo::DEAD) {
		//LOGD("Main", "Let's walk!!");
		this->changeFrames("kobo_omg", 5);
	}
}

bool SpriteKobo::isDead() {
	return state == StateKobo::DEAD;
}

void SpriteKobo::startDead() {
	// State
	this->changeState(StateKobo::DEAD);
}