#include "UtilDebug.h"

// Singleton Object
static UtilDebug *selfUtilDebug = nullptr;

UtilDebug::UtilDebug() : dWidth(0), dHeight(0), dColor(0),
						 gSize(0), gRows(0), gCols(40),
						 gColor(GetColor(0, 99, 0)) {
	LOGD("Util", "UtilDebug()\n");
}

UtilDebug::~UtilDebug() {
	LOGD("Util", "~UtilDebug()\n");
}

UtilDebug *UtilDebug::getInstance() {
	if (selfUtilDebug) return selfUtilDebug;
	selfUtilDebug = new UtilDebug();
	if (selfUtilDebug && selfUtilDebug->init()) return selfUtilDebug;
	DX_SAFE_DELETE(selfUtilDebug);
	return nullptr;
}

void UtilDebug::destroyInstance() {
	if (!selfUtilDebug) return;

	delete (selfUtilDebug);
	selfUtilDebug = nullptr;
}

bool UtilDebug::init() {
	LOGD("Util", "UtilDebug::init()\n");
	GetScreenState(&dWidth, &dHeight, &dColor);
	gSize = dWidth / gCols;
	gRows = dHeight / gSize;
	return true;
}

void UtilDebug::drawDebug(float delay) {
	//this->drawGrid();
	this->drawFPS(delay);
}

void UtilDebug::drawGrid() {
	// Center
	const int cX = dWidth / 2;
	const int cY = dHeight / 2;
	// Draw center
	DrawLine(0, cY, dWidth, cY, gColor);
	DrawLine(cX, 0, cX, dHeight, gColor);
	// Grid
	for (int r = 1; r <= gRows / 2; r++) {
		DrawLine(0, cY + gSize * r, dWidth, cY + gSize * r, gColor);
		DrawLine(0, cY - gSize * r, dWidth, cY - gSize * r, gColor);
	}
	for (int c = 1; c <= gCols; c++) {
		DrawLine(cX + gSize * c, 0, cX + gSize * c, dHeight, gColor);
		DrawLine(cX - gSize * c, 0, cX - gSize * c, dHeight, gColor);
	}
}

void UtilDebug::drawFPS(float delay) {
	// FPS
	sprintf(fpsStr, "FPS:%.2f", 1.0f / delay);
	UtilLabel::getInstance()->drawStr(fpsStr, dWidth / 2, dHeight - gSize * 7,
									  1, UtilAlign::CENTER);
}