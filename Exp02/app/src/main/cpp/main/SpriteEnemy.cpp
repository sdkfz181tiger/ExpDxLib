#include "SpriteEnemy.h"

SpriteEnemy *SpriteEnemy::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteEnemy *sprite = new SpriteEnemy(x, y);
	if (sprite && sprite->initGraph(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteEnemy::SpriteEnemy(float x, float y) : SpriteBase(x, y) {
	LOGD("Main", "SpriteEnemy()\n");
}

SpriteEnemy::~SpriteEnemy() {
	LOGD("Main", "~SpriteEnemy()\n");
}