#include "SpriteBozu.h"

SpriteBozu *SpriteBozu::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteBozu *sprite = new SpriteBozu(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteBozu::SpriteBozu(float x, float y) : SpriteFrames(x, y) {
	LOGD("Main", "SpriteBozu()\n");
}

SpriteBozu::~SpriteBozu() {
	LOGD("Main", "~SpriteBozu()\n");
}

bool SpriteBozu::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("bozu_f");
	this->pushFrames("bozu_b");
	this->pushFrames("bozu_r");
	this->pushFrames("bozu_l");
	this->pushFrames("bozu_d");
	this->changeFrames("bozu_f");

	return true;
}