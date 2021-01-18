#include "ScenePreload.h"

ScenePreload *ScenePreload::createScene(int dWidth, int dHeight) {
	// New
	ScenePreload *scene = new ScenePreload(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

ScenePreload::ScenePreload(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
													  sceneListener(nullptr),
													  vCode(UtilJNI::getInstance()->getVersionCode()),
													  vName(UtilJNI::getInstance()->getVersionName()) {
	LOGD("Main", "ScenePreload()\n");
}

ScenePreload::~ScenePreload() {
	LOGD("Main", "~ScenePreload()\n");
	// Delete
	DX_SAFE_DELETE_VECTOR(btns);
}

bool ScenePreload::init() {
	LOGD("Main", "ScenePreload::init()\n");

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

	// TODO: test json
	const json jObj = UtilJson::getInstance()->loadJson("json/sample.json");
	const bool happy = jObj["happy"].get<bool>();
	const string name = jObj["name"].get<string>();
	const int hp = jObj["hp"].get<int>();
	LOGD("Main", "Find:%s, %d", name.c_str(), hp);

	// Connect to server
	const string url = "https://ozateck.sakura.ne.jp/shimejigames/chickader/debug/";
	const string fileName = "index.php";
	auto func = [](CallbackType type, const char *fileName) -> void {
		if (type == CallbackType::SUCCESS) {
			LOGD("Main", "Success: %d, %s", type, fileName);
			return;
		}
		if (type == CallbackType::PROGRESS) {
			LOGD("Main", "Progress: %d, %s", type, fileName);
			return;
		}
		if (type == CallbackType::ERROR) {
			LOGD("Main", "Error: %d, %s", type, fileName);
			return;
		}
	};
	UtilJNI::getInstance()->connectServer(url.c_str(), fileName.c_str(), func);

	return true;
}

void ScenePreload::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
}

void ScenePreload::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void ScenePreload::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void ScenePreload::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	// Label, Buttons
	UtilLabel::getInstance()->drawStr("==PRELOAD==", cX, 120,
									  3, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vCode, cX, 150,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vName, cX, 180,
									  2, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);
}

void ScenePreload::addSceneListener(SceneListener *listener) {
	sceneListener = listener;
}

void ScenePreload::onBtnPressed(BtnTag &tag) {
	//LOGD("Main", "onBtnPressed()");
}

void ScenePreload::onBtnCanceled(BtnTag &tag) {
	//LOGD("Main", "onBtnCanceled()");
}

void ScenePreload::onBtnReleased(BtnTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	if (tag == BtnTag::QUIT) UtilDx::getInstance()->setQuitFlg();
	if (tag == BtnTag::TITLE) {
		UtilSound::getInstance()->playSE("sounds/se_coin_01.wav");
		if (sceneListener) sceneListener->onSceneChange(SceneTag::TITLE);
	}
}