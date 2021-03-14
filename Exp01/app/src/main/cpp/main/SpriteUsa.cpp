#include "SpriteUsa.h"

SpriteUsa *SpriteUsa::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteUsa *sprite = new SpriteUsa(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteUsa::SpriteUsa(float x, float y) : SpriteMaze(x, y),
										 wanCnt(0), wanInterval(10),
										 stkNow(Stick::DEFAULT),
										 stkNext(Stick::DEFAULT) {
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
			this->startIdle();
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
					if (0 < ways.size()) {
						this->startFollowNext();
					} else {
						this->startStay();
					}
					if (stkNow != stkNext) this->checkStick();
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
	// Followway
	if (state == StateUsa::FOLLOWWAY) {
		if (0 < ways.size()) {
			const int gSize = UtilDebug::getInstance()->getGridSize();
			const int spd = gSize * 8;
			const Vec2 &pos = ways.at(ways.size() - 1);
			this->startWalkDst(spd, pos.x, pos.y, false);
			ways.pop_back();
		} else {
			this->startStay();
		}
	}
	// Follownext
	if (state == StateUsa::FOLLOWNEXT) {
		if (0 < ways.size()) {
			const int gSize = UtilDebug::getInstance()->getGridSize();
			const int spd = gSize * 8;
			const Vec2 &pos = ways.at(ways.size() - 1);
			this->startWalkDst(spd, pos.x, pos.y, false);
			ways.pop_back();
		} else {
			this->startStay();
		}
	}

	// Draw, State, Ways, Stick
	this->draw();
	this->showState();
	this->showWays();
	this->showStick();
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

void SpriteUsa::flickL() {
	// MazeManager
	if (mManager == nullptr) return;
	// Stick
	if (stkNext == Stick::LEFT) return;
	stkNext = Stick::LEFT;// Stick

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridL = mManager->getWallLG(pos.x, pos.y, 30);
	if (grid.c == gridL.c) return;
	stkNow = stkNext;// Stick
	this->startFollowPos(gridL.pos.x, gridL.pos.y);
}

void SpriteUsa::flickR() {
	// MazeManager
	if (mManager == nullptr) return;
	// Stick
	if (stkNext == Stick::RIGHT) return;
	stkNext = Stick::RIGHT;// Stick

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridR = mManager->getWallRG(pos.x, pos.y, 30);
	if (grid.c == gridR.c) return;
	stkNow = stkNext;// Stick
	this->startFollowPos(gridR.pos.x, gridR.pos.y);
}

void SpriteUsa::flickU() {
	// MazeManager
	if (mManager == nullptr) return;
	// Stick
	if (stkNext == Stick::UP) return;
	stkNext = Stick::UP;// Stick

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridU = mManager->getWallUG(pos.x, pos.y, 30);
	if (grid.r == gridU.r) return;
	stkNow = stkNext;// Stick
	this->startFollowPos(gridU.pos.x, gridU.pos.y);
}

void SpriteUsa::flickD() {
	// MazeManager
	if (mManager == nullptr) return;
	// Stick
	if (stkNext == Stick::DOWN) return;
	stkNext = Stick::DOWN;// Stick

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridD = mManager->getWallDG(pos.x, pos.y, 30);
	if (grid.r == gridD.r) return;
	stkNow = stkNext;// Stick
	this->startFollowPos(gridD.pos.x, gridD.pos.y);
}

void SpriteUsa::checkStick() {

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);

	if (stkNext == Stick::DEFAULT) {
		// Do nothing
	} else if (stkNext == Stick::LEFT) {
		const MazeGrid &gridL = mManager->getWallLG(pos.x, pos.y, 30);
		if (grid.c != gridL.c) {
			stkNow = stkNext;// Update stick
			this->startFollowPos(gridL.pos.x, gridL.pos.y);
		}
	} else if (stkNext == Stick::RIGHT) {
		const MazeGrid &gridR = mManager->getWallRG(pos.x, pos.y, 30);
		if (grid.c != gridR.c) {
			stkNow = stkNext;// Update stick
			this->startFollowPos(gridR.pos.x, gridR.pos.y);
		}
	} else if (stkNext == Stick::UP) {
		const MazeGrid &gridU = mManager->getWallUG(pos.x, pos.y, 30);
		if (grid.r != gridU.r) {
			stkNow = stkNext;// Update stick
			this->startFollowPos(gridU.pos.x, gridU.pos.y);
		}
	} else if (stkNext == Stick::DOWN) {
		const MazeGrid &gridD = mManager->getWallDG(pos.x, pos.y, 30);
		if (grid.r != gridD.r) {
			stkNow = stkNext;// Update stick
			this->startFollowPos(gridD.pos.x, gridD.pos.y);
		}
	} else {
		// Do nothing
	}
}

void SpriteUsa::showStick() {

	string str = "DEFAULT";
	switch (stkNext) {
		case Stick::LEFT:
			str = "LEFT";
			break;
		case Stick::RIGHT:
			str = "RIGHT";
			break;
		case Stick::UP:
			str = "UP";
			break;
		case Stick::DOWN:
			str = "DOWN";
			break;
		default:
			// Do nothing
			break;
	}
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y, 1,
									  UtilAlign::CENTER);
}