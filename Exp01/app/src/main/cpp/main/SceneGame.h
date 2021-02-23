#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "SceneBase.h"

class SceneGame : public SceneBase, BtnListener, DpadListener, EggListener {

private:
	enum UpdateMode {
		READY, START, FINISH
	};
	UpdateMode updateMode;
	int waitCnt, waitInterval;

private:
	SpriteBase *background;
	MazeManager *mManager;
	StatusBar *sBar;
	CtlDpad *dPad;
	SpriteKobo *player;
	SpriteOsho *osho;
	SpriteChicken *chicken;
	SpriteTanu *tanuA, *tanuB;
	vector<SpriteEgg *> eggs;
	vector<SpriteChick *> chicks;
	vector<MsgHopper *> hoppers;

public:
	static SceneGame *createScene(int dWidth, int dHeight);

	SceneGame(int dWidth, int dHeight);

	~SceneGame() override;

	bool init() override;

	void setOnTouchBegan(int id, int x, int y) override;

	void setOnTouchMoved(int id, int x, int y) override;

	void setOnTouchEnded(int id, int x, int y) override;

	void update(const float delay) override;

	void onBtnPressed(BtnTag &tag) override;

	void onBtnCanceled(BtnTag &tag) override;

	void onBtnReleased(BtnTag &tag) override;

	void onDpadPressed(DpadTag &tag) override;

	void onDpadCanceled(DpadTag &tag) override;

	void onDpadReleased(DpadTag &tag) override;

	void onDpadChanged(DpadTag &tag) override;

	void gameReady(const float delay);

	void gameStart(const float delay);

	void gameFinish(const float delay);

	void onEggLayed(int x, int y) override;

	void chainChick(int num, int x, int y);

	void purgeChick();
};

#endif // _SCENEGAME_H_