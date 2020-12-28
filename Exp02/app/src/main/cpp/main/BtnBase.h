#ifndef _BTNBASE_H_
#define _BTNBASE_H_

#include "Utility.h"

// EventListener
class BtnEventListener {
public:
	virtual void onBtnPressed() = 0;

	virtual void onBtnCanceled() = 0;

	virtual void onBtnReleased() = 0;
};

class BtnBase {

protected:
	const string title;
	Vec2 pos;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;
	bool touchFlg;
	int touchID;

	// EventListener
	BtnEventListener *eventListener;

public:
	static BtnBase *createBtn(const string &fileName,
	                          const string &title,
	                          float x, float y);

	BtnBase(string title, float x, float y);

	virtual ~BtnBase();

	bool init(const char *fileName);

	void addEventListener(BtnEventListener *eventListener);

	void setPosition(float x, float y);

	void setScale(int scale);

	bool containsPoint(int x, int y);

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void update(const float delay);
};

#endif // _BTNBASE_H_