#include "CtlDpad.h"

CtlDpad *CtlDpad::createDpad(const string &fileName, float x, float y) {
	// New
	CtlDpad *sprite = new CtlDpad(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

CtlDpad::CtlDpad(float x, float y) :
		pos(Vec2(x, y)), dpad(Vec2(x, y)),
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
	this->calcDirection(x, y);// Calc
}

void CtlDpad::setOnTouchMoved(int id, int x, int y) {
	if (!dpadFlg) return;
	if (dpadID != id) return;
	if (this->containsPoint(x, y)) {
		this->calcDirection(x, y);// Calc
		return;
	}
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

void CtlDpad::calcDirection(int x, int y) {
	dpad.x = x;
	dpad.y = y;
	dpadDir = UtilMath::getInstance()->calcDeg2D(pos, dpad);
	if (dpadDir < 45) {
		if (dpadTag == DpadTag::RIGHT) return;
		dpadTag = DpadTag::RIGHT;
		if (dpadListener) dpadListener->onDpadChanged(dpadTag);
	} else if (dpadDir < 135) {
		if (dpadTag == DpadTag::DOWN) return;
		dpadTag = DpadTag::DOWN;
		if (dpadListener) dpadListener->onDpadChanged(dpadTag);
	} else if (dpadDir < 225) {
		if (dpadTag == DpadTag::LEFT) return;
		dpadTag = DpadTag::LEFT;
		if (dpadListener) dpadListener->onDpadChanged(dpadTag);
	} else if (dpadDir < 315) {
		if (dpadTag == DpadTag::UP) return;
		dpadTag = DpadTag::UP;
		if (dpadListener) dpadListener->onDpadChanged(dpadTag);
	} else {
		if (dpadTag == DpadTag::RIGHT) return;
		dpadTag = DpadTag::RIGHT;
		if (dpadListener) dpadListener->onDpadChanged(dpadTag);
	}
}

void CtlDpad::update(const float delay) {
	// Rect
	minX = pos.x - width / 2;
	maxX = pos.x + width / 2;
	minY = pos.y - height / 2;
	maxY = pos.y + height / 2;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
	// Marker
	if (!dpadFlg) return;
	int white = GetColor(255, 255, 255);
	DrawBox(dpad.x - 5, dpad.y - 5, dpad.x + 5, dpad.y + 5, white, true);
}

void CtlDpad::addDpadListener(DpadListener *listener) {
	dpadListener = listener;
}
