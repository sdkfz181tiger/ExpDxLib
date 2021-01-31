#ifndef _BTNTOGGLE_H_
#define _BTNTOGGLE_H_

#include "BtnBase.h"

class BtnToggle : public BtnBase {

private:
	int graphOn, graphOff;

public:
	static BtnToggle *createToggle(const string &fileNameOn,
								   const string &fileNameOff,
								   float x, float y);

	BtnToggle(float x, float y);

	virtual ~BtnToggle();

	bool init(const char *fileNameOn, const char *fileNameOff);

	bool setOnTouchBegan(int id, int x, int y) override;

	bool setOnTouchMoved(int id, int x, int y) override;

	bool setOnTouchEnded(int id, int x, int y) override;

	void update(float delay) override;
};

#endif // _BTNTOGGLE_H_