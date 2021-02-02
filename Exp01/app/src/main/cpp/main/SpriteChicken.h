#ifndef _SPRITECHICKEN_H_
#define _SPRITECHICKEN_H_

#include "SpriteChara.h"

class StateChicken : public StateChara {
public:
	const static int GO = 101;
	const static int LAY = 102;
};

class EggListener {
public:
	virtual void onEggLayed(int x, int y) = 0;
};

class SpriteChicken : public SpriteChara {

private:
	int goCnt, goInterval;
	int layCnt, layInterval;

	Vec2 next, nest;
	int eggCnt, eggTotal;
	EggListener *eggListener;

public:
	static SpriteChicken *createSprite(const string &fileName, float x, float y);

	SpriteChicken(float x, float y);

	virtual ~SpriteChicken();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;

	void setNext(int x, int y);

	void setEggListener(EggListener *listener);

	void startGo();

	void startLay();
};

#endif // _SPRITECHICKEN_H_