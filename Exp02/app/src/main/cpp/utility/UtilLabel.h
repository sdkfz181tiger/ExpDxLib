#ifndef _UTILLABEL_H_
#define _UTILLABEL_H_

#include "Utility.h"

enum class UtilAlign {
	DEFAULT,
	LEFT,
	RIGHT,
	CENTER
};

class UtilLabel {

private:
	map<char, int> handleMap;
	int fWidth, fHeight;
	const float fPadding;
	const int black;

public:
	UtilLabel();

	~UtilLabel();

	static UtilLabel *getInstance();

	void destroyInstance();

	bool init();

	string toUpper(const string &str);

	string toLower(const string &str);

	void drawStr(const string &str, int x, int y,
				 int scale = 1, UtilAlign align = UtilAlign::DEFAULT);
};

#endif // _UTILLABEL_H_