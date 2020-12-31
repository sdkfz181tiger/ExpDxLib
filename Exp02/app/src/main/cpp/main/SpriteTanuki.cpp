#include "SpriteTanuki.h"

SpriteTanuki *SpriteTanuki::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteTanuki *sprite = new SpriteTanuki(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteTanuki::SpriteTanuki(float x, float y) : SpriteFrames(x, y) {
	LOGD("Main", "SpriteTanuki()\n");
}

SpriteTanuki::~SpriteTanuki() {
	LOGD("Main", "~SpriteTanuki()\n");
}

bool SpriteTanuki::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("tanu_f");
	this->pushFrames("tanu_b");
	this->pushFrames("tanu_r");
	this->pushFrames("tanu_l");
	this->pushFrames("tanu_d");
	this->changeFrames("tanu_f");

	return true;
}