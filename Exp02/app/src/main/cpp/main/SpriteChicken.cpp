#include "SpriteChicken.h"

SpriteChicken *SpriteChicken::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteChicken *sprite = new SpriteChicken(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteChicken::SpriteChicken(float x, float y) : SpriteFrames(x, y) {
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
	if(rdm == 0){
		this->changeFrames("chi_f");
	}else if(rdm == 1){
		this->changeFrames("chi_b");
	}else if(rdm == 2){
		this->changeFrames("chi_r");
	}else if(rdm == 3){
		this->changeFrames("chi_l");
	}else{
		this->changeFrames("chi_d");
	}

	return true;
}