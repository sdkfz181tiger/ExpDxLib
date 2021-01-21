#include "BtnToggle.h"

BtnToggle *BtnToggle::createToggle(const string &fileName,
								   const string &title,
								   float x, float y) {
	// New
	BtnToggle *sprite = new BtnToggle(title, x, y);
	if (sprite && sprite->init(fileName.c_str())) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

BtnToggle::BtnToggle(const string &title, float x, float y) : BtnBase(title, x, y) {
	LOGD("Main", "BtnToggle()\n");
}

BtnToggle::~BtnToggle() {
	LOGD("Main", "~BtnToggle()\n");
}

bool BtnToggle::init(const char *fileName) {
	// Load graph
	graph = UtilGraph::getInstance()->getGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	title = (UtilSound::getInstance()->isMute()) ? "X" : "O";
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
	title = (UtilSound::getInstance()->isMute()) ? "X" : "O";
	return true;
}