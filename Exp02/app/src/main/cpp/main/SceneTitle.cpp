#include "SceneTitle.h"

SceneTitle *SceneTitle::createScene(int dWidth, int dHeight) {
	// New
	SceneTitle *scene = new SceneTitle(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneTitle::SceneTitle(int dWidth, int dHeight) : SceneBase(dWidth, dHeight) {
	LOGD("Main", "SceneTitle()\n");
}

SceneTitle::~SceneTitle() {
	LOGD("Main", "~SceneTitle()\n");
	// Delete
	DX_SAFE_DELETE(btn);
	DX_SAFE_DELETE_VECTOR(sprites);
}

bool SceneTitle::init() {
	LOGD("Main", "SceneTitle::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	btn = BtnBase::createBtn("images/box_100x60.png", "GREAT", cX, cY);
	btn->setScale(3);
	btn->addEventListener(this, BtnTag::QUIT);

	for (int i = 0; i < 3; i++) {
		int rX = UtilMath::getInstance()->getRandom(0, dWidth);
		int rY = UtilMath::getInstance()->getRandom(0, dHeight);
		auto sprite = SpriteBase::createSprite("images/y_reimu_x1.png", rX, rY);
		sprite->setScale(5);
		sprites.push_back(sprite);
	}

	return true;
}

void SceneTitle::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	btn->setOnTouchBegan(id, x, y);// Btn

	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		if (sprite->containsPoint(x, y)) {
			LOGD("Main", "Contains!!");
		}
	}
}

void SceneTitle::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	btn->setOnTouchMoved(id, x, y);// Btn
}

void SceneTitle::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	btn->setOnTouchEnded(id, x, y);// Btn
}

void SceneTitle::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	btn->update(delay);// Btn

	// Label
	UtilLabel::getInstance()->drawStr("TITLE!!", cX, 120,
	                                  5, UtilAlign::CENTER);

	// Test
	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		sprite->update(delay);
	}
}

void SceneTitle::onBtnPressed(BtnTag& tag) {
	LOGD("Main", "onBtnPressed()");
}

void SceneTitle::onBtnCanceled(BtnTag& tag) {
	LOGD("Main", "onBtnCanceled()");
}

void SceneTitle::onBtnReleased(BtnTag& tag) {
	LOGD("Main", "onBtnReleased():%d", tag);
	UtilSound::getInstance()->playSE("se_coin_01.wav");
	if(tag == BtnTag::QUIT) UtilDx::getInstance()->setQuitFlg();// Quit
}