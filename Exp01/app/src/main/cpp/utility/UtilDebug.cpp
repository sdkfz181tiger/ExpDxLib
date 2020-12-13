#include "UtilDebug.h"

// Singleton Object
static UtilDebug *selfUtilDebug = nullptr;

UtilDebug::UtilDebug() : dWidth(0), dHeight(0), dColor(0),
                         gSize(64), gRows(0), gCols(0), gColor(0),
                         fWidth(0), fHeight(0), fColor(0),
                         sSize(0), sColor(0), pCnt(0) {
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
	GetScreenState(&dWidth, &dHeight, &dColor);
	LOGD("Display:%d x %d", dWidth, dHeight);
	gRows = dHeight / gSize;
	gCols = dWidth / gSize;
	gColor = GetColor(0, 99, 0);
	fWidth = gSize * 3;
	fHeight = gSize * 2;
	fColor = GetColor(33, 33, 99);
	sSize = gSize * 0.5f;
	sColor = GetColor(255, 255, 255);
	pCnt = GetNowCount();
	return true;
}

void UtilDebug::drawGrid() {
	// Center
	const int cX = dWidth * 0.5f;
	const int cY = dHeight * 0.5f;
	// Draw center
	DrawLine(0, cY, dWidth, cY, gColor);
	DrawLine(cX, 0, cX, dHeight, gColor);
	// Grid
	for (int r = 1; r <= gRows * 0.5f; ++r) {
		DrawLine(0, cY + gSize * r, dWidth, cY + gSize * r, gColor);
		DrawLine(0, cY - gSize * r, dWidth, cY - gSize * r, gColor);
	}
	for (int c = 1; c <= gCols; ++c) {
		DrawLine(cX + gSize * c, 0, cX + gSize * c, dHeight, gColor);
		DrawLine(cX - gSize * c, 0, cX - gSize * c, dHeight, gColor);
	}
}

void UtilDebug::drawFPS() {

	const int sX = dWidth - fWidth;
	const int sY = dHeight - fHeight;
	const float delay = 1000.0f / float(GetNowCount() - pCnt);
	DrawBox(sX, sY, dWidth, dHeight, fColor, true);
	SetFontSize(sSize);
	DrawFormatString(sX, sY, sColor, "FPS:%.2f", delay);
	DrawFormatString(sX, sY+gSize*0.5f, sColor, "W:%d", dWidth);
	DrawFormatString(sX, sY+gSize*1.0f, sColor, "Y:%d", dHeight);
	pCnt = GetNowCount();// Update
}