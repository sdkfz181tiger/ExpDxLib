#ifndef _SPRITEFRAMES_H_
#define _SPRITEFRAMES_H_

#include "SpriteBase.h"

class SpriteFrames : public SpriteBase {

private:
	map<string, vector<int>> frameMap;
	vector<int> frames;
	int frameCnt, frameInterval, frameIndex, frameLoop;

public:
	static SpriteFrames *createSprite(const string &fileName, float x, float y);

	SpriteFrames(float x, float y);

	virtual ~SpriteFrames();

	virtual bool init(const string &fileName) override;

	void pushFrames(const string &frameName);

	void changeFrames(const string &frameName, int loop);

	void startFrames(int loop);

	void stopFrames();

	virtual void update(const float delay) override;

	virtual void draw() override;
};

#endif // _SPRITEFRAMES_H_