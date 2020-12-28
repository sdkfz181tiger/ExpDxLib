#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "SceneBase.h"
#include "BtnBase.h"

class SceneTitle : public SceneBase, BtnListener {

private:
	BtnBase *btnQuit, *btnGame;
	vector<SpriteBase *> sprites;

public:
	static SceneTitle *createScene(int dWidth, int dHeight);

	SceneTitle(int dWidth, int dHeight);

	~SceneTitle() override;

	bool init() override;

	void setOnTouchBegan(int id, int x, int y) override;

	void setOnTouchMoved(int id, int x, int y) override;

	void setOnTouchEnded(int id, int x, int y) override;

	void update(const float delay) override;

	void onBtnPressed(BtnTag &tag) override;

	void onBtnCanceled(BtnTag &tag) override;

	void onBtnReleased(BtnTag &tag) override;
};

#endif // _SCENETITLE_H_