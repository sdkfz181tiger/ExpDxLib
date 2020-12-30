#include "UtilDx.h"

// Singleton Object
static UtilDx *selfUtilDx = nullptr;

UtilDx::UtilDx() : quitFlg(false), defScale(2) {
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

bool UtilDx::getQuitFlg() {
	return quitFlg;
}

int UtilDx::getDefScale() {
	return defScale;
}