#include "SpriteDancer.h"

SpriteDancer *SpriteDancer::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteDancer *sprite = new SpriteDancer(x, y);
	if (sprite && sprite->initDivGraph(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteDancer::SpriteDancer(float x, float y) : SpriteBase(x, y) {
	LOGD("Main", "SpriteDancer()\n");
}

SpriteDancer::~SpriteDancer() {
	LOGD("Main", "~SpriteDancer()\n");
}