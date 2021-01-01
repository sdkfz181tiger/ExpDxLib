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

	// Background
	background = SpriteBase::createSprite("images/c_temple.png", cX, cY - gSize * 2);

	// Characters
	auto bozu = SpriteBozu::createSprite("images/c_bozu.png", cX, cY);
	bozu->changeFrames("bozu_f");
	sprites.push_back(bozu);
	auto kobo = SpriteKobozu::createSprite("images/c_kobo.png", cX - gSize * 2, cY);
	kobo->changeFrames("kobo_f");
	sprites.push_back(kobo);
	auto chicken = SpriteChicken::createSprite("images/c_chi.png", cX + gSize * 2, cY);
	chicken->changeFrames("chi_f");
	sprites.push_back(chicken);

	auto c2 = SpriteChicken::createSprite("images/c_chi.png",
										  cX + gSize * 4, cY + gSize * 2);
	c2->changeFrames("chi_r");
	sprites.push_back(c2);

	auto c3 = SpriteChicken::createSprite("images/c_chi.png",
										  cX - gSize * 3, cY + gSize * 3);
	c3->changeFrames("chi_l");
	sprites.push_back(c3);

	auto c4 = SpriteChicken::createSprite("images/c_chi.png",
										  cX - gSize * 5, cY + gSize * 1);
	c4->changeFrames("chi_d");
	sprites.push_back(c4);


	auto tanu = SpriteTanuki::createSprite("images/c_tanu.png",
										   dWidth - gSize * 2, cY + gSize * 2);
	tanu->changeFrames("tanu_l");
	sprites.push_back(tanu);

	for (int i = 0; i < 100; i++) {
		this->birth();
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

	background->update(delay);

	// Sprites
	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		if (sprite->getPosX() < 0) sprite->setPosX(dWidth);
		if (dWidth < sprite->getPosX()) sprite->setPosX(0);
		if (sprite->getPosY() < 0) sprite->setPosY(dHeight);
		if (dHeight < sprite->getPosY()) sprite->setPosY(0);
		sprite->update(delay);
	}

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=HAPPY NEW YEAR=", cX, cY - gSize * 6.0f,
									  2, UtilAlign::CENTER);

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

void SceneGame::birth() {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// New chicken
	int deg = UtilMath::getInstance()->getRandom(0, 360);
	int spd = 120;
	float vX = UtilMath::getInstance()->getCos(deg) * spd;
	float vY = UtilMath::getInstance()->getSin(deg) * spd;
	int rdm = UtilMath::getInstance()->getRandom(0, 3);
	if (rdm == 0) {
		auto spr = SpriteChicken::createSprite("images/c_chi.png", cX, cY);
		spr->setVelocity(vX, vY);
		sprites.push_back(spr);
	} else if (rdm == 1) {
		auto spr = SpriteBozu::createSprite("images/c_chi.png", cX, cY);
		spr->setVelocity(vX, vY);
		sprites.push_back(spr);
	} else if (rdm == 2) {
		auto spr = SpriteKobozu::createSprite("images/c_chi.png", cX, cY);
		spr->setVelocity(vX, vY);
		sprites.push_back(spr);
	} else {
		auto spr = SpriteTanuki::createSprite("images/c_chi.png", cX, cY);
		spr->setVelocity(vX, vY);
		sprites.push_back(spr);
	}
}