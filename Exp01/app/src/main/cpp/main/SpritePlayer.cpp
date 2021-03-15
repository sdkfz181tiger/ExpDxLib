#include "SpritePlayer.h"

SpritePlayer *SpritePlayer::createSprite(const string &fileName, float x, float y) {
	// New
	SpritePlayer *sprite = new SpritePlayer(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpritePlayer::SpritePlayer(float x, float y) : SpriteMaze(x, y),
											   wanCnt(0), wanInterval(10),
											   stkNow(StickPlayer::DEFAULT),
											   stkNext(StickPlayer::DEFAULT) {
	LOGD("Main", "SpritePlayer()\n");
}

SpritePlayer::~SpritePlayer() {
	LOGD("Main", "~SpritePlayer()\n");
}

bool SpritePlayer::init(const string &fileName) {
	if (!SpriteMaze::init(fileName)) return false;
	this->startIdle();// Idle
	return true;
}

void SpritePlayer::update(float delay) {
	// Stay
	if (state == StatePlayer::STAY) {
		if (0 < stayCnt) {
			stayCnt--;
		} else {
			this->startIdle();
		}
	}
	// Idle
	if (state == StatePlayer::IDLE) {
		if (0 < idleCnt) {
			idleCnt--;
		} else {
			this->startStay();
		}
	}
	// Walk
	if (state == StatePlayer::WALK) {
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
	// Followway
	if (state == StatePlayer::FOLLOWWAY) {
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
	if (state == StatePlayer::FOLLOWNEXT) {
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

	// Draw, State, Ways, StickPlayer
	this->draw();
	//this->showState();
	//this->showWays();
	//this->showStick();
}

void SpritePlayer::changeState(int sta) {
	// State
	if (state == sta) return;
	state = sta;

	if (state == StatePlayer::STAY) {
		//LOGD("Main", "Let's stay!!");
		// Frames
		this->pauseFrames();
		return;
	}
	if (state == StatePlayer::IDLE) {
		//LOGD("Main", "Let's idle!!");
		// Frames
		this->changeFrames("kobo_f", 2);
		return;
	}
	if (state == StatePlayer::WALK) {
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
	if (state == StatePlayer::DEAD) {
		//LOGD("Main", "Let's walk!!");
		this->changeFrames("kobo_omg", 5);
	}
}

void SpritePlayer::flickL() {
	// MazeManager
	if (mManager == nullptr) return;
	// StickPlayer
	if (stkNext == StickPlayer::LEFT) return;
	stkNext = StickPlayer::LEFT;// StickPlayer

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridL = mManager->getWallLG(pos.x, pos.y, 30);
	if (grid.c == gridL.c) return;
	stkNow = stkNext;// StickPlayer
	this->startFollowPos(gridL.pos.x, gridL.pos.y);
}

void SpritePlayer::flickR() {
	// MazeManager
	if (mManager == nullptr) return;
	// StickPlayer
	if (stkNext == StickPlayer::RIGHT) return;
	stkNext = StickPlayer::RIGHT;// StickPlayer

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridR = mManager->getWallRG(pos.x, pos.y, 30);
	if (grid.c == gridR.c) return;
	stkNow = stkNext;// StickPlayer
	this->startFollowPos(gridR.pos.x, gridR.pos.y);
}

void SpritePlayer::flickU() {
	// MazeManager
	if (mManager == nullptr) return;
	// StickPlayer
	if (stkNext == StickPlayer::UP) return;
	stkNext = StickPlayer::UP;// StickPlayer

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridU = mManager->getWallUG(pos.x, pos.y, 30);
	if (grid.r == gridU.r) return;
	stkNow = stkNext;// StickPlayer
	this->startFollowPos(gridU.pos.x, gridU.pos.y);
}

void SpritePlayer::flickD() {
	// MazeManager
	if (mManager == nullptr) return;
	// StickPlayer
	if (stkNext == StickPlayer::DOWN) return;
	stkNext = StickPlayer::DOWN;// StickPlayer

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);
	const MazeGrid &gridD = mManager->getWallDG(pos.x, pos.y, 30);
	if (grid.r == gridD.r) return;
	stkNow = stkNext;// StickPlayer
	this->startFollowPos(gridD.pos.x, gridD.pos.y);
}

void SpritePlayer::checkStick() {

	const MazeGrid &grid = mManager->getGridByPos(pos.x, pos.y);

	if (stkNext == StickPlayer::DEFAULT) {
		// Do nothing
	} else if (stkNext == StickPlayer::LEFT) {
		const MazeGrid &gridL = mManager->getWallLG(pos.x, pos.y, 30);
		if (grid.c != gridL.c) {
			stkNow = stkNext;// Update StickPlayer
			this->startFollowPos(gridL.pos.x, gridL.pos.y);
		}
	} else if (stkNext == StickPlayer::RIGHT) {
		const MazeGrid &gridR = mManager->getWallRG(pos.x, pos.y, 30);
		if (grid.c != gridR.c) {
			stkNow = stkNext;// Update StickPlayer
			this->startFollowPos(gridR.pos.x, gridR.pos.y);
		}
	} else if (stkNext == StickPlayer::UP) {
		const MazeGrid &gridU = mManager->getWallUG(pos.x, pos.y, 30);
		if (grid.r != gridU.r) {
			stkNow = stkNext;// Update StickPlayer
			this->startFollowPos(gridU.pos.x, gridU.pos.y);
		}
	} else if (stkNext == StickPlayer::DOWN) {
		const MazeGrid &gridD = mManager->getWallDG(pos.x, pos.y, 30);
		if (grid.r != gridD.r) {
			stkNow = stkNext;// Update StickPlayer
			this->startFollowPos(gridD.pos.x, gridD.pos.y);
		}
	} else {
		// Do nothing
	}
}

void SpritePlayer::showStick() {

	string str = "DEFAULT";
	switch (stkNext) {
		case StickPlayer::LEFT:
			str = "LEFT";
			break;
		case StickPlayer::RIGHT:
			str = "RIGHT";
			break;
		case StickPlayer::UP:
			str = "UP";
			break;
		case StickPlayer::DOWN:
			str = "DOWN";
			break;
		default:
			// Do nothing
			break;
	}
	UtilLabel::getInstance()->drawStr(str, pos.x, pos.y, 1,
									  UtilAlign::CENTER);
}

bool SpritePlayer::isDead() {
	return state == StatePlayer::DEAD;
}

void SpritePlayer::startDead() {
	// State
	this->changeState(StatePlayer::DEAD);
}