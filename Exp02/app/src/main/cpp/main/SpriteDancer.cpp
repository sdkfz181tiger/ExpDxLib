#include "SpriteDancer.h"

SpriteDancer *SpriteDancer::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteDancer *sprite = new SpriteDancer(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteDancer::SpriteDancer(float x, float y) : SpriteFrames(x, y) {
	LOGD("Main", "SpriteDancer()\n");
}

SpriteDancer::~SpriteDancer() {
	LOGD("Main", "~SpriteDancer()\n");
}

bool SpriteDancer::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("chi_f");
	this->pushFrames("chi_b");
	this->pushFrames("chi_r");
	this->pushFrames("chi_l");
	this->pushFrames("chi_d");
	this->changeFrames("chi_f");

	return true;
}