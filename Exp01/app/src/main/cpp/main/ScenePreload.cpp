#include "ScenePreload.h"

ScenePreload *ScenePreload::createScene(int dWidth, int dHeight) {
	// New
	ScenePreload *scene = new ScenePreload(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

ScenePreload::ScenePreload(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
													  vCode(UtilJNI::getInstance()->getVersionCode()),
													  vName(UtilJNI::getInstance()->getVersionName()),
													  dUrl("https://sdkfz181tiger.github.io/chickader/"),
													  dPrefix(UtilJNI::getInstance()->getDebugFlg()
															  ? "debug/" : "release/") {
	LOGD("Main", "ScenePreload()\n");
}

ScenePreload::~ScenePreload() {
	LOGD("Main", "~ScenePreload()\n");
	// Delete
	DX_SAFE_DELETE(lMarker);
	DX_SAFE_DELETE_VECTOR(btns);
}

bool ScenePreload::init() {
	LOGD("Main", "ScenePreload::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Callback
	const string url = dUrl + dPrefix;
	const string fileName = "index.json";
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

	// JNI
	UtilJNI::getInstance()->connectAdMob();
	UtilJNI::getInstance()->connectGitHub(url.c_str(), fileName.c_str(), func);

	// LoadingMarker
	lMarker = new LoadingMarker(cX, cY, gSize * 10, gSize / 4);

	return true;
}

void ScenePreload::downloadJson(const char *fileName) {
	//LOGD("Main", "downloadJson()");
	const string fullPath = UtilJNI::getInstance()->getFilePath() + fileName;
	const json jObj = UtilJson::getInstance()->loadJson(fullPath.c_str());
	const char *key = "time";

	if (jObj.find(key) == jObj.end()) {
		LOGW("Main", "Please connect to internet!!");
		lMarker->setMsg("PLEASE CONNECT TO INTERNET");// Message
		UtilLocalSave::getInstance()->setString(key, "");// Reset
		return;
	}

	const string jTime = jObj[key].get<string>();
	const string sTime = UtilLocalSave::getInstance()->getString(key);
	LOGD("Main", "jTime:%s <-> sTime:%s", jTime.c_str(), sTime.c_str());
	if (sTime.length() == 0) {
		LOGD("Main", "Downloding assets!!");
		lMarker->setMsg("DOWNLOADING");// Message
		UtilLocalSave::getInstance()->setString(key, jTime);
		this->downloadAssets(jObj);// Download all assets
		return;
	}

	if (jTime != sTime) {
		LOGD("Main", "Updating assets!!");
		lMarker->setMsg("UPDATING");// Message
		UtilLocalSave::getInstance()->setString(key, jTime);
		this->downloadAssets(jObj);// Update all assets
		return;
	}

	if (!this->checkAssets(jObj)) {
		LOGD("Main", "Redownloading assets!!");
		lMarker->setMsg("REDOWNLOADING");// Message
		UtilLocalSave::getInstance()->setString(key, jTime);
		this->downloadAssets(jObj);// Redownload all assets
		return;
	}

	LOGD("Main", "Starting game!!");
	lMarker->setMsg("STARTING");// Message
	this->replaceSceneWait(1.0f, SceneTag::TITLE);// Title
}

void ScenePreload::downloadAssets(const json &jObj) {
	LOGD("Main", "downloadAssets()");
	const json jArr = jObj["assets"];
	for (string fileName : jArr) fileNames.push_back(fileName);
	lMarker->setCnt(0);// Reset
	lMarker->setTotal(fileNames.size());// Total
	this->downloadImages();
}

void ScenePreload::downloadImages() {
	LOGD("Main", "downloadImages():%lu", fileNames.size());
	if (fileNames.empty()) {
		LOGD("Main", "Completed!!");
		lMarker->setMsg("COMPLETED");
		lMarker->progress(1);// Progress
		this->replaceSceneWait(1.0f, SceneTag::TITLE);// Title
		return;
	}

	auto func = [&](CallbackType type, const char *fileName) -> void {
		if (type == CallbackType::SUCCESS) {
			LOGD("Main", "Success: %d, %s", type, fileName);
			lMarker->setMsg("LOADING");
			lMarker->progress(1);// Progress
			this->downloadImages();// Recursive
			return;
		}
		if (type == CallbackType::PROGRESS) {
			LOGD("Main", "Progress: %d, %s", type, fileName);
			int rdm = UtilMath::getInstance()->getRandom(0, 10);
			const string msg = (rdm % 2 == 0) ? "L A I G " : " O D N ";
			lMarker->setMsg(msg.c_str());
			return;
		}
		if (type == CallbackType::ERROR) {
			LOGE("Main", "Error: %d, %s", type, fileName);
			lMarker->setMsg("ERROR");
			UtilLocalSave::getInstance()->setString("time", "");// Reset
			return;
		}
	};

	const string url = dUrl + dPrefix;
	const string fileName = fileNames.back();
	fileNames.pop_back();
	UtilJNI::getInstance()->connectGitHub(url.c_str(), fileName.c_str(), func);
}

bool ScenePreload::checkAssets(const json &jObj) {
	LOGD("Main", "checkAssets()");
	const json jArr = jObj["assets"];
	for (string fileName : jArr) {
		const string fullPath = UtilJNI::getInstance()->getFilePath() + fileName;
		if (!UtilDx::getInstance()->isFileExists(fullPath)) return false;
	}
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
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Label
	UtilLabel::getInstance()->drawStr(vName, dWidth - gSize / 2, dHeight - gSize / 2,
									  2, UtilAlign::RIGHT);

	lMarker->update();// Loading

	this->replaceSceneTick(delay);// NextScene
}

void ScenePreload::onBtnPressed(BtnTag &tag) {
	//LOGD("Main", "onBtnPressed()");
}

void ScenePreload::onBtnCanceled(BtnTag &tag) {
	//LOGD("Main", "onBtnCanceled()");
}

void ScenePreload::onBtnReleased(BtnTag &tag) {
	//LOGD("Main", "onBtnReleased()");
}