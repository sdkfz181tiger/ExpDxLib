#include "SpriteItem.h"

SpriteItem *SpriteItem::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteItem *sprite = new SpriteItem(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteItem::SpriteItem(float x, float y) : SpriteChara(x, y) {
	LOGD("Main", "SpriteItem()\n");
}

SpriteItem::~SpriteItem() {
	LOGD("Main", "~SpriteItem()\n");
}

bool SpriteItem::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	return true;
}

void SpriteItem::update(float delay) {
	// Draw
	this->draw();
}