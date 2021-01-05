#ifndef _CTLDPAD_H_
#define _CTLDPAD_H_

#include "Utility.h"

// DpadTag
enum class DpadTag {
	DEFAULT,
	LEFT, RIGHT, UP, DOWN
};

// DpadListener
class DpadListener {
public:
	virtual void onDpadPressed(DpadTag &tag) = 0;

	virtual void onDpadCanceled(DpadTag &tag) = 0;

	virtual void onDpadReleased(DpadTag &tag) = 0;

	virtual void onDpadChanged(DpadTag &tag) = 0;
};

class CtlDpad {

private:
	Vec2 pos, dpad;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;
	bool dpadFlg;
	int dpadID, dpadDir;

	// EventListener
	DpadListener *dpadListener;
	DpadTag dpadTag;

public:
	static CtlDpad *createDpad(const string &fileName, float x, float y);

	CtlDpad(float x, float y);

	virtual ~CtlDpad();

	bool init(const string &fileName);

	void setScale(int scl);

	bool containsPoint(int x, int y);

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void calcDirection(int x, int y);

	void update(const float delay);

	void addDpadListener(DpadListener *listener);
};

#endif // _CTLDPAD_H_