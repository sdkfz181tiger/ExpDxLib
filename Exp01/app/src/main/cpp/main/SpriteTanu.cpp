#include "SpriteTanu.h"

SpriteTanu *SpriteTanu::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteTanu *sprite = new SpriteTanu(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteTanu::SpriteTanu(float x, float y) : SpriteMaze(x, y),
										   wanCnt(0), wanInterval(10),
										   capCnt(0), capInterval(10),
										   escCnt(0), escInterval(10),
										   relCnt(0), relInterval(20),
										   slpCnt(0), slpInterval(240),
										   eggFlg(false), egg(nullptr),
										   chickFlg(false), chick(nullptr) {
	LOGD("Main", "SpriteTanu()\n");
}

SpriteTanu::~SpriteTanu() {
	LOGD("Main", "~SpriteTanu()\n");
}

bool SpriteTanu::init(const string &fileName) {
	if (!SpriteMaze::init(fileName)) return false;
	egg = SpriteEgg::createSprite("images/c_egg.png", pos.x, pos.y);// Egg
	chick = SpriteChick::createSprite("images/c_chick.png", pos.x, pos.y);// Chick
	this->startIdle();// Idle
	return true;
}

void SpriteTanu::update(float delay) {
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
			const int rdm = UtilMath::getInstance()->getRandom(0, 10);
			if (rdm < 9) {
				this->startFollowRdm();
			} else {
				this->startSleep();
			}
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
					if (0 < ways.size()) {
						this->startFollowNext();
						if (!this->getItemFlg()) {
							if (this->searchLeaderInsight() &&
								!this->checkLeaderOnSameRC() &&
								!this->checkLeaderOnway()) {
								this->startFollowLeader();
							}
						}
					} else {
						if (this->getItemFlg()) {
							this->startRelease();
						} else {
							this->startStay();
						}
					}
				}
			}
		}
	}
	// Wander
	if (state == StateTanu::WANDER) {
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
			this->startWalk(gSize * 5, x, y, false);
		}
	}
	// Captured
	if (state == StateTanu::CAPTURED) {
		if (0 < capCnt) {
			capCnt--;
		} else {
			this->startEscape();
		}
	}
	// Escape
	if (state == StateTanu::ESCAPE) {
		if (0 < escCnt) {
			escCnt--;
		} else {
			// Next
			this->startFollowRdm();
		}
	}
	// Release
	if (state == StateTanu::RELEASE) {
		if (0 < relCnt) {
			relCnt--;
		} else {
			this->startIdle();
		}
	}
	// Sleep
	if (state == StateTanu::SLEEP) {
		if (0 < slpCnt) {
			slpCnt--;
		} else {
			this->startIdle();
		}
	}
	// Followway
	if (state == StateTanu::FOLLOWWAY) {
		if (0 < ways.size()) {
			const int gSize = UtilDebug::getInstance()->getGridSize();
			const int spd = (getItemFlg()) ? gSize * 30 : gSize * 10;
			const Vec2 &pos = ways.at(ways.size() - 1);
			this->startWalk(spd, pos.x, pos.y, false);
			ways.pop_back();
		} else {
			this->startStay();
		}
	}
	// Follownext
	if (state == StateTanu::FOLLOWNEXT) {
		if (0 < ways.size()) {
			const int gSize = UtilDebug::getInstance()->getGridSize();
			const int spd = (getItemFlg()) ? gSize * 30 : gSize * 10;
			const Vec2 &pos = ways.at(ways.size() - 1);
			this->startWalk(spd, pos.x, pos.y, false);
			ways.pop_back();
		} else {
			this->startStay();
		}
	}

	// Draw, State, Ways
	this->draw();
	this->showState();
	this->showWays();

	// Egg
	if (eggFlg) {
		egg->setPosX(pos.x);
		egg->setPosY(pos.y);
		egg->update(delay);
	}

	// Chick
	if (chickFlg) {
		chick->setPosX(pos.x);
		chick->setPosY(pos.y);
		chick->update(delay);
	}
}

void SpriteTanu::changeState(int sta) {
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
		if (this->getItemFlg()) {
			this->changeFrames("tanu_grab", -1);
			return;
		}
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
	if (state == StateTanu::WANDER) {
		//LOGD("Main", "Let's wander!!");
		// Frames
		this->changeFrames("tanu_grab", -1);
		return;
	}
	if (state == StateTanu::CAPTURED) {
		//LOGD("Main", "Let's captured!!");
		// Frames
		this->changeFrames("tanu_grab", -1);
		return;
	}
	if (state == StateTanu::ESCAPE) {
		//LOGD("Main", "Let's escape!!");
		// Frames
		this->changeFrames("tanu_grab", -1);
		return;
	}
	if (state == StateTanu::RELEASE) {
		//LOGD("Main", "Let's release!!");
		// Frames
		this->changeFrames("tanu_eat", -1);
		return;
	}
	if (state == StateTanu::SLEEP) {
		//LOGD("Main", "Let's sleep!!");
		// Frames
		const int rdm = UtilMath::getInstance()->getRandom(0, 10);
		if (rdm < 5) {
			this->changeFrames("tanu_sleep_r", -1);
		} else {
			this->changeFrames("tanu_sleep_l", -1);
		}
		return;
	}
}

void SpriteTanu::startWander() {
	// Wander
	wanCnt = UtilMath::getInstance()->getRandom(wanInterval / 2, wanInterval);
	// State
	this->changeState(StateTanu::WANDER);
}

void SpriteTanu::startCapture(bool egg, bool chick) {
	// Capture
	capCnt = capInterval;
	// Flgs
	eggFlg = egg;
	chickFlg = chick;
	// State
	this->changeState(StateTanu::CAPTURED);
}

void SpriteTanu::startEscape() {
	// Escape
	escCnt = escInterval;
	// State
	this->changeState(StateTanu::ESCAPE);
}

void SpriteTanu::startRelease() {
	// Release
	relCnt = relInterval;
	// State
	this->changeState(StateTanu::RELEASE);
	// Flgs
	eggFlg = false;
	chickFlg = false;
}

void SpriteTanu::startSleep() {
	// Sleep
	slpCnt = slpInterval;
	// State
	this->changeState(StateTanu::SLEEP);
}

bool SpriteTanu::getItemFlg() {
	return chickFlg || eggFlg;
}