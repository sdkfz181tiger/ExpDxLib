#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "Utility.h"
#include "BoardGrid.h"
#include "BtnBase.h"
#include "BtnToggle.h"
#include "CtlDpad.h"
#include "StatusBar.h"
#include "ScoreHopper.h"
#include "SpriteBase.h"
#include "SpriteChick.h"
#include "SpriteChicken.h"
#include "SpriteEgg.h"
#include "SpriteFrames.h"
#include "SpriteItem.h"
#include "SpriteKobo.h"
#include "SpriteOsho.h"
#include "SpriteTanu.h"
#include "TimerCpp.h"

// SceneTag
enum class SceneTag {
	DEFAULT,
	TITLE, GAME, RESULT
};

// SceneListener
class SceneListener {
public:
	virtual void onSceneChange(SceneTag tag) = 0;
};

class SceneBase {

protected:
	const int dWidth, dHeight;
	vector<BtnBase *> btns;

private:
	SceneListener *sceneListener;
	bool sceneWaitFlg;
	float sceneWaitTime;
	SceneTag sceneNextTag;

public:
	SceneBase(int dWidth, int dHeight);

	virtual ~SceneBase();

	virtual bool init() = 0;

	virtual void setOnTouchBegan(int id, int x, int y) = 0;

	virtual void setOnTouchMoved(int id, int x, int y) = 0;

	virtual void setOnTouchEnded(int id, int x, int y) = 0;

	virtual void update(const float delay) = 0;

	void addSceneListener(SceneListener *listener);

	void replaceSceneWait(float wait, SceneTag tag);

	void replaceSceneTick(float delay);
};

#endif // _SCENEBASE_H_