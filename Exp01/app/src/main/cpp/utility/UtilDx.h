#ifndef _UTILDX_H_
#define _UTILDX_H_

#include "Utility.h"

class UtilDx {

private:
	bool quitFlg;
	const int dWidth, dHeight, dDepth, defScale, fps;

public:
	UtilDx();

	~UtilDx();

	static UtilDx *getInstance();

	void destroyInstance();

	bool init();

	void setQuitFlg();

	bool getQuitFlg() { return quitFlg; }

	int getDispWidth() { return dWidth; }

	int getDispHeight() { return dHeight; }

	int getDispDepth() { return dDepth; }

	int getDefScale() { return defScale; }

	int getFPS() { return fps; }

	bool isFileExists(const string &path);
};

#endif // _UTILDX_H_