#include "SceneBase.h"

SceneBase::SceneBase(int dWidth, int dHeight) :
		dWidth(dWidth), dHeight(dHeight) {
	LOGD("Main", "SceneBase()\n");
}

SceneBase::~SceneBase() {
	LOGD("Main", "~SceneBase()\n");
}