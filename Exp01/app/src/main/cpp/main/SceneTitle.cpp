#include "SceneTitle.h"

SceneTitle *SceneTitle::createScene(int dWidth, int dHeight) {
	// New
	SceneTitle *scene = new SceneTitle(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneTitle::SceneTitle(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
												  background(nullptr),
												  vCode(UtilJNI::getInstance()->getVersionCode()),
												  vName(UtilJNI::getInstance()->getVersionName()) {
	LOGD("Main", "SceneTitle()\n");
}

SceneTitle::~SceneTitle() {
	LOGD("Main", "~SceneTitle()\n");
	// Delete
	DX_SAFE_DELETE(background);
	DX_SAFE_DELETE_VECTOR(btns);
}

bool SceneTitle::init() {
	LOGD("Main", "SceneTitle::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	BtnBase *btnQuit = BtnBase::createBtn("images/box_12x12.png", "X",
										  dWidth - gSize * 1, gSize * 1);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	BtnBase *btnTest = BtnBase::createBtn("images/box_12x12.png", "G",
										  gSize * 1, gSize * 1);
	btnTest->addBtnListener(this, BtnTag::GAME);
	btns.push_back(btnTest);

	BtnToggle *btnSound = BtnToggle::createToggle("images/box_12x12.png", "S",
												  dWidth - gSize * 3, gSize * 1);
	btnSound->addBtnListener(this, BtnTag::SOUND);
	btns.push_back(btnSound);

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png", cX, cY + gSize * 10);

	// Characters
	auto osho = SpriteOsho::createSprite("images/c_osho.png", cX + gSize * 3, cY);
	sprites.push_back(osho);
	auto chick = SpriteChick::createSprite("images/c_chi_m.png", cX, cY);
	sprites.push_back(chick);
	auto hiyo1 = SpriteHiyo::createSprite("images/c_hiyo.png", cX + gSize * 1, cY + gSize * 1.5f);
	sprites.push_back(hiyo1);
	auto hiyo2 = SpriteHiyo::createSprite("images/c_hiyo.png", cX + gSize * 2, cY + gSize * 1.5f);
	sprites.push_back(hiyo2);
	auto tanu = SpriteTanu::createSprite("images/c_tanu.png", cX - gSize * 3, cY);
	sprites.push_back(tanu);


	// BGM
	UtilSound::getInstance()->stopBGM();
	UtilSound::getInstance()->playBGM("sounds/bgm_title.wav", false, true);

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
	UtilLabel::getInstance()->drawStr("==REALLY==", cX, 120,
									  3, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vCode, cX, 150,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vName, cX, 180,
									  2, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);

	this->replaceSceneTick(delay);// NextScene
}

void SceneTitle::onBtnPressed(BtnTag &tag) {
	//LOGD("Main", "onBtnPressed()");
}

void SceneTitle::onBtnCanceled(BtnTag &tag) {
	//LOGD("Main", "onBtnCanceled()");
}

void SceneTitle::onBtnReleased(BtnTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	if (tag == BtnTag::QUIT) UtilDx::getInstance()->setQuitFlg();
	if (tag == BtnTag::GAME) {
		UtilSound::getInstance()->playSE("sounds/se_coin_01.wav");
		this->replaceSceneWait(0.2f, SceneTag::GAME);
	}
}