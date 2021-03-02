#ifndef _SPRITEMAZE_H_
#define _SPRITEMAZE_H_

#include "SpriteChara.h"
#include "MazeManager.h"

class StateMaze : public StateChara {
public:
	const static int FOLLOWWAY = 2021;
	const static int FOLLOWNEXT = 2022;
};

class SpriteMaze : public SpriteChara {

protected:
	MazeManager *mManager;
	vector<Vec2> ways;
	SpriteBase *leader;

public:
	static SpriteMaze *createSprite(const string &fileName, float x, float y);

	SpriteMaze(float x, float y);

	virtual ~SpriteMaze();

	virtual bool init(const string &fileName) override;

	void setMazeManager(MazeManager *mm);

	void showWays();

	void startFollowRdm();

	void startFollowLeader();

	void startFollowPos(int x, int y);

	void startFollowNext();

	void setLeader(SpriteBase *spr);

	bool searchLeaderInsight();

	bool checkLeaderOnSameRC();

	bool checkLeaderOnway();
};

#endif // _SPRITEMAZE_H_