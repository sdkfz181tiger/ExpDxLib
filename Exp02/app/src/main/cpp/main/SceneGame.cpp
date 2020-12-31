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
	const int gSize = UtilDebug::getInstance()->getGridSize();

	btnQuit = BtnBase::createBtn("images/box_16x16.png", "Q",
								 dWidth - gSize * 1, gSize);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	btnTest = BtnBase::createBtn("images/box_16x16.png", "R",
								 dWidth - gSize * 3, gSize);
	btnTest->addBtnListener(this, BtnTag::RESULT);
	btns.push_back(btnTest);

	auto bozu = SpriteBozu::createSprite("images/c_bozu.png", cX, cY);
	sprites.push_back(bozu);
	auto kobo = SpriteKobozu::createSprite("images/c_kobo.png", cX - gSize * 2, cY);
	sprites.push_back(kobo);
	auto tanu = SpriteTanuki::createSprite("images/c_tanu.png", cX + gSize * 2, cY);
	sprites.push_back(tanu);

	for (int i = 0; i < 30; i++) {
		int pX = UtilMath::getInstance()->getRandom(200, dWidth - 200);
		int pY = UtilMath::getInstance()->getRandom(200, dHeight - 200);
		int vX = UtilMath::getInstance()->getRandom(30, 80);
		int vY = UtilMath::getInstance()->getRandom(30, 80);
		(UtilMath::getInstance()->getRandom(0, 4) < 2) ? vX *= -1 : vX *= 1;
		(UtilMath::getInstance()->getRandom(0, 4) < 2) ? vY *= -1 : vY *= 1;
		auto sprite = SpriteChicken::createSprite("images/c_chi.png", pX, pY);
		sprite->setVelocity(vX, vY);
		sprites.push_back(sprite);
	}

	return true;
}

void SceneGame::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);

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
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void SceneGame::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void SceneGame::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Test
	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		if (sprite->getPosX() < 0) sprite->setPosX(dWidth);
		if (dWidth < sprite->getPosX()) sprite->setPosX(0);
		if (sprite->getPosY() < 0) sprite->setPosY(dHeight - 80);
		if (dHeight - 80 < sprite->getPosY()) sprite->setPosY(0);
		sprite->update(delay);
	}

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=HAPPY NEW YEAR=", cX, cY - gSize * 5,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr("2021", cX, cY - gSize * 3,
									  6, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);
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