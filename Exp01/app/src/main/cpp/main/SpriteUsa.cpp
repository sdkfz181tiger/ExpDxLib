#include "SpriteUsa.h"

SpriteUsa *SpriteUsa::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteUsa *sprite = new SpriteUsa(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteUsa::SpriteUsa(float x, float y) : SpriteMaze(x, y),
										 wanCnt(0), wanInterval(10) {
	LOGD("Main", "SpriteUsa()\n");
}

SpriteUsa::~SpriteUsa() {
	LOGD("Main", "~SpriteUsa()\n");
}

bool SpriteUsa::init(const string &fileName) {
	if (!SpriteMaze::init(fileName)) return false;
	this->startIdle();// Idle
	return true;
}

void SpriteUsa::update(float delay) {
	// Stay
	if (state == StateChara::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			if (this->searchLeaderInsight() &&
				!this->checkLeaderOnSameRC() &&
				!this->checkLeaderOnway()) {
				this->startFollowLeader();
			} else {
				this->startIdle();
			}
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
				if (walkLen <= 0.0f) {
					this->startStay();
				}
			}
		}
	}
	// Wander
	if (state == StateUsa::WANDER) {
		if (0 < wanCnt) {
			wanCnt--;
		} else {
			// Next
			int gSize = UtilDebug::getInstance()->getGridSize();
			int minX = gSize * 2;
			int maxX = UtilDx::getInstance()->getDispWidth() - gSize * 2;
			int minY = gSize * 10;
			int maxY = UtilDx::getInstance()->getDispHeight() - gSize * 10;
			int x = UtilMath::getInstance()->getRandom(minX, maxX);
			int y = UtilMath::getInstance()->getRandom(minY, maxY);
			this->startWalkDst(gSize * 5, x, y, false);
		}
	}

	// Draw, State, Ways
	this->draw();
	this->showState();
	this->showWays();
}

void SpriteUsa::changeState(int sta) {
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
	if (state == StateUsa::WANDER) {
		//LOGD("Main", "Let's wander!!");
		// Frames
		this->changeFrames("tanu_grab", -1);
		return;
	}
}
