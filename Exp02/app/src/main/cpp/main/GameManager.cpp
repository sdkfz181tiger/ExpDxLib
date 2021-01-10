#include "GameManager.h"

GameManager::GameManager(int dWidth, int dHeight, int cDepth) :
		dWidth(dWidth), dHeight(dHeight), cDepth(cDepth),
		touchFlgs(5, false), touchPositions(5, Vec2()) {
	LOGD("Main", "GameManager()\n");
	this->init();// Initialize
}

GameManager::~GameManager() {
	LOGD("Main", "~GameManager()\n");
	// Delete all scenes
	DX_SAFE_DELETE_VECTOR(scenes);
	// Destroy all utilities
	UtilDebug::getInstance()->destroyInstance();
	UtilDx::getInstance()->destroyInstance();
	UtilGraph::getInstance()->destroyInstance();
	UtilJNI::getInstance()->destroyInstance();
	UtilJson::getInstance()->destroyInstance();
	UtilLabel::getInstance()->destroyInstance();
	UtilMath::getInstance()->destroyInstance();
	UtilSound::getInstance()->destroyInstance();
}

void GameManager::init() {
	LOGD("Main", "GameManager::init()\n");
	// GraphMode
	SetGraphMode(dWidth, dHeight, cDepth);
	SetOutApplicationLogValidFlag(true);
	// Scenes
	SceneBase *scene = SceneGame::createScene(dWidth, dHeight);
	scene->addSceneListener(this);
	scenes.push_back(scene);
}

void GameManager::touchInput() {

	// Scene
	SceneBase *scene = scenes.back();

	// Touches(Began, Moved)
	vector<bool> touches(5, false);
	for (int i = 0; i < GetTouchInputNum(); i++) {
		int x, y, id;
		GetTouchInput(i, &x, &y, &id, nullptr);
		if (touchFlgs.size() <= id) continue;
		if (touchPositions.size() <= id) continue;
		if (!touchFlgs.at(id)) {
			//LOGD("Main", "Began[%d]:%d, %d", i, x, y);
			scene->setOnTouchBegan(id, x, y);// Began
		} else {
			if (touchPositions.at(id).x != x || touchPositions.at(id).y != y) {
				//LOGD("Main", "Moved[%d]:%d, %d", i, x, y);
				scene->setOnTouchMoved(id, x, y);// Moved
			}
		}
		touches.at(id) = true;
		touchFlgs.at(id) = true;
		touchPositions.at(id).x = x;
		touchPositions.at(id).y = y;
	}

	// Touches(Ended)
	for (int i = 0; i < touches.size(); i++) {
		if (touches.at(i)) continue;
		if (!touchFlgs.at(i)) continue;
		touchFlgs.at(i) = false;
		const int x = int(touchPositions.at(i).x);
		const int y = int(touchPositions.at(i).y);
		//LOGD("Main", "Ended[%d]:%d, %d", i, x, y);
		scene->setOnTouchEnded(i, x, y);// Ended
	}
}

void GameManager::update(const float delay) {

	scenes.back()->update(delay);// DrawScene
	//UtilDebug::getInstance()->drawGrid();// DrawGrid
	UtilDebug::getInstance()->drawFPS(delay);// DrawFPS
}

void GameManager::onSceneChange(SceneTag tag) {
	LOGD("Main", "GameManager::onSceneChange() %d\n", tag);

	if (SceneTag::TITLE == tag) {
		SceneTitle *scene = SceneTitle::createScene(dWidth, dHeight);
		scene->addSceneListener(this);
		scenes.push_back(scene);
	}

	if (SceneTag::GAME == tag) {
		SceneGame *scene = SceneGame::createScene(dWidth, dHeight);
		scene->addSceneListener(this);
		scenes.push_back(scene);
	}

	if (SceneTag::RESULT == tag) {
		SceneResult *scene = SceneResult::createScene(dWidth, dHeight);
		scene->addSceneListener(this);
		scenes.push_back(scene);
	}

	// Delete previous scene
	if (1 < scenes.size()) {
		auto it = scenes.begin();
		delete (*it);
		scenes.erase(it);
	}
}