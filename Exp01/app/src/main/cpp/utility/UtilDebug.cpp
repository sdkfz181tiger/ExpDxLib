#include "UtilDebug.h"

// Singleton Object
static UtilDebug *selfUtilDebug = nullptr;

UtilDebug::UtilDebug() : dispWidth(0), dispHeight(0), dispColor(0),
                         gridSize(64), gridRows(0), gridCols(0), gridColor(0),
                         fpsWidth(0), fpsHeight(0), fpsColor(0), delayCnt(0) {
	LOGD("UtilDebug()\n");
}

UtilDebug::~UtilDebug() {
	LOGD("~UtilDebug()\n");
}

UtilDebug *UtilDebug::getInstance() {

	if (!selfUtilDebug) {
		selfUtilDebug = new UtilDebug();
		if (selfUtilDebug && selfUtilDebug->init()) {
			return selfUtilDebug;
		} else {
			delete (selfUtilDebug);
			selfUtilDebug = nullptr;
		}
	}
	return selfUtilDebug;
}

void UtilDebug::destroyInstance() {
	if (!selfUtilDebug) return;

	delete (selfUtilDebug);
	selfUtilDebug = nullptr;
}

bool UtilDebug::init() {
	LOGD("UtilDebug::init()\n");
	GetScreenState(&dispWidth, &dispHeight, &dispColor);
	gridRows = dispHeight / gridSize;
	gridCols = dispWidth / gridSize;
	gridColor = GetColor(0, 99, 0);
	fpsWidth = gridSize * 4;
	fpsHeight = gridSize * 1;
	fpsColor = GetColor(33, 33, 99);
	delayCnt = GetNowCount();
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
	for (int r = 1; r <= gridRows / 2; ++r) {
		DrawLine(0, cY + gridSize * r, dispWidth, cY + gridSize * r, gridColor);
		DrawLine(0, cY - gridSize * r, dispWidth, cY - gridSize * r, gridColor);
	}
	for (int c = 1; c <= gridCols; ++c) {
		DrawLine(cX + gridSize * c, 0, cX + gridSize * c, dispHeight, gridColor);
		DrawLine(cX - gridSize * c, 0, cX - gridSize * c, dispHeight, gridColor);
	}
}

void UtilDebug::drawFPS() {

	const int sX = dispWidth - fpsWidth;
	const int sY = dispHeight - fpsHeight;
	const float delay = 1000.0f / float(GetNowCount() - delayCnt);
	char fpsStr[20];
	sprintf(fpsStr, "FPS:%.2f", delay);
	UtilLabel::getInstance()->drawStr(fpsStr, sX + fpsWidth / 2, sY,
	                                  3, UtilLabelAlign::CENTER);
	delayCnt = GetNowCount();// Update
}