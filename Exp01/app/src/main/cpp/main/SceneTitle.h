#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

#include "SceneBase.h"

class SceneTitle : public SceneBase {

private:
	SpriteBase *tSprite;

public:
	SceneTitle(int dWidth, int dHeight);

	~SceneTitle() override;

	void init() override;

	void setOnTouchBegan(int id, int x, int y) override;

	void setOnTouchMoved(int id, int x, int y) override;

	void setOnTouchEnded(int id, int x, int y) override;

	void update(const float delay) override;
};

#endif // _SCENETITLE_H_