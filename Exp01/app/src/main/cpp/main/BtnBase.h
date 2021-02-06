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
	Vec2 pos;
	int graph, width, height, scale;
	int minX, maxX, minY, maxY;
	bool touchFlg;
	int touchID;
	string title;

	// EventListener
	BtnListener *btnListener;
	BtnTag btnTag;

public:
	static BtnBase *createBtn(const string &fileName,
							  float x, float y);

	BtnBase(float x, float y);

	virtual ~BtnBase();

	virtual bool init(const char *fileName);

	void offsetPos(int x, int y);

	void setScale(int scale);

	void setTitle(string str);

	bool containsPoint(int x, int y);

	virtual bool setOnTouchBegan(int id, int x, int y);

	virtual bool setOnTouchMoved(int id, int x, int y);

	virtual bool setOnTouchEnded(int id, int x, int y);

	virtual void update(const float delay);

	void addBtnListener(BtnListener *listener, BtnTag tag);
};

#endif // _BTNBASE_H_