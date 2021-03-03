#include "SceneGame.h"

SceneGame *SceneGame::createScene(int dWidth, int dHeight) {
	// New
	SceneGame *scene = new SceneGame(dWidth, dHeight);
	if (scene && scene->init()) return scene;
	DX_SAFE_DELETE(scene);
	return nullptr;
}

SceneGame::SceneGame(int dWidth, int dHeight) : SceneBase(dWidth, dHeight),
												background(nullptr), mManager(nullptr),
												dPad(nullptr), sBar(nullptr),
												player(nullptr), osho(nullptr),
												chicken(nullptr),
												updateMode(READY),
												waitCnt(0), waitInterval(150) {
	LOGD("Main", "SceneGame()\n");
}

SceneGame::~SceneGame() {
	LOGD("Main", "~SceneGame()\n");
	// Delete
	DX_SAFE_DELETE(background);
	DX_SAFE_DELETE(mManager);
	DX_SAFE_DELETE(sBar);
	DX_SAFE_DELETE(dPad);
	DX_SAFE_DELETE(player);
	DX_SAFE_DELETE(chicken);
	DX_SAFE_DELETE_VECTOR(tanus);
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

	// MazeManager
	mManager = MazeManager::createBoard(cX, cY, gSize * 3, gSize / 2);

	// Quit, Sound
	BtnBase *btnQuit = BtnBase::createBtn("images/c_quit.png",
										  gSize * 2, gSize * 2);
	btnQuit->addBtnListener(this, BtnTag::QUIT);

	BtnToggle *btnSound = BtnToggle::createToggle("images/c_sound_on.png",
												  "images/c_sound_off.png",
												  dWidth - gSize * 2, gSize * 2);
	btnSound->addBtnListener(this, BtnTag::SOUND);

	// StatusBar
	sBar = StatusBar::create(0, 0, dWidth, gSize * 4);
	sBar->pushBtnBase(btnQuit);
	sBar->pushBtnBase(btnSound);
	sBar->resetScore();// Reset score
	sBar->resetBonus();// Reset bonus

	// Dpad
	dPad = CtlDpad::createDpad(cX, cY);
	dPad->hide();// Hide
	dPad->addDpadListener(this);

	// Player
	player = SpriteKobo::createSprite("images/c_kobo.png", cX, cY);
	player->setPos(mManager->getRdmPos());

	// Osho
	osho = SpriteOsho::createSprite("images/c_osho.png", cX, cY);
	osho->setMazeManager(mManager);
	osho->setPos(mManager->getRdmPos());

	// Chicken
	chicken = SpriteChicken::createSprite("images/c_chicken_f.png", cX, gSize * 3);
	chicken->setPos(mManager->getRdmPos());

	// Next
	Vec2 &next = mManager->getRdmPos();
	chicken->setNext(next.x, next.y);
	chicken->setEggListener(this);

	// Tanu
	for (int i = 0; i < 3; i++) {
		SpriteTanu *tanu = SpriteTanu::createSprite("images/c_tanu.png", cX, cY);
		tanu->setMazeManager(mManager);
		tanu->setLeader(player);
		tanu->setPos(mManager->getRdmPos());
		tanus.push_back(tanu);
	}

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
	if (updateMode != START) return;// Important
	if (y < dHeight / 5) sBar->setOnTouchBegan(id, x, y);
	if (dHeight / 5 < y) dPad->setOnTouchBegan(id, x, y);
	for (auto btn : btns) btn->setOnTouchBegan(id, x, y);
}

void SceneGame::setOnTouchMoved(int id, int x, int y) {
	//LOGD("Main", "setOnTouchMoved()[%d]:%d, %d", id, x, y);
	if (updateMode != START) return;// Important
	if (sBar) sBar->setOnTouchMoved(id, x, y);
	if (dPad) dPad->setOnTouchMoved(id, x, y);
	for (auto btn : btns) btn->setOnTouchMoved(id, x, y);
}

void SceneGame::setOnTouchEnded(int id, int x, int y) {
	//LOGD("Main", "setOnTouchEnded()[%d]:%d, %d", id, x, y);
	if (updateMode != START) return;// Important
	if (sBar) sBar->setOnTouchEnded(id, x, y);
	if (dPad) dPad->setOnTouchEnded(id, x, y);
	for (auto btn : btns) btn->setOnTouchEnded(id, x, y);
}

void SceneGame::update(const float delay) {

	// Background, MazeManager
	//background->update(delay);
	mManager->update(delay);

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
}

void SceneGame::onDpadPressed(DpadTag &tag) {
	//LOGD("Dpad", "onDpadPressed():%d", tag);
	if (player->isDead()) return;
	int spd = UtilDebug::getInstance()->getGridSize() * 5;
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);
}

void SceneGame::onDpadCanceled(DpadTag &tag) {
	//LOGD("Dpad", "onDpadCanceled():%d", tag);
	if (player->isDead()) return;
	player->startStay();// Stay
}

void SceneGame::onDpadReleased(DpadTag &tag) {
	//LOGD("Dpad", "onDpadReleased():%d", tag);
	if (player->isDead()) return;
	player->startStay();// Stay
}

void SceneGame::onDpadChanged(DpadTag &tag) {
	//LOGD("Main", "onBtnReleased()");
	if (player->isDead()) return;
	player->startStay();
	const int spd = UtilDebug::getInstance()->getGridSize() * 20;
	if (tag == DpadTag::LEFT) player->startWalk(spd, 180, true);
	if (tag == DpadTag::RIGHT) player->startWalk(spd, 0, true);
	if (tag == DpadTag::UP) player->startWalk(spd, 270, true);
	if (tag == DpadTag::DOWN) player->startWalk(spd, 90, true);
}

void SceneGame::gameReady(const float delay) {

	const float cX = dWidth * 0.5f;
	const float cY = dHeight * 0.5f;

	// Player
	player->update(delay);

	// Wait
	waitCnt++;
	if (waitInterval < waitCnt) {
		waitCnt = 0;
		updateMode = START;// Next
		// Hopper
		MsgHopper *hopper = MsgHopper::createStr(cX, cY, 4, "START!");
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

	// Player x Osho
	if (player->containsPos(osho)) {
		updateMode = FINISH;// Next
		// Player, Dpad
		player->startDead();
		dPad->hide();
		// Hopper
		MsgHopper *hopper = MsgHopper::createStr(cX, cY, 4, "FINISH!");
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
		// x Tanu
		auto itT = tanus.end();
		while (itT-- != tanus.begin()) {
			auto tanu = static_cast<SpriteTanu *>(*itT);
			if (tanu->containsPos(egg)) {
				tanu->startCapture(true, false);
				eggs.erase(itE);
				DX_SAFE_DELETE(egg);
				UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
				break;
			}
		}
	}

	// Chicks x Tanu
	auto itH = chicks.end();
	while (itH-- != chicks.begin()) {
		auto chick = static_cast<SpriteChick *>(*itH);
		chick->update(delay);
		// Tanu
		auto itT = tanus.end();
		while (itT-- != tanus.begin()) {
			auto tanu = static_cast<SpriteTanu *>(*itT);
			if (tanu->containsPos(chick)) {
				if (tanu->getItemFlg()) continue;
				tanu->startCapture(false, true);
				this->purgeChick();// Purge
				UtilSound::getInstance()->playSE("sounds/se_grab_01.wav");
				goto OUTER_LOOP;
			}
		}
	}
	OUTER_LOOP:

	// Tanus
	for (auto tanu : tanus) tanu->update(delay);

	// Osho, Chicken
	osho->update(delay);
	chicken->update(delay);

	// Player
	player->update(delay);
	if (!player->getMoveFlg()) return;

	if (player->getMinX() < mManager->getMinX()) {
		player->setPosX(mManager->getMinX() + player->getWidth() / 2);
	}
	if (mManager->getMaxX() < player->getMaxX()) {
		player->setPosX(mManager->getMaxX() - player->getWidth() / 2);
	}
	if (player->getMinY() < mManager->getMinY()) {
		player->setPosY(mManager->getMinY() + player->getHeight() / 2);
	}
	if (mManager->getMaxY() < player->getMaxY()) {
		player->setPosY(mManager->getMaxY() - player->getHeight() / 2);
	}

	const MazeGrid &grid = mManager->getGridByPos(player->getPosX(), player->getPosY());
	if (player->getVX() < 0) {
		const MazeGrid &gridT = mManager->getGridByRC(grid.r, grid.c - 1);
		if (gridT.type != MazeType::FLOOR) {
			if (player->getPosX() < grid.pos.x) player->setPosX(grid.pos.x);
		} else {
			player->setPosY(grid.pos.y);
		}
		return;
	}
	if (0 < player->getVX()) {
		const MazeGrid &gridT = mManager->getGridByRC(grid.r, grid.c + 1);
		if (gridT.type != MazeType::FLOOR) {
			if (grid.pos.x < player->getPosX()) player->setPosX(grid.pos.x);
		} else {
			player->setPosY(grid.pos.y);
		}
		return;
	}
	if (player->getVY() < 0) {
		const MazeGrid &gridT = mManager->getGridByRC(grid.r - 1, grid.c);
		if (gridT.type != MazeType::FLOOR) {
			if (player->getPosY() < grid.pos.y) player->setPosY(grid.pos.y);
		} else {
			player->setPosX(grid.pos.x);
		}
		return;
	}
	if (0 < player->getVY()) {
		const MazeGrid &gridT = mManager->getGridByRC(grid.r + 1, grid.c);
		if (gridT.type != MazeType::FLOOR) {
			if (grid.pos.y < player->getPosY()) player->setPosY(grid.pos.y);
		} else {
			player->setPosX(grid.pos.x);
		}
		return;
	}
}

void SceneGame::gameFinish(const float delay) {

	// Tanus, Eggs, Chicks
	for (auto tanu : tanus) tanu->update(delay);
	for (auto egg : eggs) egg->update(delay);
	for (auto chick : chicks) chick->update(delay);

	// Osho, Chicken, Player
	osho->update(delay);
	chicken->update(delay);
	player->update(delay);

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
	Vec2 &next = mManager->getRdmPos();
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