#include "BtnBase.h"

BtnBase *BtnBase::createSprite(const string &fileName, float x, float y,
                               int xNum, int yNum) {
	// New
	BtnBase *sprite = new BtnBase(x, y);
	if (sprite && sprite->init(fileName.c_str(), xNum, yNum)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

BtnBase::BtnBase(float x, float y) :
		pos(Vec2(x, y)),
		width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0),
		touchID(-1) {
	LOGD("Main", "BtnBase()\n");
}

BtnBase::~BtnBase() {
	LOGD("Main", "~BtnBase()\n");
}

bool BtnBase::init(const char *fileName, int xNum, int yNum) {
	// Load graph
	int graph = LoadGraph(fileName);
	if (graph == -1) return false;
	int sWidth, sHeight;
	GetGraphSize(graph, &sWidth, &sHeight);
	// Width, Height
	width = sWidth / xNum;
	height = sHeight / yNum;
	int result = LoadDivGraph(fileName, xNum * yNum,
	                          xNum, yNum, width, height, graphs);
	if (result == 0) {
		DeleteGraph(graph);// Delete
		return true;
	}
	return false;
}

void BtnBase::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void BtnBase::setScale(int scale) {
	this->scale = scale;
	this->width *= scale;
	this->height *= scale;
}

bool BtnBase::containsPoint(int x, int y) {
	if (x < minX) return false;
	if (maxX < x) return false;
	if (y < minY) return false;
	if (maxY < y) return false;
	return true;
}

void BtnBase::setOnTouchBegan(int id, int x, int y) {
	if (touchID != -1) return;
	if (!this->containsPoint(x, y)) return;
	LOGD("Main", "Capture[%d]:%d, %d", id, x, y);
	touchID = id;
}

void BtnBase::setOnTouchMoved(int id, int x, int y) {
	if (touchID != id) return;
	if (this->containsPoint(x, y)) return;
	LOGD("Main", "Cancel[%d]:%d, %d", id, x, y);
	touchID = -1;
}

void BtnBase::setOnTouchEnded(int id, int x, int y) {
	if (touchID != id) return;
	if (!this->containsPoint(x, y)) return;
	LOGD("Main", "Confirm[%d]:%d, %d", id, x, y);
	touchID = -1;
}

void BtnBase::update(const float delay) {
	// Rect
	minX = pos.x - width * 0.5f;
	maxX = pos.x + width * 0.5f;
	minY = pos.y - height * 0.5f;
	maxY = pos.y + height * 0.5f;
	// Draw
	int color = GetColor(255, 255, 255);
	DrawBox(minX, minY, maxX, maxY, color, false);
	if (touchID != -1) {
		DrawExtendGraph(minX, minY, maxX, maxY, graphs[1], true);
	} else {
		DrawExtendGraph(minX, minY, maxX, maxY, graphs[0], true);
	}
}