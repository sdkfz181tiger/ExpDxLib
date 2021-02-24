#include "SpriteEgg.h"

SpriteEgg *SpriteEgg::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteEgg *sprite = new SpriteEgg(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteEgg::SpriteEgg(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteEgg()\n");
}

SpriteEgg::~SpriteEgg() {
	LOGD("Main", "~SpriteEgg()\n");
}

bool SpriteEgg::init(const string &fileName) {
	if (!SpriteChara::init(fileName)) return false;
	this->changeFrames("egg_hop", -1);// Frames
	return true;
}

void SpriteEgg::update(float delay) {
	// Draw
	this->draw();
}