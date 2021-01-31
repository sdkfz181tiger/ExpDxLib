#include "BtnToggle.h"

BtnToggle *BtnToggle::createToggle(const string &fileNameOn,
								   const string &fileNameOff,
								   float x, float y) {
	// New
	BtnToggle *sprite = new BtnToggle(x, y);
	if (sprite && sprite->init(fileNameOn.c_str(), fileNameOff.c_str())) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

BtnToggle::BtnToggle(float x, float y) : BtnBase(x, y),
										 graphOn(-1), graphOff(-1) {
	LOGD("Main", "BtnToggle()\n");
}

BtnToggle::~BtnToggle() {
	LOGD("Main", "~BtnToggle()\n");
}

bool BtnToggle::init(const char *fileNameOn, const char *fileNameOff) {
	// Load graph
	graphOn = UtilGraph::getInstance()->getGraph(fileNameOn);// On
	graphOff = UtilGraph::getInstance()->getGraph(fileNameOff);// Off
	graph = (UtilSound::getInstance()->isMute()) ? graphOff : graphOn;// Graph
	if (graphOn == -1 || graphOff == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	return true;
}

bool BtnToggle::setOnTouchBegan(int id, int x, int y) {
	return BtnBase::setOnTouchBegan(id, x, y);
}

bool BtnToggle::setOnTouchMoved(int id, int x, int y) {
	return BtnBase::setOnTouchMoved(id, x, y);
}

bool BtnToggle::setOnTouchEnded(int id, int x, int y) {
	if (!BtnBase::setOnTouchEnded(id, x, y)) return false;
	UtilSound::getInstance()->toggleMute();// Sound
	graph = (UtilSound::getInstance()->isMute()) ? graphOff : graphOn;// Graph
	return true;
}

void BtnToggle::update(const float delay) {
	// Rect
	minX = pos.x - width * 0.5f;
	maxX = pos.x + width * 0.5f;
	minY = pos.y - height * 0.5f;
	maxY = pos.y + height * 0.5f;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
}