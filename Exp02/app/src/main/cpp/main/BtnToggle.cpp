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
	graph = LoadGraph(fileName);
	if (graph == -1) return false;
	GetGraphSize(graph, &width, &height);
	this->setScale(UtilDx::getInstance()->getDefScale());
	return true;
}