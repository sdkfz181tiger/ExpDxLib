#include "SceneBase.h"

SceneBase::SceneBase(int dWidth, int dHeight) :
		dWidth(dWidth), dHeight(dHeight),
		sceneListener(nullptr),
		sceneWaitFlg(true), sceneWaitTime(0.0f),
		sceneNextTag(SceneTag::DEFAULT) {
	LOGD("Main", "SceneBase()\n");
}

SceneBase::~SceneBase() {
	LOGD("Main", "~SceneBase()\n");
}

void SceneBase::addSceneListener(SceneListener *listener) {
	sceneListener = listener;
}

void SceneBase::replaceSceneWait(float wait, SceneTag tag) {
	sceneWaitFlg = false;
	sceneWaitTime = wait;
	sceneNextTag = tag;
}

void SceneBase::replaceSceneTick(float delay) {
	if (sceneWaitFlg) return;
	sceneWaitTime -= delay;
	if (0.0f < sceneWaitTime) return;
	sceneWaitFlg = true;
	if (!sceneListener) return;
	sceneListener->onSceneChange(sceneNextTag);
}