#ifndef _SPRITETANU_H_
#define _SPRITETANU_H_

#include "SpriteChara.h"

class StateTanu : public StateChara {
public:
	const static int WANDER = 101;
	const static int CAPTURED = 102;
	const static int ESCAPE = 103;
};

class SpriteTanu : public SpriteChara {

private:
	int wanCnt, wanInterval;
	int capCnt, capInterval;
	int escCnt, escInterval;
	bool hiyoFlg;

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

	void setHiyoFlg(bool flg);

	bool getHiyoFlg() { return hiyoFlg; }
};

#endif // _SPRITETANU_H_