#include "BtnBase.h"

#include <utility>

BtnBase *BtnBase::createBtn(const string &fileName,
							float x, float y) {
	// New
	BtnBase *sprite = new BtnBase(x, y);
	if (sprite && sprite->init(fileName.c_str())) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

BtnBase::BtnBase(float x, float y) :
		pos(Vec2(x, y)),
		graph(0), width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0),
		touchFlg(false), touchID(-1), title(""),
		btnListener(nullptr), btnTag(BtnTag::DEFAULT) {
	LOGD("Main", "BtnBase()\n");
}

BtnBase::~BtnBase() {
	LOGD("Main", "~BtnBase()\n");
}

bool BtnBase::init(const char *fileName) {
	// Load graph
	graph = UtilGraph::getInstance()->getGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	return true;
}

void BtnBase::offsetPos(int x, int y) {
	pos.x += x;
	pos.y += y;
}

void BtnBase::setScale(int scale) {
	this->scale = scale;
	this->width *= scale;
	this->height *= scale;
}

void BtnBase::setTitle(string str) {
	title = str;
}

bool BtnBase::containsPoint(int x, int y) {
	if (x < minX) return false;
	if (maxX < x) return false;
	if (y < minY) return false;
	if (maxY < y) return false;
	return true;
}

bool BtnBase::setOnTouchBegan(int id, int x, int y) {
	if (touchFlg) return false;
	if (touchID != -1) return false;
	if (!this->containsPoint(x, y)) return false;
	if (btnListener) btnListener->onBtnPressed(btnTag);
	touchFlg = true;
	touchID = id;
	return true;
}

bool BtnBase::setOnTouchMoved(int id, int x, int y) {
	if (!touchFlg) return false;
	if (touchID != id) return false;
	if (this->containsPoint(x, y)) return false;
	if (btnListener) btnListener->onBtnCanceled(btnTag);
	touchFlg = false;
	touchID = -1;
	return true;
}

bool BtnBase::setOnTouchEnded(int id, int x, int y) {
	if (!touchFlg) return false;
	if (touchID != id) return false;
	if (!this->containsPoint(x, y)) return false;
	if (btnListener) btnListener->onBtnReleased(btnTag);
	touchFlg = false;
	touchID = -1;
	return true;
}

void BtnBase::update(const float delay) {
	// Rect
	minX = pos.x - width * 0.5f;
	maxX = pos.x + width * 0.5f;
	minY = pos.y - height * 0.5f;
	maxY = pos.y + height * 0.5f;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
	// Title
	if (title.empty()) return;
	UtilLabel::getInstance()->drawStr(title, pos.x, pos.y, 2,
									  UtilAlign::CENTER);
}

void BtnBase::addBtnListener(BtnListener *listener, BtnTag tag) {
	btnListener = listener;
	btnTag = tag;
}