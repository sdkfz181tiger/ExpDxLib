#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

#include "SceneBase.h"
#include "BtnBase.h"

class SceneGame : public SceneBase, BtnListener {

private:
	SceneListener *sceneListener;
	BtnBase *btnQuit, *btnTest;
	vector<SpriteBase *> sprites;

public:
	static SceneGame *createScene(int dWidth, int dHeight);

	SceneGame(int dWidth, int dHeight);

	~SceneGame() override;

	bool init() override;

	void setOnTouchBegan(int id, int x, int y) override;

	void setOnTouchMoved(int id, int x, int y) override;

	void setOnTouchEnded(int id, int x, int y) override;

	void update(const float delay) override;

	void addSceneListener(SceneListener *sceneListener) override;

	void onBtnPressed(BtnTag &tag) override;

	void onBtnCanceled(BtnTag &tag) override;

	void onBtnReleased(BtnTag &tag) override;
};

#endif // _SCENEGAME_H_