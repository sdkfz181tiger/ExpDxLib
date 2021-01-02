#include "SpriteChicken.h"

SpriteChicken *SpriteChicken::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChicken *sprite = new SpriteChicken(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChicken::SpriteChicken(float x, float y) : SpriteFrames(x, y),
												 dst(Vec2(x, y)), distance(0.0f) {
	LOGD("Main", "SpriteChicken()\n");
}

SpriteChicken::~SpriteChicken() {
	LOGD("Main", "~SpriteChicken()\n");
}

bool SpriteChicken::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("chi_f");
	this->pushFrames("chi_b");
	this->pushFrames("chi_r");
	this->pushFrames("chi_l");
	this->pushFrames("chi_d");

	int rdm = UtilMath::getInstance()->getRandom(0, 5);
	if (rdm == 0) {
		this->changeFrames("chi_f");
	} else if (rdm == 1) {
		this->changeFrames("chi_b");
	} else if (rdm == 2) {
		this->changeFrames("chi_r");
	} else if (rdm == 3) {
		this->changeFrames("chi_l");
	} else {
		this->changeFrames("chi_d");
	}

	return true;
}

void SpriteChicken::update(float delay) {
	// Move
	if (moveFlg) {
		pos.x += vel.x * delay;
		pos.y += vel.y * delay;
		distance -= speed * delay;
		if (distance <= 0.0f) stop();
	}
	// Test
	int white = GetColor(255, 255, 255);
	DrawLine(pos.x, pos.y, dst.x, dst.y, white, 2);
	// Draw
	this->draw();
}

void SpriteChicken::moveTo(int spd, int x, int y) {
	// Move
	this->move(spd, UtilMath::getInstance()->calcDeg2D(pos, Vec2(x, y)));
	dst.x = x;
	dst.y = y;
	distance = UtilMath::getInstance()->calcDistance2D(pos, Vec2(x, y));
	// Frames
	if (degree < 45) {
		this->changeFrames("chi_r");
	} else if (degree < 135) {
		this->changeFrames("chi_f");
	} else if (degree < 225) {
		this->changeFrames("chi_l");
	} else if (degree < 315) {
		this->changeFrames("chi_b");
	} else {
		this->changeFrames("chi_r");
	}
}