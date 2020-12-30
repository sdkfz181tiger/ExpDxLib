#include "UtilDebug.h"

// Singleton Object
static UtilDebug *selfUtilDebug = nullptr;

UtilDebug::UtilDebug() : dispWidth(0), dispHeight(0), dispColor(0),
						 gridSize(0), gridRows(0), gridCols(10),
						 gridColor(GetColor(0, 99, 0)) {
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
	gridSize = dispWidth / gridCols;
	gridRows = dispHeight / gridSize;
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
	// FPS
	sprintf(fpsStr, "FPS:%.1f", 1.0f / delay);
	UtilLabel::getInstance()->drawStr(fpsStr, gridSize / 4, gridSize / 4,
									  2, UtilAlign::LEFT);
}