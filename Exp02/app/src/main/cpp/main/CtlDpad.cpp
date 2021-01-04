#include "CtlDpad.h"

CtlDpad *CtlDpad::createDpad(const string &fileName, float x, float y) {
	// New
	CtlDpad *sprite = new CtlDpad(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

CtlDpad::CtlDpad(float x, float y) :
		pos(Vec2(x, y)),
		graph(0), width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0),
		dpadFlg(false), dpadID(-1), dpadDir(0),
		dpadListener(nullptr), dpadTag(DpadTag::DEFAULT) {
	LOGD("Main", "CtlDpad()\n");
}

CtlDpad::~CtlDpad() {
	LOGD("Main", "~CtlDpad()\n");
}

bool CtlDpad::init(const string &fileName) {
	// Load graph
	graph = UtilGraph::getInstance()->getGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	return true;
}

void CtlDpad::setScale(int scl) {
	width *= scl;
	height *= scl;
	scale = scl;
}

bool CtlDpad::containsPoint(int x, int y) {
	if (x < minX) return false;
	if (maxX < x) return false;
	if (y < minY) return false;
	if (maxY < y) return false;
	return true;
}

void CtlDpad::setOnTouchBegan(int id, int x, int y) {
	if (dpadFlg) return;
	if (dpadID != -1) return;
	if (!this->containsPoint(x, y)) return;
	if (dpadListener) dpadListener->onDpadPressed(dpadTag);
	dpadFlg = true;
	dpadID = id;
}

void CtlDpad::setOnTouchMoved(int id, int x, int y) {
	if (!dpadFlg) return;
	if (dpadID != id) return;
	if (this->containsPoint(x, y)) return;
	if (dpadListener) dpadListener->onDpadCanceled(dpadTag);
	dpadFlg = false;
	dpadID = -1;
}

void CtlDpad::setOnTouchEnded(int id, int x, int y) {
	if (!dpadFlg) return;
	if (dpadID != id) return;
	if (!this->containsPoint(x, y)) return;
	if (dpadListener) dpadListener->onDpadReleased(dpadTag);
	dpadFlg = false;
	dpadID = -1;
}

void CtlDpad::update(const float delay) {
	// Rect
	minX = pos.x - width / 2;
	maxX = pos.x + width / 2;
	minY = pos.y - height / 2;
	maxY = pos.y + height / 2;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
}

void CtlDpad::addDpadListener(DpadListener *listener) {
	dpadListener = listener;
}
