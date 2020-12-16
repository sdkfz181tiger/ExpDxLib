#include "UtilLabel.h"

// Singleton Object
static UtilLabel *selfUtilLabel = nullptr;

UtilLabel::UtilLabel() : fWidth(0), fHeight(0), fPadding(1.2f) {
	LOGD("Util", "UtilLabel()\n");
}

UtilLabel::~UtilLabel() {
	LOGD("Util", "~UtilLabel()\n");
}

UtilLabel *UtilLabel::getInstance() {

	if (!selfUtilLabel) {
		selfUtilLabel = new UtilLabel();
		if (selfUtilLabel && selfUtilLabel->init()) {
			return selfUtilLabel;
		} else {
			delete (selfUtilLabel);
			selfUtilLabel = nullptr;
		}
	}
	return selfUtilLabel;
}

void UtilLabel::destroyInstance() {
	if (!selfUtilLabel) return;

	delete (selfUtilLabel);
	selfUtilLabel = nullptr;
}

bool UtilLabel::init() {
	LOGD("Util", "UtilLabel::init()\n");

	// Number
	const string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.,:;!?";
	int gW, gH = 0;
	for (int i = 0; i < str.length(); ++i) {
		string key = str.substr(i, 1);// Important!!
		if (key == ":") key = "_colon";
		if (key == ",") key = "_comma";
		if (key == ".") key = "_dot";
		if (key == ";") key = "_semicolon";
		if (key == "/") key = "_slash";
		char path[30];
		sprintf(path, "fonts/white/%s.png", key.c_str());
		int handle = LoadGraph(path);
		if (0 <= handle) GetGraphSize(handle, &gW, &gH);
		handleMap[str.at(i)] = handle;
		if (fWidth < gW) fWidth = gW;
		if (fHeight < gH) fHeight = gH;
	}

	return true;
}

void UtilLabel::drawStr(const string &str, int x, int y,
						int scale, UtilAlign align) {

	int gX = x;
	int gY = y;
	int gPadding = fWidth * fPadding * scale;
	int gWidth = gPadding * str.length();
	if (align == UtilAlign::LEFT) gX -= 0;
	if (align == UtilAlign::RIGHT) gX -= gWidth;
	if (align == UtilAlign::CENTER) gX -= gWidth / 2;
	for (int i = 0; i < str.length(); ++i) {
		const char c = str.at(i);
		const int handle = handleMap[c];
		if (0 <= handle)
			DrawExtendGraph(gX, gY,
			                gX + fWidth * scale,
			                gY + fHeight * scale, handle,
			                true);
		gX += gPadding;
	}
}