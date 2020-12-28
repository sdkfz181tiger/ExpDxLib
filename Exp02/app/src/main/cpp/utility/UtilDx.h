#ifndef _UTILDX_H_
#define _UTILDX_H_

#include "Utility.h"

class UtilDx {

private:
	bool quitFlg;
	const int defScale;

public:
	UtilDx();

	~UtilDx();

	static UtilDx *getInstance();

	void destroyInstance();

	bool init();

	void setQuitFlg();

	bool getQuitFlg();

	int getDefScale();
};

#endif // _UTILDX_H_