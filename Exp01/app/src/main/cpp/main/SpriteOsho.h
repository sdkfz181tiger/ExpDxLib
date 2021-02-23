#ifndef _SPRITEOSHO_H_
#define _SPRITEOSHO_H_

#include "SpriteChara.h"
#include "MazeManager.h"

class StateOsho : public StateChara {
public:
	const static int FOLLOWWAY = 101;
	const static int FOLLOWNEXT = 102;
};

class SpriteOsho : public SpriteChara {

private:
	vector<Vec2> ways;
	MazeManager *mManager;

public:
	static SpriteOsho *createSprite(const string &fileName, float x, float y);

	SpriteOsho(float x, float y);

	virtual ~SpriteOsho();

	bool init(const string &fileName) override;

	void update(const float delay) override;

	void changeState(int sta) override;

	void startFollowway(const vector<Vec2> &poses, MazeManager *mm);

	void startFollownext();
};

#endif // _SPRITEOSHO_H_