#ifndef _UTILLABEL_H_
#define _UTILLABEL_H_

#include "Utility.h"

enum class UtilLabelAlign {
	DEFAULT,
	LEFT,
	RIGHT,
	CENTER
};

class UtilLabel {

private:
	map<char, int> handleMap;
	int fWidth, fHeight;
	float fPadding;

public:
	UtilLabel();

	~UtilLabel();

	static UtilLabel *getInstance();

	void destroyInstance();

	bool init();

	void drawStr(const string &str, int x, int y, int scale = 1,
	             UtilLabelAlign align = UtilLabelAlign::DEFAULT);
};

#endif // _UTILLABEL_H_