#ifndef _BTNTOGGLE_H_
#define _BTNTOGGLE_H_

#include "BtnBase.h"

class BtnToggle : public BtnBase {

public:
	static BtnToggle *createToggle(const string &fileName,
								   const string &title,
								   float x, float y);

	BtnToggle(const string &title, float x, float y);

	virtual ~BtnToggle();

	bool init(const char *fileName) override;

	bool setOnTouchBegan(int id, int x, int y) override;

	bool setOnTouchMoved(int id, int x, int y) override;

	bool setOnTouchEnded(int id, int x, int y) override;
};

#endif // _BTNTOGGLE_H_