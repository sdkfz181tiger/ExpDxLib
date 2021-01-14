#ifndef _SPRITECHARA_H_
#define _SPRITECHARA_H_

#include "SpriteFrames.h"

enum class TypeChara {
	DEFAULT, CHI_M, CHI_F, HIYO, TANU, OSHO, KOBO
};

enum class StateChara {
	DEFAULT, STAY, IDLE, WALK
};

class SpriteChara : public SpriteFrames {

protected:
	TypeChara type;
	StateChara state;
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

	void setType(TypeChara typ);

	TypeChara getType() const;

	virtual void changeState(StateChara sta);

	void startStay();

	void startIdle();

	void startWalk(int spd, int x, int y, bool flg);

	void startWalk(int spd, int deg, bool flg);
};

#endif // _SPRITECHARA_H_