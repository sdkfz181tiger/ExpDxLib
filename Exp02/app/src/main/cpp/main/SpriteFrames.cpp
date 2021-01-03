#include "SpriteFrames.h"

SpriteFrames *SpriteFrames::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteFrames *sprite = new SpriteFrames(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteFrames::SpriteFrames(float x, float y) : SpriteBase(x, y),
											   frameCnt(0), frameInterval(5),
											   frameIndex(0), frameLoop(-1) {
	LOGD("Main", "SpriteFrames()\n");
}

SpriteFrames::~SpriteFrames() {
	LOGD("Main", "~SpriteFrames()\n");
}

bool SpriteFrames::init(const string &fileName) {
	if (!SpriteBase::init(fileName)) return false;

	// Frames
	this->pushFrames("bone");
	this->changeFrames("bone", -1);

	return true;
}

void SpriteFrames::pushFrames(const string &frameName) {
	frameMap.insert(make_pair(frameName, UtilGraph::getInstance()->getDivGraph(frameName)));
}

void SpriteFrames::changeFrames(const string &frameName, int loop) {
	if (frameMap.count(frameName) <= 0) return;
	frames = frameMap.find(frameName)->second;
	frameCnt = 0;
	frameIndex = 0;
	frameLoop = loop;
}

void SpriteFrames::stopFrames() {
	frameLoop = 0;
}

void SpriteFrames::update(const float delay) {
	// Move
	if (this->getMoveFlg()) {
		pos.x += vel.x * delay;
		pos.y += vel.y * delay;
	}
	// Draw
	this->draw();
}

void SpriteFrames::draw() {
	// Rect
	minX = pos.x - width / 2;
	maxX = pos.x + width / 2;
	minY = pos.y - height / 2;
	maxY = pos.y + height / 2;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, frames.at(frameIndex), true);
	if (frameLoop == 0) return;
	if (++frameCnt < frameInterval) return;
	frameCnt = 0;
	if (++frameIndex < frames.size()) return;
	frameIndex = 0;
	if (0 < frameLoop) frameLoop--;
}