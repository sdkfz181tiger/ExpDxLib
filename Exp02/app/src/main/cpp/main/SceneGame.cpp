#include "SceneGame.h"

SceneGame *SceneGame::createScene(int dWidth, int dHeight) {
	// New
	SceneGame *scene = new SceneGame(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneGame::SceneGame(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
                                                sceneListener(nullptr),
                                                btnQuit(nullptr), btnTest(nullptr) {
	LOGD("Main", "SceneGame()\n");
}

SceneGame::~SceneGame() {
	LOGD("Main", "~SceneGame()\n");
	// Delete
	DX_SAFE_DELETE(btnQuit);
	DX_SAFE_DELETE(btnTest);
	DX_SAFE_DELETE_VECTOR(sprites);
}

bool SceneGame::init() {
	LOGD("Main", "SceneGame::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	btnQuit = BtnBase::createBtn("images/box_32x32.png", "QUIT", cX - 180, cY);
	btnQuit->addBtnListener(this, BtnTag::QUIT);

	btnTest = BtnBase::createBtn("images/box_90x30.png", "RESULT", cX + 180, cY);
	btnTest->addBtnListener(this, BtnTag::RESULT);

	for (int i = 0; i < 3; i++) {
		int rX = UtilMath::getInstance()->getRandom(0, dWidth);
		int rY = UtilMath::getInstance()->getRandom(0, dHeight);
		auto sprite = SpriteBase::createSprite("images/y_reimu_x1.png", rX, rY);
		sprites.push_back(sprite);
	}

	return true;
}

void SceneGame::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	btnQuit->setOnTouchBegan(id, x, y);// Btn
	btnTest->setOnTouchBegan(id, x, y);// Btn

	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		if (sprite->containsPoint(x, y)) {
			LOGD("Main", "Contains!!");
		}
	}
}

void SceneGame::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	btnQuit->setOnTouchMoved(id, x, y);// Btn
	btnTest->setOnTouchMoved(id, x, y);// Btn
}

void SceneGame::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	btnQuit->setOnTouchEnded(id, x, y);// Btn
	btnTest->setOnTouchEnded(id, x, y);// Btn
}

void SceneGame::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	btnQuit->update(delay);// Btn
	btnTest->update(delay);// Btn

	// Label
	UtilLabel::getInstance()->drawStr("GAME!!", cX, 120,
	                                  5, UtilAlign::CENTER);

	// Test
	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		sprite->update(delay);
	}
}

void SceneGame::addSceneListener(SceneListener *sceneListener) {
	this->sceneListener = sceneListener;
}

void SceneGame::onBtnPressed(BtnTag &tag) {
	LOGD("Main", "onBtnPressed()");
}

void SceneGame::onBtnCanceled(BtnTag &tag) {
	LOGD("Main", "onBtnCanceled()");
}

void SceneGame::onBtnReleased(BtnTag &tag) {
	LOGD("Main", "onBtnReleased():%d", tag);
	if (tag == BtnTag::QUIT) {
		UtilDx::getInstance()->setQuitFlg();
	}
	if (tag == BtnTag::RESULT) {
		UtilSound::getInstance()->playSE("se_coin_01.wav");
		if (sceneListener) sceneListener->onSceneChange(SceneTag::RESULT);
	}
}