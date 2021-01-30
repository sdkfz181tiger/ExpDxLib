#include "SpriteChick.h"

SpriteChick *SpriteChick::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChick *sprite = new SpriteChick(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChick::SpriteChick(float x, float y) : SpriteChara(x, y),
										   target(nullptr),
										   footprints(8, Vec2(0, 0)) {
	LOGD("Main", "SpriteChick()\n");
}

SpriteChick::~SpriteChick() {
	LOGD("Main", "~SpriteChick()\n");
}

bool SpriteChick::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;
	this->changeFrames("chick_roll", -1);
	return true;
}

void SpriteChick::update(float delay) {
	// Footprints
	this->checkFootprints();
	// Draw
	this->draw();
}

void SpriteChick::checkFootprints() {
	if (!target) return;
	if (target->getPosX() != footprints.front().x ||
		target->getPosY() != footprints.front().y) {

		footprints.emplace_front(target->getPosX(), target->getPosY());

		int deg = UtilMath::getInstance()->calcDeg2D(pos, footprints.back());
		if (deg != getDegree()) {
			if (deg < 45) {
				this->changeFrames("chick_r", -1);
			} else if (deg < 135) {
				this->changeFrames("chick_f", -1);
			} else if (deg < 225) {
				this->changeFrames("chick_l", -1);
			} else if (deg < 315) {
				this->changeFrames("chick_b", -1);
			} else {
				this->changeFrames("chick_r", -1);
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

void SpriteChick::setTarget(SpriteBase *tgt) {
	target = tgt;
	for (auto &footprint : footprints) {
		footprint.x = getPosX();
		footprint.y = getPosY();
	}
}