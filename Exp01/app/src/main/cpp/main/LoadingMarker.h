#ifndef _LOADINGMARKER_H_
#define _LOADINGMARKER_H_

#include "Utility.h"

class LoadingMarker {

private:
	Vec2 pos;
	int width, height;
	int loadCnt, loadTotal;
	string loadMsg;
	unsigned int white, gray;

public:
	static LoadingMarker *createMarker(float x, float y, int w, int h);

	LoadingMarker(float x, float y, int w, int h);

	virtual ~LoadingMarker();

	bool init();

	void setMsg(const char *msg);

	void setCnt(int cnt);

	int getCnt();

	void setTotal(int total);

	void progress(int progress);

	void update();
};

#endif // _LOADINGMARKER_H_