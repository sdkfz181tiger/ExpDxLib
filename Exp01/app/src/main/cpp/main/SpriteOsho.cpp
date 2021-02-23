#include "SpriteOsho.h"

SpriteOsho *SpriteOsho::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteOsho *sprite = new SpriteOsho(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteOsho::SpriteOsho(float x, float y) : SpriteChara(x, y), mManager(nullptr) {
	LOGD("Main", "SpriteOsho()\n");
}

SpriteOsho::~SpriteOsho() {
	LOGD("Main", "~SpriteOsho()\n");
}

bool SpriteOsho::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;
	this->startIdle();// Idle
	return true;
}

void SpriteOsho::update(float delay) {
	// Stay
	if (state == StateOsho::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			this->startIdle();
		}
	}
	// Idle
	if (state == StateOsho::IDLE) {
		if (0 < idleCnt) {
			idleCnt--;
		} else {
			this->startStay();
		}
	}
	// Walk
	if (state == StateOsho::WALK) {
		if (this->getMoveFlg()) {
			pos.x += vel.x * delay;
			pos.y += vel.y * delay;
			if (!walkFlg) {
				walkLen -= this->getSpeed() * delay;
				if (walkLen <= 0.0f) {
					if (0 < ways.size()) {
						this->startFollownext();
					} else {
						this->startStay();
					}
				}
			}
		}
	}
	// Followway
	if (state == StateOsho::FOLLOWWAY) {
		if (0 < ways.size()) {
			Vec2 &pos = ways.at(ways.size() - 1);
			this->startWalk(120, pos.x, pos.y, false);
			ways.pop_back();
		} else {
			this->startStay();
		}
	}
	// Follownext
	if (state == StateOsho::FOLLOWNEXT) {
		if (0 < ways.size()) {
			Vec2 &pos = ways.at(ways.size() - 1);
			this->startWalk(120, pos.x, pos.y, false);
			ways.pop_back();
		} else {
			this->startStay();
		}
	}
	// Ways
	unsigned int cWhite = GetColor(255, 255, 255);
	for (auto way: ways) {
		const int x = way.x;
		const int y = way.y;
		DrawBox(x - 2, y - 2, x + 2, y + 2, cWhite, true);
	}
	// Draw
	this->draw();
}

void SpriteOsho::changeState(int sta) {
	// State
	if (state == sta) return;
	state = sta;

	if (state == StateOsho::STAY) {
		//LOGD("Main", "Let's stay!!");
		// Frames
		this->pauseFrames();
		return;
	}
	if (state == StateOsho::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		vector<string> frames = {"osho_f", "osho_r", "osho_l", "osho_b"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateOsho::WALK) {
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

void SpriteOsho::startFollowway(const vector<Vec2> &poses, MazeManager *mm) {
	// Ways
	if (0 < ways.size()) ways.clear();
	for (auto pos: poses) ways.push_back(pos);
	// MazeManager
	if (mManager == nullptr) mManager = mm;
	// State
	this->changeState(StateOsho::FOLLOWWAY);
}

void SpriteOsho::startFollownext() {
	// State
	this->changeState(StateOsho::FOLLOWNEXT);
}