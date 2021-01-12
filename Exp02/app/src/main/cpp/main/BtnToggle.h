#ifndef _BTNTOGGLE_H_
#define _BTNTOGGLE_H_

#include "BtnBase.h"

class BtnToggle : public BtnBase {

protected:

public:
	static BtnToggle *createToggle(const string &fileName,
								   const string &title,
								   float x, float y);

	BtnToggle(const string &title, float x, float y);

	virtual ~BtnToggle();

	bool init(const char *fileName) override;
};

#endif // _BTNTOGGLE_H_