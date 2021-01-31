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
												dPad(nullptr), sBar(nullptr),
												player(nullptr), osho(nullptr),
												chicken(nullptr), tanu(nullptr) {
	LOGD("Main", "SceneGame()\n");
}

SceneGame::~SceneGame() {
	LOGD("Main", "~SceneGame()\n");
	// Delete
	DX_SAFE_DELETE(background);
	DX_SAFE_DELETE(bGrid);
	DX_SAFE_DELETE(dPad);
	DX_SAFE_DELETE(sBar);
	DX_SAFE_DELETE(player);
	DX_SAFE_DELETE(chicken);
	DX_SAFE_DELETE(tanu);
	DX_SAFE_DELETE_VECTOR(btns);
	DX_SAFE_DELETE_VECTOR(eggs);
	DX_SAFE_DELETE_VECTOR(chicks);
}

bool SceneGame::init() {
	LOGD("Main", "SceneGame::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	BtnBase *btnQuit = BtnBase::createBtn("images/box_12x12.png", "X",
										  dWidth - gSize * 1, gSize * 6);
	btnQuit->addBtnListener(this, BtnTag::QUIT);
	btns.push_back(btnQuit);

	BtnBase *btnTest = BtnBase::createBtn("images/box_12x12.png", "R",
										  gSize * 1, gSize * 6);
	btnTest->addBtnListener(this, BtnTag::RESULT);
	btns.push_back(btnTest);

	BtnToggle *btnSound = BtnToggle::createToggle("images/box_12x12.png", "S",
												  dWidth - gSize * 3, gSize * 6);
	btnSound->addBtnListener(this, BtnTag::SOUND);
	btns.push_back(btnSound);

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png", cX, cY - gSize * 18);

	// BoardGrid
	bGrid = BoardGrid::createBoard(cX, cY, gSize * 2, 9, 9);

	// Dpad
	dPad = CtlDpad::createDpad(cX, cY + gSize * 10);
	dPad->addDpadListener(this);

	// ScoreBar
	sBar = ScoreBar::create(0, 0, dWidth, gSize * 2);

	// Player
	player = SpriteKobo::createSprite("images/c_kobo.png", cX + gSize * 1, cY - gSize * 2);
	osho = SpriteOsho::createSprite("images/c_osho.png", cX - gSize * 3, cY - gSize * 12);
	// Chicken
	chicken = SpriteChicken::createSprite("images/c_chicken_f.png", cX + gSize * 3,
										  cY - gSize * 12);
	chicken->setEggListener(this);
	// Tanu
	tanu = SpriteTanu::createSprite("images/c_tanu.png", cX, cY + gSize * 4);

	UtilSound::getInstance()->stopBGM();// BGM

	return true;
}

void SceneGame::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
	if (dHeight / 5 < y) dPad->setOnTouchBegan(id, x, y);
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

	// Eggs x Player or Tanu
	auto itE = eggs.end();
	while (itE-- != eggs.begin()) {
		auto egg = static_cast<SpriteEgg *>(*itE);
		egg->update(delay);
		// x Player
		if (player->containsPos(egg)) {
			this->chainChick(1);// Chain
			eggs.erase(itE);
			DX_SAFE_DELETE(egg);
			UtilSound::getInstance()->playSE("sounds/se_get_01.wav");
			continue;
		}
		// x Tanu
		if (tanu->containsPos(egg)) {
			if (tanu->getItemFlg()) continue;
			tanu->startCapture(true, false);
			eggs.erase(itE);
			DX_SAFE_DELETE(egg);
			UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
			continue;
		}
	}

	// Chicks x Tanu
	auto itH = chicks.end();
	while (itH-- != chicks.begin()) {
		auto chick = static_cast<SpriteChick *>(*itH);
		chick->update(delay);
		// x Tanu
		if (tanu->containsPos(chick)) {
			if (tanu->getItemFlg()) continue;
			tanu->startCapture(false, true);
			this->purgeChick();// Purge
			UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
			continue;
		}
	}

	// Player, Osho, Chicken, Tanu
	player->update(delay);
	osho->update(delay);
	chicken->update(delay);
	tanu->update(delay);

	// Label
	UtilLabel::getInstance()->drawStr("GAME START!!", cX, cY - gSize * 12,
									  2, UtilAlign::CENTER);

	// UI
	if (dPad) dPad->update(delay);
	if (sBar) sBar->update(delay);
	for (auto btn : btns) btn->update(delay);

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
	player->startStay();
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);
}

void SceneGame::onEggLayed(int x, int y) {

	UtilSound::getInstance()->playSE("sounds/se_egg_01.wav");

	// Egg
	auto egg = SpriteEgg::createSprite("images/c_egg.png", x, y);
	eggs.push_back(egg);
}

void SceneGame::chainChick(int num) {

	// Chains x Player
	if (chicks.size() == 0) {
		auto chick = SpriteChick::createSprite("images/c_chick.png",
											   player->getPosX(),
											   player->getPosY());
		chick->setTarget(player);
		chicks.push_back(chick);
		num--;// Decrement
	}
	// Chains x Chick
	for (int i = 0; i < num; i++) {
		size_t last = chicks.size() - 1;
		auto chick = SpriteChick::createSprite("images/c_chick.png",
											   chicks.at(last)->getPosX(),
											   chicks.at(last)->getPosY());
		chick->setTarget(chicks.at(last));
		chicks.push_back(chick);
	}
}

void SceneGame::purgeChick() {
	auto itH = chicks.end() - 1;
	auto chick = static_cast<SpriteChick *>(*itH);
	chicks.erase(itH);
	DX_SAFE_DELETE(chick);
}