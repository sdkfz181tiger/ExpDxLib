#ifndef _SCENEPRELOAD_H_
#define _SCENEPRELOAD_H_

#include "SceneBase.h"

class ScenePreload : public SceneBase, BtnListener {

private:
	SceneListener *sceneListener;
	string vCode, vName;

public:
	static ScenePreload *createScene(int dWidth, int dHeight);

	ScenePreload(int dWidth, int dHeight);

	~ScenePreload() override;

	bool init() override;

	void setOnTouchBegan(int id, int x, int y) override;

	void setOnTouchMoved(int id, int x, int y) override;

	void setOnTouchEnded(int id, int x, int y) override;

	void update(const float delay) override;

	void addSceneListener(SceneListener *listener) override;

	void onBtnPressed(BtnTag &tag) override;

	void onBtnCanceled(BtnTag &tag) override;

	void onBtnReleased(BtnTag &tag) override;
};

#endif // _SCENEPRELOAD_H_