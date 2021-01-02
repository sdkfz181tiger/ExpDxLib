#include "SceneTitle.h"

SceneTitle *SceneTitle::createScene(int dWidth, int dHeight) {
	// New
	SceneTitle *scene = new SceneTitle(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneTitle::SceneTitle(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
												  sceneListener(nullptr),
												  btnQuit(nullptr), btnTest(nullptr) {
	LOGD("Main", "SceneTitle()\n");
}

SceneTitle::~SceneTitle() {
	LOGD("Main", "~SceneTitle()\n");
	// Delete
	DX_SAFE_DELETE(btnQuit);
	DX_SAFE_DELETE(btnTest);
}

bool SceneTitle::init() {
	LOGD("Main", "SceneTitle::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	btnQuit = BtnBase::createBtn("images/box_12x12.png", "X",
								 dWidth - gSize * 1, gSize * 1);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	btnTest = BtnBase::createBtn("images/box_12x12.png", "G",
								 gSize * 1, gSize * 1);
	btnTest->addBtnListener(this, BtnTag::GAME);
	btns.push_back(btnTest);

	// Background
	background = SpriteBase::createSprite("images/box_135x240.png", cX, cY);

	// Characters
	auto kobo = SpriteKobozu::createSprite("images/c_kobo.png", cX, cY);
	kobo->changeFrames("kobo_f", -1);
	sprites.push_back(kobo);
	auto bozu = SpriteBozu::createSprite("images/c_bozu.png", cX - gSize * 3, cY);
	bozu->changeFrames("bozu_f", -1);
	sprites.push_back(bozu);
	auto chicken = SpriteChicken::createSprite("images/c_chi.png", cX - gSize * 4, cY + gSize * 2);
	chicken->changeFrames("chi_f", -1);
	sprites.push_back(chicken);
	auto tanuki = SpriteTanuki::createSprite("images/c_tanu.png", cX + gSize * 5, cY + gSize * 3);
	tanuki->changeFrames("tanu_f", -1);
	sprites.push_back(tanuki);

	return true;
}

void SceneTitle::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
}

void SceneTitle::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void SceneTitle::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void SceneTitle::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	background->update(delay);// Background

	for (auto sprite : sprites) sprite->update(delay);// Sprites

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=TITLE=", cX, 120,
									  2, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);
}

void SceneTitle::addSceneListener(SceneListener *sceneListener) {
	this->sceneListener = sceneListener;
}

void SceneTitle::onBtnPressed(BtnTag &tag) {
	LOGD("Main", "onBtnPressed()");
}

void SceneTitle::onBtnCanceled(BtnTag &tag) {
	LOGD("Main", "onBtnCanceled()");
}

void SceneTitle::onBtnReleased(BtnTag &tag) {
	LOGD("Main", "onBtnReleased():%d", tag);
	if (tag == BtnTag::QUIT) {
		UtilDx::getInstance()->setQuitFlg();
	}
	if (tag == BtnTag::GAME) {
		UtilSound::getInstance()->playSE("se_coin_01.wav");
		if (sceneListener) sceneListener->onSceneChange(SceneTag::GAME);
	}
}