#include "SpriteKobozu.h"

SpriteKobozu *SpriteKobozu::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteKobozu *sprite = new SpriteKobozu(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteKobozu::SpriteKobozu(float x, float y) : SpriteFrames(x, y) {
	LOGD("Main", "SpriteKobozu()\n");
}

SpriteKobozu::~SpriteKobozu() {
	LOGD("Main", "~SpriteKobozu()\n");
}

bool SpriteKobozu::init(const string &fileName) {
	if (!SpriteFrames::init(fileName)) return false;

	// Frames
	this->pushFrames("kobo_f");
	this->pushFrames("kobo_b");
	this->pushFrames("kobo_r");
	this->pushFrames("kobo_l");
	this->pushFrames("kobo_d");

	int rdm = UtilMath::getInstance()->getRandom(0, 5);
	if(rdm == 0){
		this->changeFrames("kobo_f");
	}else if(rdm == 1){
		this->changeFrames("kobo_b");
	}else if(rdm == 2){
		this->changeFrames("kobo_r");
	}else if(rdm == 3){
		this->changeFrames("kobo_l");
	}else{
		this->changeFrames("kobo_d");
	}

	return true;
}