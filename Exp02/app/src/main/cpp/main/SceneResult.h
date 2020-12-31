#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

#include "SceneBase.h"

class SceneResult : public SceneBase, BtnListener {

private:
	SceneListener *sceneListener;
	BtnBase *btnQuit, *btnTest;

public:
	static SceneResult *createScene(int dWidth, int dHeight);

	SceneResult(int dWidth, int dHeight);

	~SceneResult() override;

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

#endif // _SCENERESULT_H_