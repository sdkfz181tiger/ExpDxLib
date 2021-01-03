#ifndef _SPRITECHARA_H_
#define _SPRITECHARA_H_

#include "SpriteFrames.h"

enum class StateChara {
	DEFAULT, STAY, IDLE, WALK
};

class SpriteChara : public SpriteFrames {

protected:
	StateChara state;
	int stayCnt, stayInterval;
	int idleCnt, idleInterval;
	Vec2 walkDst;
	float walkLen;

public:
	static SpriteChara *createSprite(const string &fileName, float x, float y);

	SpriteChara(float x, float y);

	virtual ~SpriteChara();

	virtual bool init(const string &fileName) override;

	virtual void update(const float delay) override;

	virtual void changeState(StateChara sta);

	void startStay();

	void startIdle();

	void startWalk(int spd, int x, int y);
};

#endif // _SPRITECHARA_H_