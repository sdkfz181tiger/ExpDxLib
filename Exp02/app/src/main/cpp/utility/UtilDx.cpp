#include "UtilDx.h"

// Singleton Object
static UtilDx *selfUtilDx = nullptr;

UtilDx::UtilDx() : quitFlg(false), defScale(4) {
	LOGD("Util", "UtilDx()\n");
}

UtilDx::~UtilDx() {
	LOGD("Util", "~UtilDx()\n");
}

UtilDx *UtilDx::getInstance() {

	if (!selfUtilDx) {
		selfUtilDx = new UtilDx();
		if (selfUtilDx && selfUtilDx->init()) {
			return selfUtilDx;
		} else {
			delete (selfUtilDx);
			selfUtilDx = nullptr;
		}
	}
	return selfUtilDx;
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