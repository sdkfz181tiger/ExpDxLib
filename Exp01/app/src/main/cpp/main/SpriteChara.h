#ifndef _SPRITECHARA_H_
#define _SPRITECHARA_H_

#include "SpriteFrames.h"

class TypeChara {
public:
	const static int DEFAULT = 0;
};

class StateChara {
public:
	const static int DEFAULT = 0;
	const static int STAY = 1;
	const static int IDLE = 2;
	const static int WALK = 3;
};

class SpriteChara : public SpriteFrames {

protected:
	int type, state;
	int stayCnt, stayInterval;
	int idleCnt, idleInterval;
	Vec2 walkDst;
	float walkLen;
	bool walkFlg;

public:
	static SpriteChara *createSprite(const string &fileName, float x, float y);

	SpriteChara(float x, float y);

	virtual ~SpriteChara();

	virtual bool init(const string &fileName) override;

	virtual void update(const float delay) override;

	void setType(int typ);

	int getType() const;

	virtual void changeState(int sta);

	void startStay();

	void startIdle();

	void startWalk(int spd, int x, int y, bool flg);

	void startWalk(int spd, int deg, bool flg);
};

#endif // _SPRITECHARA_H_