#include "SpriteChicken.h"

SpriteChicken *SpriteChicken::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChicken *sprite = new SpriteChicken(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChicken::SpriteChicken(float x, float y) : SpriteChara(x, y),
												 goCnt(0), goInterval(20),
												 layCnt(0), layInterval(40),
												 next(Vec2(0, 0)),
												 nest(Vec2(x, y)),
												 eggCnt(0), eggTotal(1),
												 eggListener(nullptr) {
	LOGD("Main", "SpriteChicken()\n");
}

SpriteChicken::~SpriteChicken() {
	LOGD("Main", "~SpriteChicken()\n");
}

bool SpriteChicken::init(const string &fileName) {
	if (!SpriteChara::init(fileName)) return false;
	this->startIdle();// Idle
	return true;
}

void SpriteChicken::update(float delay) {
	// Stay
	if (state == StateChicken::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			this->startIdle();
		}
	}
	// Idle
	if (state == StateChicken::IDLE) {
		if (0 < idleCnt) {
			idleCnt--;
		} else {
			this->startGo();
		}
	}
	// Walk
	if (state == StateChicken::WALK) {
		if (this->getMoveFlg()) {
			pos.x += vel.x * delay;
			pos.y += vel.y * delay;
			if (!walkFlg) {
				walkLen -= this->getSpeed() * delay;
				if (walkLen <= 0.0f) {
					if (0 < eggCnt) {
						pos.x = next.x;
						pos.y = next.y;
						this->startLay();
					} else {
						pos.x = nest.x;
						pos.y = nest.y;
						this->startStay();
					}
				}
			}
		}
	}
	// Go
	if (state == StateChicken::GO) {
		if (0 < goCnt) {
			goCnt--;
		} else {
			// Next
			int gSize = UtilDebug::getInstance()->getGridSize();
			this->startWalk(gSize * 20, next.x, next.y, false);
		}
	}
	// Lay
	if (state == StateChicken::LAY) {
		if (0 < layCnt) {
			layCnt--;
		} else {
			// Listener
			if (eggListener) eggListener->onEggLayed(pos.x, pos.y);
			// Nest
			int gSize = UtilDebug::getInstance()->getGridSize();
			this->startWalk(gSize * 20, nest.x, nest.y, false);
		}
	}
	// Draw
	this->draw();
}

void SpriteChicken::changeState(int sta) {
	// State
	if (state == sta) return;
	state = sta;

	if (state == StateChicken::STAY) {
		//LOGD("Main", "Let's stay!!");
		// Frames
		this->pauseFrames();
		return;
	}
	if (state == StateChicken::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		vector<string> frames = {"chicken_f_i1", "chicken_f_i2", "chicken_f_i3", "chicken_f_i4"};
		int index = UtilMath::getInstance()->getRandom(0, frames.size() - 1);
		this->changeFrames(frames.at(index), 2);
		return;
	}
	if (state == StateChicken::WALK) {
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
	if (state == StateChicken::GO) {
		//LOGD("Main", "Let's go!!");
		// Frames
		this->changeFrames("chicken_f_fly", 1);
		return;
	}
	if (state == StateChicken::LAY) {
		//LOGD("Main", "Let's lay!!");
		// Frames
		this->changeFrames("chicken_f_lay", 1);
		return;
	}
}

void SpriteChicken::setNext(int x, int y) {
	next.x = x;
	next.y = y;
}

void SpriteChicken::setEggListener(EggListener *listener) {
	eggListener = listener;
}

void SpriteChicken::startGo() {
	// Go
	goCnt = UtilMath::getInstance()->getRandom(goInterval / 2, goInterval);
	// Egg
	eggCnt = eggTotal;
	// State
	this->changeState(StateChicken::GO);
}

void SpriteChicken::startLay() {
	// Capture
	layCnt = UtilMath::getInstance()->getRandom(layInterval / 2, layInterval);
	// Egg
	eggCnt--;
	// State
	this->changeState(StateChicken::LAY);
}