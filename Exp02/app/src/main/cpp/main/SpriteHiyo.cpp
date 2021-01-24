#include "SpriteHiyo.h"

SpriteHiyo *SpriteHiyo::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteHiyo *sprite = new SpriteHiyo(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteHiyo::SpriteHiyo(float x, float y) : SpriteChara(x, y),
										   target(nullptr),
										   footprints(8, Vec2(0, 0)) {
	LOGD("Main", "SpriteHiyo()\n");
}

SpriteHiyo::~SpriteHiyo() {
	LOGD("Main", "~SpriteHiyo()\n");
}

bool SpriteHiyo::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("hiyo_f");
	this->pushFrames("hiyo_b");
	this->pushFrames("hiyo_r");
	this->pushFrames("hiyo_l");
	this->pushFrames("hiyo_d");
	this->pushFrames("hiyo_i1");
	this->pushFrames("hiyo_i2");

	this->startIdle();// Idle

	return true;
}

void SpriteHiyo::update(float delay) {
	// Footprints
	this->checkFootprints();
	// Draw
	this->draw();
}

void SpriteHiyo::checkFootprints() {
	if (!target) return;
	if (target->getPosX() != footprints.front().x ||
		target->getPosY() != footprints.front().y) {

		footprints.emplace_front(target->getPosX(), target->getPosY());

		int deg = UtilMath::getInstance()->calcDeg2D(pos, footprints.back());
		if (deg != getDegree()) {
			if (deg < 45) {
				this->changeFrames("hiyo_r", -1);
			} else if (deg < 135) {
				this->changeFrames("hiyo_f", -1);
			} else if (deg < 225) {
				this->changeFrames("hiyo_l", -1);
			} else if (deg < 315) {
				this->changeFrames("hiyo_b", -1);
			} else {
				this->changeFrames("hiyo_r", -1);
			}
		}
		setDegree(deg);
		resumeFrames();

		pos.x = footprints.back().x;
		pos.y = footprints.back().y;
		footprints.pop_back();
		return;
	}
	this->pauseFrames();
}

void SpriteHiyo::setTarget(SpriteBase *tgt) {
	target = tgt;
	for (auto &footprint : footprints) {
		footprint.x = getPosX();
		footprint.y = getPosY();
	}
}