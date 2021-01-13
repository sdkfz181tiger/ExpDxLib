#include "SceneGame.h"

SceneGame *SceneGame::createScene(int dWidth, int dHeight) {
	// New
	SceneGame *scene = new SceneGame(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneGame::SceneGame(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
												sceneListener(nullptr),
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
	DX_SAFE_DELETE_VECTOR(sprites);
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
	player = SpriteKobozu::createSprite("images/c_chi.png", cX, cY);

	// Characters
	auto osho = SpriteOsho::createSprite("images/c_osho.png", cX - gSize * 3, cY);
	sprites.push_back(osho);
	auto chicken = SpriteChicken::createSprite("images/c_chi.png", cX - gSize * 4, cY + gSize * 2);
	sprites.push_back(chicken);
	auto hiyo1 = SpriteHiyo::createSprite("images/c_hiyo.png", cX - gSize * 4, cY + gSize * 4);
	sprites.push_back(hiyo1);
	auto hiyo2 = SpriteHiyo::createSprite("images/c_hiyo.png", cX - gSize * 5, cY + gSize * 4);
	sprites.push_back(hiyo2);
	auto hiyo3 = SpriteHiyo::createSprite("images/c_hiyo.png", cX - gSize * 6, cY + gSize * 4);
	sprites.push_back(hiyo3);
	auto tanuki = SpriteTanuki::createSprite("images/c_tanu.png", cX + gSize * 5, cY + gSize * 3);
	sprites.push_back(tanuki);

	// BGM
	UtilSound::getInstance()->stopBGM();
	UtilSound::getInstance()->playBGM("sounds/bgm_game.wav", true);

	return true;
}

void SceneGame::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
	if (dHeight / 2 < y) dPad->setOnTouchBegan(id, x, y);

	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		if (sprite->containsPoint(x, y)) {
			LOGD("Main", "Contains!!");
		}
	}
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

	// Background, Board, Player
	background->update(delay);
	bGrid->update(delay);
	player->update(delay);

	// Sprites
	auto it = sprites.end();
	while (it-- != sprites.begin()) {
		auto sprite = static_cast<SpriteBase *>(*it);
		if (sprite->getPosX() < 0) sprite->setPosX(dWidth);
		if (dWidth < sprite->getPosX()) sprite->setPosX(0);
		if (sprite->getPosY() < 0) sprite->setPosY(dHeight);
		if (dHeight < sprite->getPosY()) sprite->setPosY(0);
		sprite->update(delay);
	}

	// Label
	UtilLabel::getInstance()->drawStr("GAME START!!", cX, cY - gSize * 8,
									  2, UtilAlign::CENTER);

	// Buttons, Dpad
	for (auto btn : btns) btn->update(delay);
	if (dPad) dPad->update(delay);
}

void SceneGame::addSceneListener(SceneListener *listener) {
	sceneListener = listener;
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
		if (sceneListener) sceneListener->onSceneChange(SceneTag::RESULT);
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
}

void SceneGame::onDpadReleased(DpadTag &tag) {
	//LOGD("Dpad", "onDpadReleased():%d", tag);
	player->startStay();// Stay
}

void SceneGame::onDpadChanged(DpadTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	int spd = UtilDebug::getInstance()->getGridSize() * 5;
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);
}