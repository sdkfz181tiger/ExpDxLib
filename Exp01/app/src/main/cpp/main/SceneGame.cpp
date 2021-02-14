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
												chicken(nullptr),
												tanuA(nullptr), tanuB(nullptr),
												updateMode(READY),
												waitCnt(0), waitInterval(90) {
	LOGD("Main", "SceneGame()\n");
}

SceneGame::~SceneGame() {
	LOGD("Main", "~SceneGame()\n");
	// Delete
	DX_SAFE_DELETE(background);
	DX_SAFE_DELETE(bGrid);
	DX_SAFE_DELETE(sBar);
	DX_SAFE_DELETE(dPad);
	DX_SAFE_DELETE(player);
	DX_SAFE_DELETE(chicken);
	DX_SAFE_DELETE(tanuA);
	DX_SAFE_DELETE(tanuB);
	DX_SAFE_DELETE_VECTOR(btns);
	DX_SAFE_DELETE_VECTOR(eggs);
	DX_SAFE_DELETE_VECTOR(chicks);
}

bool SceneGame::init() {
	LOGD("Main", "SceneGame::init()\n");

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Background
	background = SpriteBase::createSprite("images/c_temple_135x480.png",
										  cX, cY - gSize * 32);

	// BoardGrid
	bGrid = BoardGrid::createBoard(cX, cY + gSize * 5, gSize * 5,
								   8, 8);

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
	btnTest->addBtnListener(this, BtnTag::RESULT);

	// StatusBar
	sBar = StatusBar::create(0, 0, dWidth, gSize * 4);
	sBar->pushBtnBase(btnQuit);
	sBar->pushBtnBase(btnSound);
	sBar->pushBtnBase(btnTest);
	sBar->offsetAdHeight();
	sBar->resetScore();// Reset score
	sBar->resetBonus();// Reset bonus

	// Dpad
	dPad = CtlDpad::createDpad(cX, cY + gSize * 24);
	dPad->addDpadListener(this);

	// Player
	player = SpriteKobo::createSprite("images/c_kobo.png",
									  cX, cY - gSize * 2);
	// Osho
	osho = SpriteOsho::createSprite("images/c_osho.png",
									cX - gSize * 3, cY - gSize * 18);
	// Chicken
	chicken = SpriteChicken::createSprite("images/c_chicken_f.png",
										  cX + gSize * 3, cY - gSize * 18);
	chicken->setNext(cX, cY);
	chicken->setEggListener(this);
	// Tanu
	tanuA = SpriteTanu::createSprite("images/c_tanu.png",
									 cX - gSize * 2, cY + gSize * 4);
	tanuB = SpriteTanu::createSprite("images/c_tanu.png",
									 cX + gSize * 2, cY + gSize * 4);

	// Hopper
	MsgHopper *hopper = MsgHopper::createStr(cX, cY, 4, "READY!");
	hoppers.push_back(hopper);

	// BGM
	UtilSound::getInstance()->stopBGM();
	UtilSound::getInstance()->playBGM("sounds/bgm_ready_01.wav",
									  false, true);

	return true;
}

void SceneGame::setOnTouchBegan(int id, int x, int y) {
	//LOGD("Main", "setOnTouchBegan()[%d]:%d, %d", id, x, y);
	if (y < dHeight / 5) sBar->setOnTouchBegan(id, x, y);
	if (dHeight / 5 < y) dPad->setOnTouchBegan(id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
}

void SceneGame::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	if (sBar) sBar->setOnTouchMoved(id, x, y);
	if (dPad) dPad->setOnTouchMoved(id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void SceneGame::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	if (sBar) sBar->setOnTouchEnded(id, x, y);
	if (dPad) dPad->setOnTouchEnded(id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void SceneGame::update(const float delay) {

	// Background, Board
	//background->update(delay);
	bGrid->update(delay);

	// Mode
	switch (updateMode) {
		case READY:
			this->gameReady(delay);
			break;
		case START:
			this->gameStart(delay);
			break;
		case FINISH:
			this->gameFinish(delay);
			break;
		default:
			// Do nothing
			break;
	}

	// Hopper
	auto itS = hoppers.end();
	while (itS-- != hoppers.begin()) {
		auto hopper = static_cast<MsgHopper *>(*itS);
		hopper->update(delay);
		if (hopper->isWaiting()) continue;
		hoppers.erase(itS);
		DX_SAFE_DELETE(hopper);
	}

	// StatusBar, Dpad, Buttons
	if (sBar) sBar->update(delay);
	if (dPad) dPad->update(delay);
	for (auto btn : btns) btn->update(delay);

	this->replaceSceneTick(delay);// Tick
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
}

void SceneGame::onDpadReleased(DpadTag &tag) {
	//LOGD("Dpad", "onDpadReleased():%d", tag);
	player->startStay();// Stay
}

void SceneGame::onDpadChanged(DpadTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	if (updateMode != START) return;// Important
	int spd = UtilDebug::getInstance()->getGridSize() * 20;
	player->startStay();
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);
}

void SceneGame::gameReady(const float delay) {

	// Eggs, Chicks
	for (auto egg : eggs) egg->update(delay);
	for (auto chick : chicks) chick->update(delay);

	// Player, Osho, Chicken
	player->update(delay);
	osho->update(delay);
	chicken->update(delay);

	// Wait
	waitCnt++;
	if (waitInterval < waitCnt) {
		waitCnt = 0;
		updateMode = START;// Next
		// Hopper
		MsgHopper *hopper = MsgHopper::createStr(dWidth / 2, dHeight / 2, 4, "START!");
		hoppers.push_back(hopper);
		// BGM
		UtilSound::getInstance()->stopBGM();
		UtilSound::getInstance()->playBGM("sounds/bgm_game_01.wav",
										  true, true);
	}
}

void SceneGame::gameStart(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;
	const int gSize = UtilDebug::getInstance()->getGridSize();

	// Player x Osho
	if (player->containsPos(osho)) {
		player->startStay();// Stay
		updateMode = FINISH;// Next
		// Hopper
		MsgHopper *hopper = MsgHopper::createStr(dWidth / 2, dHeight / 2, 4, "FINISH!");
		hoppers.push_back(hopper);
		// BGM
		UtilSound::getInstance()->stopBGM();
		UtilSound::getInstance()->playBGM("sounds/bgm_omg_01.wav",
										  false, true);
	}

	// Eggs x Player or Tanu
	auto itE = eggs.end();
	while (itE-- != eggs.begin()) {
		auto egg = static_cast<SpriteEgg *>(*itE);
		egg->update(delay);
		// x Player
		if (player->containsPos(egg)) {
			this->chainChick(1, egg->getPosX(), egg->getPosY());// Chain
			eggs.erase(itE);
			DX_SAFE_DELETE(egg);
			UtilSound::getInstance()->playSE("sounds/se_get_01.wav");
			continue;
		}
		// x TanuA
		if (tanuA->containsPos(egg)) {
			if (tanuA->getItemFlg()) continue;
			tanuA->startCapture(true, false);
			eggs.erase(itE);
			DX_SAFE_DELETE(egg);
			UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
			continue;
		}
		// x TanuB
		if (tanuB->containsPos(egg)) {
			if (tanuB->getItemFlg()) continue;
			tanuB->startCapture(true, false);
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
		// x TanuA
		if (tanuA->containsPos(chick)) {
			if (tanuA->getItemFlg()) continue;
			tanuA->startCapture(false, true);
			this->purgeChick();// Purge
			UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
			continue;
		}
		// x TanuB
		if (tanuB->containsPos(chick)) {
			if (tanuB->getItemFlg()) continue;
			tanuB->startCapture(false, true);
			this->purgeChick();// Purge
			UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
			continue;
		}
	}

	// Player, Osho, Chicken, Tanu
	player->update(delay);
	osho->update(delay);
	chicken->update(delay);
	tanuA->update(delay);
	tanuB->update(delay);
}

void SceneGame::gameFinish(const float delay) {

	// Eggs, Chicks
	for (auto egg : eggs) egg->update(delay);
	for (auto chick : chicks) chick->update(delay);

	// Player, Osho, Chicken, Tanu
	player->update(delay);
	osho->update(delay);
	chicken->update(delay);
	tanuA->update(delay);
	tanuB->update(delay);

	// Wait
	waitCnt++;
	if (waitInterval < waitCnt) {
		waitCnt = 0;
		this->replaceSceneWait(0.2f, SceneTag::RESULT);// NextScene
	}
}

void SceneGame::onEggLayed(int x, int y) {

	UtilSound::getInstance()->playSE("sounds/se_egg_01.wav");

	// Egg
	auto egg = SpriteEgg::createSprite("images/c_egg.png", x, y);
	eggs.push_back(egg);

	// Chicken
	Vec2 next = bGrid->getRdmPos();
	chicken->setNext(next.x, next.y);
}

void SceneGame::chainChick(int num, int x, int y) {

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

	// ScoreBar
	sBar->addScore(10);
	sBar->setBonus(chicks.size());

	// Hopper
	MsgHopper *hopper = MsgHopper::createNum(x, y, 2, 10);
	hoppers.push_back(hopper);
}

void SceneGame::purgeChick() {
	auto itH = chicks.end() - 1;
	auto chick = static_cast<SpriteChick *>(*itH);
	chicks.erase(itH);
	DX_SAFE_DELETE(chick);
}