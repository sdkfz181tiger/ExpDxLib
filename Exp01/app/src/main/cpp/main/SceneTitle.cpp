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
	DX_SAFE_DELETE(sBar);
	DX_SAFE_DELETE_VECTOR(btns);
}

bool SceneTitle::init() {
	LOGD("Main", "SceneTitle::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png",
										  cX, cY + gSize * 34);

	// Quit, Sound
	BtnBase *btnQuit = BtnBase::createBtn("images/c_quit.png",
										  dWidth - gSize * 2, gSize * 2);
	btnQuit->addBtnListener(this, BtnTag::QUIT);

	BtnToggle *btnSound = BtnToggle::createToggle("images/c_sound_on.png",
												  "images/c_sound_off.png",
												  dWidth - gSize * 6, gSize * 2);
	btnSound->addBtnListener(this, BtnTag::SOUND);

	BtnBase *btnTest = BtnBase::createBtn("images/box_12x12.png",
										  dWidth - gSize * 2, gSize * 6);
	btnTest->addBtnListener(this, BtnTag::GAME);

	// StatusBar
	sBar = StatusBar::create(0, 0, dWidth, gSize * 4);
	sBar->pushBtnBase(btnQuit);
	sBar->pushBtnBase(btnSound);
	sBar->pushBtnBase(btnTest);
	sBar->offsetAdHeight();

	// Characters
	auto osho = SpriteOsho::createSprite("images/c_osho.png", cX, cY);
	sprites.push_back(osho);

	// BGM
	UtilSound::getInstance()->stopBGM();
	UtilSound::getInstance()->playBGM("sounds/bgm_title.wav", false, true);

	return true;
}

void SceneTitle::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	if (y < dHeight / 5) sBar->setOnTouchBegan(id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
}

void SceneTitle::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	if (sBar) sBar->setOnTouchMoved(id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void SceneTitle::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	if (sBar) sBar->setOnTouchEnded(id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void SceneTitle::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	background->update(delay);// Background

	for (auto sprite : sprites) sprite->update(delay);// Sprites

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=TITLE=", cX, cY - gSize * 10,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vCode, cX, 150,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vName, cX, 180,
									  2, UtilAlign::CENTER);

	// StatusBar, Buttons
	if (sBar) sBar->update(delay);
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