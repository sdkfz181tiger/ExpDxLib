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

	int rdm = UtilMath::getInstance()->getRandom(0, 5);
	if(rdm == 0){
		this->changeFrames("tanu_f", -1);
	}else if(rdm == 1){
		this->changeFrames("tanu_b", -1);
	}else if(rdm == 2){
		this->changeFrames("tanu_r", -1);
	}else if(rdm == 3){
		this->changeFrames("tanu_l", -1);
	}else{
		this->changeFrames("tanu_d", -1);
	}

	return true;
}