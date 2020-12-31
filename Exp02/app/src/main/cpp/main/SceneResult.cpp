#include "SceneResult.h"

SceneResult *SceneResult::createScene(int dWidth, int dHeight) {
	// New
	SceneResult *scene = new SceneResult(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneResult::SceneResult(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
													sceneListener(nullptr),
													btnQuit(nullptr), btnTest(nullptr) {
	LOGD("Main", "SceneResult()\n");
}

SceneResult::~SceneResult() {
	LOGD("Main", "~SceneResult()\n");
	// Delete
	DX_SAFE_DELETE(btnQuit);
	DX_SAFE_DELETE(btnTest);
}

bool SceneResult::init() {
	LOGD("Main", "SceneResult::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	btnQuit = BtnBase::createBtn("images/box_16x16.png", "Q",
								 dWidth - gSize * 1, gSize);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	btnTest = BtnBase::createBtn("images/box_16x16.png", "T",
								 dWidth - gSize * 3, gSize);
	btnTest->addBtnListener(this, BtnTag::TITLE);
	btns.push_back(btnTest);

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

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("=RESULT=", cX, 120,
									  5, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);
}

void SceneResult::addSceneListener(SceneListener *sceneListener) {
	this->sceneListener = sceneListener;
}

void SceneResult::onBtnPressed(BtnTag &tag) {
	LOGD("Main", "onBtnPressed()");
}

void SceneResult::onBtnCanceled(BtnTag &tag) {
	LOGD("Main", "onBtnCanceled()");
}

void SceneResult::onBtnReleased(BtnTag &tag) {
	LOGD("Main", "onBtnReleased():%d", tag);
	if (tag == BtnTag::QUIT) {
		UtilDx::getInstance()->setQuitFlg();
	}
	if (tag == BtnTag::TITLE) {
		UtilSound::getInstance()->playSE("se_coin_01.wav");
		if (sceneListener) sceneListener->onSceneChange(SceneTag::TITLE);
	}
}