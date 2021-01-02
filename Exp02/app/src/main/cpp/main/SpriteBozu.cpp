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

	int rdm = UtilMath::getInstance()->getRandom(0, 5);
	if(rdm == 0){
		this->changeFrames("bozu_f", -1);
	}else if(rdm == 1){
		this->changeFrames("bozu_b", -1);
	}else if(rdm == 2){
		this->changeFrames("bozu_r", -1);
	}else if(rdm == 3){
		this->changeFrames("bozu_l", -1);
	}else{
		this->changeFrames("bozu_d", -1);
	}

	return true;
}