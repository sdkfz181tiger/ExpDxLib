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

	btnQuit = BtnBase::createBtn("images/box_12x12.png", "X",
								 dWidth - gSize * 1, gSize * 1);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	btnTest = BtnBase::createBtn("images/box_12x12.png", "R",
								 gSize * 1, gSize * 1);
	btnTest->addBtnListener(this, BtnTag::RESULT);
	btns.push_back(btnTest);

	// Background
	background = SpriteBase::createSprite("images/c_temple.png", cX, cY - gSize * 3);

	// Characters
	auto kobo = SpriteKobozu::createSprite("images/c_kobo.png", cX, cY);
	sprites.push_back(kobo);
	auto osho = SpriteOsho::createSprite("images/c_osho.png", cX - gSize * 3, cY);
	sprites.push_back(osho);
	auto chicken = SpriteChicken::createSprite("images/c_chi.png", cX - gSize * 4, cY + gSize * 2);
	sprites.push_back(chicken);
	auto tanuki = SpriteTanuki::createSprite("images/c_tanu.png", cX + gSize * 5, cY + gSize * 3);
	sprites.push_back(tanuki);

	// TODO: test!!
	player = SpriteChicken::createSprite("images/c_chi.png", cX, cY);

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

	// TODO: test!!
	int spd = UtilDebug::getInstance()->getGridSize() * 20;
	player->startWalk(spd, x, y);
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

	background->update(delay);// Background

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

	// TODO: test!!
	player->update(delay);

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=JUST DO IT!=", cX, cY - gSize * 6.0f,
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