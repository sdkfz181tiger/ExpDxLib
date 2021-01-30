#include "SpriteChicken.h"

SpriteChicken *SpriteChicken::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChicken *sprite = new SpriteChicken(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChicken::SpriteChicken(float x, float y) : SpriteChara(x, y),
												 goCnt(0), goInterval(10),
												 layCnt(0), layInterval(20),
												 nest(Vec2(x, y)),
												 eggCnt(0), eggTotal(1) {
	LOGD("Main", "SpriteChicken()\n");
}

SpriteChicken::~SpriteChicken() {
	LOGD("Main", "~SpriteChicken()\n");
}

bool SpriteChicken::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;
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
			this->startGo();
		}
	}
	// Walk
	if (state == StateChara::WALK) {
		if (this->getMoveFlg()) {
			pos.x += vel.x * delay;
			pos.y += vel.y * delay;
			if (!walkFlg) {
				walkLen -= this->getSpeed() * delay;
				if (walkLen <= 0.0f) {
					if (0 < eggCnt) {
						this->startLay();
					} else {
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
			int minX = gSize * 2;
			int maxX = UtilDx::getInstance()->getDispWidth() - gSize * 2;
			int minY = gSize * 10;
			int maxY = UtilDx::getInstance()->getDispHeight() - gSize * 10;
			int x = UtilMath::getInstance()->getRandom(minX, maxX);
			int y = UtilMath::getInstance()->getRandom(minY, maxY);
			this->startWalk(gSize * 20, x, y, false);
		}
	}
	// Lay
	if (state == StateChicken::LAY) {
		if (0 < layCnt) {
			layCnt--;
		} else {
			// Listener
			if (eggListener) eggListener->onEggLayed(pos.x, pos.y);
			// Next
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

	if (state == StateChara::STAY) {
		//LOGD("Main", "Let's stay!!");
		// Frames
		this->pauseFrames();
		return;
	}
	if (state == StateChara::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		vector<string> frames = {"chicken_f_i1", "chicken_f_i2", "chicken_f_i3", "chicken_f_i4"};
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