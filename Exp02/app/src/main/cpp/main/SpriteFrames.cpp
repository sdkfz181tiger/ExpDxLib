#include "SpriteFrames.h"

SpriteFrames *SpriteFrames::createSprite(const string &fileName, float x, float y) {
	// New
	SpriteFrames *sprite = new SpriteFrames(x, y);
	if (sprite && sprite->init(fileName)) return sprite;
	DX_SAFE_DELETE(sprite);
	return nullptr;
}

SpriteFrames::SpriteFrames(float x, float y) : SpriteBase(x, y),
											   frameIndex(0), frameCnt(0), frameInterval(5) {
	LOGD("Main", "SpriteFrames()\n");
}

SpriteFrames::~SpriteFrames() {
	LOGD("Main", "~SpriteFrames()\n");
}

bool SpriteFrames::init(const string &fileName) {
	if (!SpriteBase::init(fileName)) return false;

	// Frames
	this->pushFrames("bone");
	this->changeFrames("bone");

	return true;
}

void SpriteFrames::pushFrames(const string &frameName) {
	frameMap.insert(make_pair(frameName, UtilGraph::getInstance()->getDivGraph(frameName)));
}

void SpriteFrames::changeFrames(const string &frameName) {
	if (frameMap.count(frameName) <= 0) return;
	frames = frameMap.find(frameName)->second;
}

void SpriteFrames::update(float delay) {
	// Velocity
	pos.x += vel.x * delay;
	pos.y += vel.y * delay;
	// Rect
	minX = pos.x - width / 2;
	maxX = pos.x + width / 2;
	minY = pos.y - height / 2;
	maxY = pos.y + height / 2;
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, frames.at(frameIndex), true);
	if (++frameCnt < frameInterval) return;
	frameCnt = 0;
	if (++frameIndex < frames.size()) return;
	frameIndex = 0;
}