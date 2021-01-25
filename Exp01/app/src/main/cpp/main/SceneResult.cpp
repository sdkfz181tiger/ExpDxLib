#include "SceneResult.h"

SceneResult *SceneResult::createScene(int dWidth, int dHeight) {
	// New
	SceneResult *scene = new SceneResult(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneResult::SceneResult(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
													background(nullptr) {
	LOGD("Main", "SceneResult()\n");
}

SceneResult::~SceneResult() {
	LOGD("Main", "~SceneResult()\n");
	// Delete
	DX_SAFE_DELETE(background);
	DX_SAFE_DELETE_VECTOR(btns);
}

bool SceneResult::init() {
	LOGD("Main", "SceneResult::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	BtnBase *btnQuit = BtnBase::createBtn("images/box_12x12.png", "X",
										  dWidth - gSize * 1, gSize * 1);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	BtnBase *btnTest = BtnBase::createBtn("images/box_12x12.png", "T",
										  gSize * 1, gSize * 1);
	btnTest->addBtnListener(this, BtnTag::TITLE);
	btns.push_back(btnTest);

	BtnToggle *btnSound = BtnToggle::createToggle("images/box_12x12.png", "S",
												  dWidth - gSize * 3, gSize * 1);
	btnSound->addBtnListener(this, BtnTag::SOUND);
	btns.push_back(btnSound);

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png", cX, cY);

	// BGM
	UtilSound::getInstance()->stopBGM();
	UtilSound::getInstance()->playBGM("sounds/bgm_result_ng.wav", false, true);

	return true;
}

void SceneResult::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
}

void SceneResult::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void SceneResult::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void SceneResult::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	background->update(delay);// Background

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=RESULT=", cX, 120,
									  2, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);

	this->replaceSceneTick(delay);// NextScene
}

void SceneResult::onBtnPressed(BtnTag &tag) {
	//LOGD("Main", "onBtnPressed()");
}

void SceneResult::onBtnCanceled(BtnTag &tag) {
	//LOGD("Main", "onBtnCanceled()");
}

void SceneResult::onBtnReleased(BtnTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	if (tag == BtnTag::QUIT) UtilDx::getInstance()->setQuitFlg();
	if (tag == BtnTag::TITLE) {
		UtilSound::getInstance()->playSE("sounds/se_coin_01.wav");
		this->replaceSceneWait(0.2f, SceneTag::TITLE);
	}
}