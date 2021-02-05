#ifndef _SCENEPRELOAD_H_
#define _SCENEPRELOAD_H_

#include "SceneBase.h"

class ScenePreload : public SceneBase, BtnListener {

private:
	string vCode, vName;
	string dUrl, dPrefix;
	vector<string> fileNames;
	LoadingMarker *lMarker;

public:
	static ScenePreload *createScene(int dWidth, int dHeight);

	ScenePreload(int dWidth, int dHeight);

	~ScenePreload() override;

	bool init() override;

	void downloadJson(const char *fileName);

	void downloadAssets(const json &jObj);

	void downloadImages();

	bool checkAssets(const json &jObj);

	void setOnTouchBegan(int id, int x, int y) override;

	void setOnTouchMoved(int id, int x, int y) override;

	void setOnTouchEnded(int id, int x, int y) override;

	void update(const float delay) override;

	void onBtnPressed(BtnTag &tag) override;

	void onBtnCanceled(BtnTag &tag) override;

	void onBtnReleased(BtnTag &tag) override;

	void replaceSceneNext();
};

#endif // _SCENEPRELOAD_H_