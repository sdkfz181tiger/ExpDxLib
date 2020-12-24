#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

#include "Utility.h"
#include "BtnBase.h"
#include "SpriteBase.h"

class SceneBase {

protected:
	const int dWidth, dHeight;

public:
	SceneBase(int dWidth, int dHeight);

	virtual ~SceneBase();

	virtual bool init() = 0;

	virtual void setOnTouchBegan(int id, int x, int y) = 0;

	virtual void setOnTouchMoved(int id, int x, int y) = 0;

	virtual void setOnTouchEnded(int id, int x, int y) = 0;

	virtual void update(const float delay) = 0;
};

#endif // _SCENEBASE_H_