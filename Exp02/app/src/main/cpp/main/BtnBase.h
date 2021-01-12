#ifndef _BTNBASE_H_
#define _BTNBASE_H_

#include "Utility.h"

// BtnTag
enum class BtnTag {
	DEFAULT, QUIT,
	TITLE, GAME, RESULT, SOUND
};

// BtnListener
class BtnListener {
public:
	virtual void onBtnPressed(BtnTag &tag) = 0;

	virtual void onBtnCanceled(BtnTag &tag) = 0;

	virtual void onBtnReleased(BtnTag &tag) = 0;
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
	BtnListener *btnListener;
	BtnTag btnTag;

public:
	static BtnBase *createBtn(const string &fileName,
							  const string &title,
							  float x, float y);

	BtnBase(const string &title, float x, float y);

	virtual ~BtnBase();

	virtual bool init(const char *fileName);

	void setScale(int scale);

	bool containsPoint(int x, int y);

	void setOnTouchBegan(int id, int x, int y);

	void setOnTouchMoved(int id, int x, int y);

	void setOnTouchEnded(int id, int x, int y);

	void update(const float delay);

	void addBtnListener(BtnListener *listener, BtnTag tag);
};

#endif // _BTNBASE_H_