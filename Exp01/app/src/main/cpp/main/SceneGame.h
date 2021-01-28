#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "SceneBase.h"

class SceneGame : public SceneBase, BtnListener, DpadListener, EggListener {

private:
	SpriteBase *background;
	BoardGrid *bGrid;
	CtlDpad *dPad;
	SpriteKobo *player;
	SpriteChicken *chicken;
	SpriteTanu *tanu;
	vector<SpriteEgg *> eggs;
	vector<SpriteChick *> chicks;

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

	void onEggLayed(int x, int y) override;

	void chainChick(int num);

	void purgeChick();
};

#endif // _SCENEGAME_H_