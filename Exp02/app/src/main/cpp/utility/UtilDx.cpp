#include "UtilDx.h"

// Singleton Object
static UtilDx *selfUtilDx = nullptr;

UtilDx::UtilDx() : quitFlg(false), dWidth(540), dHeight(960),
				   dDepth(16), defScale(4), fps(32) {
	LOGD("Util", "UtilDx()\n");
}

UtilDx::~UtilDx() {
	LOGD("Util", "~UtilDx()\n");
}

UtilDx *UtilDx::getInstance() {
	if (selfUtilDx) return selfUtilDx;
	selfUtilDx = new UtilDx();
	if (selfUtilDx && selfUtilDx->init()) return selfUtilDx;
	DX_SAFE_DELETE(selfUtilDx);
	return nullptr;
}

void UtilDx::destroyInstance() {
	if (!selfUtilDx) return;

	delete (selfUtilDx);
	selfUtilDx = nullptr;
}

bool UtilDx::init() {
	LOGD("Util", "UtilDx::init()\n");
	return true;
}

void UtilDx::setQuitFlg() {
	this->quitFlg = true;
}