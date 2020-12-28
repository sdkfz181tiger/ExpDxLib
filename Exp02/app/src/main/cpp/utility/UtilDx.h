#ifndef _UTILDX_H_
#define _UTILDX_H_

#include "Utility.h"

class UtilDx {

private:
	bool quitFlg;

public:
	UtilDx();

	~UtilDx();

	static UtilDx *getInstance();

	void destroyInstance();

	bool init();

	void setQuitFlg();

	bool getQuitFlg();
};

#endif // _UTILDX_H_