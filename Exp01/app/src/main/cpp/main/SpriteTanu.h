#ifndef _SPRITETANU_H_
#define _SPRITETANU_H_

#include "SpriteChara.h"
#include "SpriteChick.h"

class StateTanu : public StateChara {
public:
	const static int WANDER = 101;
	const static int CAPTURED = 102;
	const static int ESCAPE = 103;
	const static int RELEASE = 104;
};

class SpriteTanu : public SpriteChara {

private:
	int wanCnt, wanInterval;
	int capCnt, capInterval;
	int escCnt, escInterval;
	int relCnt, relInterval;
	bool chickFlg;
	SpriteChick *chick;

public:
	static SpriteTanu *createSprite(const string &fileName, float x, float y);

	SpriteTanu(float x, float y);

	virtual ~SpriteTanu();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;

	void startWander();

	void startCapture();

	void startEscape();

	void startRelease();

	void setChickFlg(bool flg);

	bool getChickFlg() { return chickFlg; }
};

#endif // _SPRITETANU_H_