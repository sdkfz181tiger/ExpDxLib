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

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png", cX, cY + gSize * 10);

	// Characters
	auto kobo = SpriteKobozu::createSprite("images/c_kobo.png", cX, cY);
	sprites.push_back(kobo);
	auto osho = SpriteOsho::createSprite("images/c_osho.png", cX - gSize * 3, cY);
	sprites.push_back(osho);
	auto chicken = SpriteChicken::createSprite("images/c_chi.png", cX - gSize * 4, cY + gSize * 2);
	sprites.push_back(chicken);
	auto tanuki = SpriteTanuki::createSprite("images/c_tanu.png", cX + gSize * 5, cY + gSize * 3);
	sprites.push_back(tanuki);

	// TODO: test json
	json jObj = UtilJson::getInstance()->loadJson("json/sample.json");
	bool happy = jObj["happy"].get<bool>();
	string name = jObj["name"].get<string>();
	int hp = jObj["hp"].get<int>();
	LOGD("Main", "Find:%s, %d", name.c_str(), hp);

	// TODO: test save
	string str1 = UtilLocalSave::getInstance()->getString("buho");
	UtilLocalSave::getInstance()->setString("buho", "kitaro");
	string str2 = UtilLocalSave::getInstance()->getString("buho");
	LOGD("Main", "%s -> %s", str1.c_str(), str2.c_str());

	// BGM
	UtilSound::getInstance()->stopBGM();
	UtilSound::getInstance()->playBGM("sounds/bgm_title.wav", false);

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
	UtilLabel::getInstance()->drawStr("==TITLE==", cX, 120,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vCode, cX, 150,
									  2, UtilAlign::CENTER);
	UtilLabel::getInstance()->drawStr(vName, cX, 180,
									  2, UtilAlign::CENTER);
	for (auto btn : btns) btn->update(delay);
}

void SceneTitle::addSceneListener(SceneListener *listener) {
	sceneListener = listener;
}

void SceneTitle::onBtnPressed(BtnTag &tag) {
	LOGD("Main", "onBtnPressed()");
}

void SceneTitle::onBtnCanceled(BtnTag &tag) {
	LOGD("Main", "onBtnCanceled()");
}

void SceneTitle::onBtnReleased(BtnTag &tag) {
	LOGD("Main", "onBtnReleased():%d", tag);
	if (tag == BtnTag::QUIT) UtilDx::getInstance()->setQuitFlg();
	if (tag == BtnTag::GAME) {
		UtilSound::getInstance()->playSE("sounds/se_coin_01.wav");
		if (sceneListener) sceneListener->onSceneChange(SceneTag::GAME);
	}
}