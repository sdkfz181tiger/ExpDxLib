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
													  vName(UtilJNI::getInstance()->getVersionName()),
													  dUrl("https://ozateck.sakura.ne.jp/shimejigames/chickader/debug/"),
													  dMsg("***") {
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

	// Connect to server
	const string fileName = "index.php";
	auto func = [&](CallbackType type, const char *fileName) -> void {
		if (type == CallbackType::SUCCESS) {
			LOGD("Main", "Success: %d, %s", type, fileName);
			this->downloadJson(fileName);// Json
			return;
		}
		if (type == CallbackType::PROGRESS) {
			LOGD("Main", "Progress: %d, %s", type, fileName);
			// Do nothing
			return;
		}
		if (type == CallbackType::ERROR) {
			LOGE("Main", "Error: %d, %s", type, fileName);
			this->downloadJson(fileName);// Json
			return;
		}
	};
	UtilJNI::getInstance()->connectServer(dUrl.c_str(), fileName.c_str(), func);

	return true;
}

void ScenePreload::downloadJson(const char *fileName) {
	//LOGD("Main", "downloadJson()");
	const string fullPath = UtilJNI::getInstance()->getFilePath() + fileName;
	const json jObj = UtilJson::getInstance()->loadJson(fullPath.c_str());
	const char *key = "time";
	if (jObj.find(key) == jObj.end()) {
		LOGW("Main", "Please connect to internet!!");
		dMsg = "PLEASE CONNECT TO INTERNET";// Message
		UtilLocalSave::getInstance()->setString(key, "");// Reset
		return;
	}
	const string jTime = jObj[key].get<string>();
	const string sTime = UtilLocalSave::getInstance()->getString(key);
	LOGD("Main", "jTime:%s <-> sTime:%s", jTime.c_str(), sTime.c_str());
	if (sTime.length() == 0) {
		LOGW("Main", "Downloding assets!!");
		dMsg = "DOWNLOADING ASSETS";// Message
		UtilLocalSave::getInstance()->setString(key, jTime);
		this->downloadAssets(jObj);// Download all assets
		return;
	}
	if (jTime != sTime) {
		LOGW("Main", "Updating assets!!");
		dMsg = "UPDATING ASSETS";// Message
		UtilLocalSave::getInstance()->setString(key, jTime);
		this->downloadAssets(jObj);// Update all assets
		return;
	}
	LOGW("Main", "Starting game!!");
	dMsg = "STARTING GAME";// Message
	UtilLocalSave::getInstance()->setString(key, jTime);
	// TODO: start game!!
}

void ScenePreload::downloadAssets(const json &jObj) {
	LOGD("Main", "downloadAssets()");
	const json jArr = jObj["assets"];
	for (string fileName : jArr) fileNames.push_back(fileName);
	this->downloadImages();
}

void ScenePreload::downloadImages() {
	LOGD("Main", "downloadImages():%d", fileNames.size());
	if (fileNames.empty()) {
		LOGD("Main", "Completed!!");
		dMsg = "COMPLETED";// Message
		// TODO: start game!!
		return;
	}

	auto func = [&](CallbackType type, const char *fileName) -> void {
		if (type == CallbackType::SUCCESS) {
			LOGD("Main", "Success: %d, %s", type, fileName);
			dMsg = UtilLabel::getInstance()->toUpper(fileName);// Message
			this->downloadImages();// Recursive
			return;
		}
		if (type == CallbackType::PROGRESS) {
			LOGD("Main", "Progress: %d, %s", type, fileName);
			// Do nothing
			return;
		}
		if (type == CallbackType::ERROR) {
			LOGE("Main", "Error: %d, %s", type, fileName);
			dMsg = "ERROR";// Message
			UtilLocalSave::getInstance()->setString("time", "");// Reset
			return;
		}
	};

	const string fileName = fileNames.back();
	fileNames.pop_back();
	UtilJNI::getInstance()->connectServer(dUrl.c_str(), fileName.c_str(), func);
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
	UtilLabel::getInstance()->drawStr(dMsg, cX, cY,
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