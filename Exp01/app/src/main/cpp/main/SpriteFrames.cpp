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
											   frameIndex(0), frameLoop(-1),
											   framePause(false) {
	//LOGD("Main", "SpriteFrames()\n");
}

SpriteFrames::~SpriteFrames() {
	//LOGD("Main", "~SpriteFrames()\n");
}

bool SpriteFrames::init(const string &fileName) {
	if (!SpriteBase::init(fileName)) return false;
	return true;
}

void SpriteFrames::changeFrames(const string &frameName, int loop) {
	// Frames
	frames = UtilGraph::getInstance()->getDivGraph(frameName);
	frameCnt = 0;
	frameIndex = 0;
	frameLoop = loop;
	framePause = false;
}

void SpriteFrames::pauseFrames() {
	framePause = true;
}

void SpriteFrames::resumeFrames() {
	framePause = false;
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
	if (frames.size() <= 0) {
		DrawExtendGraph(minX, minY, maxX, maxY, graph, true);
		return;
	}
	// Draw
	DrawExtendGraph(minX, minY, maxX, maxY, frames.at(frameIndex), true);
	if (frameLoop == 0) return;
	if (framePause) return;
	if (++frameCnt < frameInterval) return;
	frameCnt = 0;
	if (++frameIndex < frames.size()) return;
	frameIndex = 0;
	if (0 < frameLoop) frameLoop--;
}