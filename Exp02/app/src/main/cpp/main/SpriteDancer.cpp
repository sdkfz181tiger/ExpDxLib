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
	this->pushFrames("kobo_front");
	this->pushFrames("kobo_back");
	this->pushFrames("kobo_right");
	this->pushFrames("kobo_left");
	this->pushFrames("kobo_dead");
	this->changeFrames("kobo_front");

	return true;
}