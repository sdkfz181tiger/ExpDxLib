#include "UtilDebug.h"

// Singleton Object
static UtilDebug *selfUtilDebug = nullptr;

UtilDebug::UtilDebug() : dispWidth(0), dispHeight(0), dispColor(0),
                         gridSize(64), gridRows(0), gridCols(0), gridColor(0) {
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
	GetScreenState(&dispWidth, &dispHeight, &dispColor);
	gridRows = dispHeight / gridSize;
	gridCols = dispWidth / gridSize;
	gridColor = GetColor(0, 99, 0);
	return true;
}

void UtilDebug::drawGrid() {
	// Center
	const int cX = dispWidth / 2;
	const int cY = dispHeight / 2;
	// Draw center
	DrawLine(0, cY, dispWidth, cY, gridColor);
	DrawLine(cX, 0, cX, dispHeight, gridColor);
	// Grid
	for (int r = 1; r <= gridRows / 2; r++) {
		DrawLine(0, cY + gridSize * r, dispWidth, cY + gridSize * r, gridColor);
		DrawLine(0, cY - gridSize * r, dispWidth, cY - gridSize * r, gridColor);
	}
	for (int c = 1; c <= gridCols; c++) {
		DrawLine(cX + gridSize * c, 0, cX + gridSize * c, dispHeight, gridColor);
		DrawLine(cX - gridSize * c, 0, cX - gridSize * c, dispHeight, gridColor);
	}
}

void UtilDebug::drawFPS(float delay) {

	char fpsStr[20];
	sprintf(fpsStr, "FPS:%.2f", delay);
	UtilLabel::getInstance()->drawStr(fpsStr, dispWidth, dispHeight - gridSize,
	                                  3, UtilAlign::RIGHT);
}