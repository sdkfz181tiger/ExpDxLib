#include "BtnBase.h"

#include <utility>

BtnBase *BtnBase::createBtn(const string &fileName,
                            const string &title,
                            float x, float y) {
	// New
	BtnBase *sprite = new BtnBase(title, x, y);
	if (sprite && sprite->init(fileName.c_str())) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

BtnBase::BtnBase(string title, float x, float y) :
		title(title), pos(Vec2(x, y)),
		graph(0), width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0),
		touchFlg(false), touchID(-1), touchColor(0) {
	LOGD("Main", "BtnBase()\n");
}

BtnBase::~BtnBase() {
	LOGD("Main", "~BtnBase()\n");
}

bool BtnBase::init(const char *fileName) {
	// Load graph
	graph = LoadGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	return true;
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
	if (touchFlg) return;
	if (touchID != -1) return;
	if (!this->containsPoint(x, y)) return;
	LOGD("Main", "Captured[%d]:%d, %d", id, x, y);
	touchFlg = true;
	touchID = id;
	touchColor = GetColor(33, 33, 255);
}

void BtnBase::setOnTouchMoved(int id, int x, int y) {
	if (!touchFlg) return;
	if (touchID != id) return;
	if (this->containsPoint(x, y)) return;
	LOGD("Main", "Canceled[%d]:%d, %d", id, x, y);
	touchFlg = false;
	touchID = -1;
	touchColor = GetColor(33, 33, 255);
}

void BtnBase::setOnTouchEnded(int id, int x, int y) {
	if (!touchFlg) return;
	if (touchID != id) return;
	if (!this->containsPoint(x, y)) return;
	LOGD("Main", "Confirmed[%d]:%d, %d", id, x, y);
	touchFlg = false;
	touchID = -1;
	touchColor = GetColor(33, 255, 33);
}

void BtnBase::update(const float delay) {
	// Rect
	minX = pos.x - width * 0.5f;
	maxX = pos.x + width * 0.5f;
	minY = pos.y - height * 0.5f;
	maxY = pos.y + height * 0.5f;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
	DrawBox(minX, minY, maxX, maxY, touchColor, false);
	// Text
	UtilLabel::getInstance()->drawStr(title, pos.x, pos.y,
	                                  scale, UtilAlign::CENTER);
}