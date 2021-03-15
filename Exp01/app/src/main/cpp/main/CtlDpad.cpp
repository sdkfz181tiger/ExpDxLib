#include "CtlDpad.h"

CtlDpad *CtlDpad::createDpad(float x, float y) {
	// New
	CtlDpad *sprite = new CtlDpad(x, y);
	if (sprite && sprite->init()) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

CtlDpad::CtlDpad(float x, float y) :
		pos(Vec2(x, y)), dpad(Vec2(x, y)),
		graph(0), width(0), height(0), scale(1),
		minX(0), maxX(0), minY(0), maxY(0),
		gRight(0), gLeft(0), gDown(0), gUp(0),
		dpadFlg(false), dpadID(-1), dpadDir(0),
		dpadListener(nullptr), dpadTag(DpadTag::DEFAULT) {
	LOGD("Main", "CtlDpad()\n");
}

CtlDpad::~CtlDpad() {
	LOGD("Main", "~CtlDpad()\n");
}

bool CtlDpad::init() {
	// Load graph
	graph = UtilGraph::getInstance()->getGraph("images/ctl_60x60_default.png");
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	// Load other graphs
	gRight = UtilGraph::getInstance()->getGraph("images/ctl_60x60_right.png");
	gDown = UtilGraph::getInstance()->getGraph("images/ctl_60x60_down.png");
	gLeft = UtilGraph::getInstance()->getGraph("images/ctl_60x60_left.png");
	gUp = UtilGraph::getInstance()->getGraph("images/ctl_60x60_up.png");
	if (gRight == -1 || gDown == -1 || gLeft == -1 || gUp == -1) return false;
	return true;
}

void CtlDpad::setPosition(int x, int y) {
	pos.x = x;
	pos.y = y;
}

void CtlDpad::setScale(int scl) {
	width *= scl;
	height *= scl;
	scale = scl;
}

void CtlDpad::hide() {
	pos.x = -width;
	pos.y = -height;
}

bool CtlDpad::containsPoint(int x, int y) {
	const int scale = 4;
	if (x < pos.x - width * scale) return false;
	if (pos.x + width * scale < x) return false;
	if (y < pos.y - height * scale) return false;
	if (pos.y + height * scale < y) return false;
	return true;
}

void CtlDpad::setOnTouchBegan(int id, int x, int y) {
	if (dpadFlg) return;
	if (dpadID != -1) return;
	this->setPosition(x, y);
	if (dpadListener) dpadListener->onDpadPressed(dpadTag);
	dpadFlg = true;
	dpadID = id;
}

void CtlDpad::setOnTouchMoved(int id, int x, int y) {
	if (!dpadFlg) return;
	if (dpadID != id) return;
	if (this->containsPoint(x, y)) {
		this->calcDirection(x, y);// Calc
		return;
	}
	this->hide();// Hide
	if (dpadListener) dpadListener->onDpadCanceled(dpadTag);
	dpadFlg = false;
	dpadID = -1;
	//dpadTag = DpadTag::DEFAULT;
}

void CtlDpad::setOnTouchEnded(int id, int x, int y) {
	if (!dpadFlg) return;
	if (dpadID != id) return;
	if (!this->containsPoint(x, y)) return;
	this->hide();// Hide
	if (dpadListener) dpadListener->onDpadReleased(dpadTag);
	dpadFlg = false;
	dpadID = -1;
	//dpadTag = DpadTag::DEFAULT;
}

void CtlDpad::calcDirection(int x, int y) {
	dpad.x = x;
	dpad.y = y;
	// Distance
	if (UtilMath::getInstance()->calcDistance2D(pos, dpad) < width / 20) return;
	// Direction
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
	if (dpadTag == DpadTag::RIGHT) {
		DrawExtendGraph(minX, minY, maxX, maxY, gRight, true);
	} else if (dpadTag == DpadTag::DOWN) {
		DrawExtendGraph(minX, minY, maxX, maxY, gDown, true);
	} else if (dpadTag == DpadTag::LEFT) {
		DrawExtendGraph(minX, minY, maxX, maxY, gLeft, true);
	} else if (dpadTag == DpadTag::UP) {
		DrawExtendGraph(minX, minY, maxX, maxY, gUp, true);
	} else {
		DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
	}
}

void CtlDpad::addDpadListener(DpadListener *listener) {
	dpadListener = listener;
}
