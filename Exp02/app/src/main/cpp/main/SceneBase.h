#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "Utility.h"
#include "BtnBase.h"
#include "SpriteBase.h"
#include "SpriteEnemy.h"

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

public:
	SceneBase(int dWidth, int dHeight);

	virtual ~SceneBase();

	virtual bool init() = 0;

	virtual void setOnTouchBegan(int id, int x, int y) = 0;

	virtual void setOnTouchMoved(int id, int x, int y) = 0;

	virtual void setOnTouchEnded(int id, int x, int y) = 0;

	virtual void update(const float delay) = 0;

	virtual void addSceneListener(SceneListener *sceneListener) = 0;
};

#endif // _SCENEBASE_H_