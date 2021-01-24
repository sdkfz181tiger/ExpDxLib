#include "SceneGame.h"

SceneGame *SceneGame::createScene(int dWidth, int dHeight) {
	// New
	SceneGame *scene = new SceneGame(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneGame::SceneGame(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
												background(nullptr), bGrid(nullptr),
												dPad(nullptr), player(nullptr) {
	LOGD("Main", "SceneGame()\n");
}

SceneGame::~SceneGame() {
	LOGD("Main", "~SceneGame()\n");
	// Delete
	DX_SAFE_DELETE(background);
	DX_SAFE_DELETE(bGrid);
	DX_SAFE_DELETE(dPad);
	DX_SAFE_DELETE(player);
	DX_SAFE_DELETE_VECTOR(btns);
	DX_SAFE_DELETE_VECTOR(eggs);
	DX_SAFE_DELETE_VECTOR(hiyos);
}

bool SceneGame::init() {
	LOGD("Main", "SceneGame::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	BtnBase *btnQuit = BtnBase::createBtn("images/box_12x12.png", "X",
										  dWidth - gSize * 1, gSize * 1);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	BtnBase *btnTest = BtnBase::createBtn("images/box_12x12.png", "R",
										  gSize * 1, gSize * 1);
	btnTest->addBtnListener(this, BtnTag::RESULT);
	btns.push_back(btnTest);

	BtnToggle *btnSound = BtnToggle::createToggle("images/box_12x12.png", "S",
												  dWidth - gSize * 3, gSize * 1);
	btnSound->addBtnListener(this, BtnTag::SOUND);
	btns.push_back(btnSound);

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png", cX, cY - gSize * 18);

	// BoardGrid
	bGrid = BoardGrid::createBoard(cX, cY, gSize * 2, 9, 9);

	// Dpad
	dPad = CtlDpad::createDpad(cX, cY + gSize * 10);
	dPad->addDpadListener(this);

	// Player
	player = SpriteKobo::createSprite("images/c_kobo.png", cX + gSize * 1, cY - gSize * 2);

	// Eggs
	for (int i = 0; i < 30; i++) {
		int x = UtilMath::getInstance()->getRandom(0, dWidth);
		int y = UtilMath::getInstance()->getRandom(0, dHeight);
		auto egg = SpriteItem::createSprite("images/c_egg.png", x, y);
		eggs.push_back(egg);
	}

	// Hiyos
	for (int i = 0; i < 10; i++) {
		int x = player->getPosX();
		int y = player->getPosY();
		auto hiyo = SpriteHiyo::createSprite("images/c_hiyo.png", x, y);
		hiyos.push_back(hiyo);
	}
	hiyos.at(0)->setTarget(player);
	for (int i = 1; i < hiyos.size(); i++) {
		hiyos.at(i)->setTarget(hiyos.at(i - 1));
	}

	UtilSound::getInstance()->stopBGM();// BGM

	return true;
}

void SceneGame::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
	if (dHeight / 2 < y) dPad->setOnTouchBegan(id, x, y);
}

void SceneGame::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
	if (dPad) dPad->setOnTouchMoved(id, x, y);
}

void SceneGame::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
	if (dPad) dPad->setOnTouchEnded(id, x, y);
}

void SceneGame::update(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Background, Board
	background->update(delay);
	bGrid->update(delay);

	// Eggs
	auto itE = eggs.end();
	while (itE-- != eggs.begin()) {
		auto egg = static_cast<SpriteItem *>(*itE);
		egg->update(delay);
		if (player->containsPoint(egg->getPosX(), egg->getPosY())) {
			UtilSound::getInstance()->playSE("sounds/se_get_01.wav");
			eggs.erase(itE);
			DX_SAFE_DELETE(egg);
		}
	}

	// Hiyos
	auto itH = hiyos.end();
	while (itH-- != hiyos.begin()) {
		auto hiyo = static_cast<SpriteHiyo *>(*itH);
		hiyo->update(delay);
	}

	// Player
	player->update(delay);

	// Label
	UtilLabel::getInstance()->drawStr("GAME START!!", cX, cY - gSize * 12,
									  2, UtilAlign::CENTER);

	// Buttons, Dpad
	for (auto btn : btns) btn->update(delay);
	if (dPad) dPad->update(delay);

	this->replaceSceneTick(delay);// NextScene
}

void SceneGame::onBtnPressed(BtnTag &tag) {
	LOGD("Main", "onBtnPressed()");
}

void SceneGame::onBtnCanceled(BtnTag &tag) {
	LOGD("Main", "onBtnCanceled()");
}

void SceneGame::onBtnReleased(BtnTag &tag) {
	LOGD("Main", "onBtnReleased():%d", tag);
	if (tag == BtnTag::QUIT) UtilDx::getInstance()->setQuitFlg();
	if (tag == BtnTag::RESULT) {
		UtilSound::getInstance()->playSE("sounds/se_coin_01.wav");
		this->replaceSceneWait(0.2f, SceneTag::RESULT);
	}
}

void SceneGame::onDpadPressed(DpadTag &tag) {
	//LOGD("Dpad", "onDpadPressed():%d", tag);
	int spd = UtilDebug::getInstance()->getGridSize() * 5;
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);
}

void SceneGame::onDpadCanceled(DpadTag &tag) {
	//LOGD("Dpad", "onDpadCanceled():%d", tag);
	player->startStay();// Stay
	UtilSound::getInstance()->stopBGM();// BGM
}

void SceneGame::onDpadReleased(DpadTag &tag) {
	//LOGD("Dpad", "onDpadReleased():%d", tag);
	player->startStay();// Stay
	UtilSound::getInstance()->stopBGM();// BGM
}

void SceneGame::onDpadChanged(DpadTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	int spd = UtilDebug::getInstance()->getGridSize() * 6;
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);

	//UtilSound::getInstance()->stopBGM();// BGM
	//UtilSound::getInstance()->playBGM("sounds/bgm_walk_01.wav", true, true);
}