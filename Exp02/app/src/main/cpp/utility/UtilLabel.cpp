#include "UtilLabel.h"

// Singleton Object
static UtilLabel *selfUtilLabel = nullptr;

UtilLabel::UtilLabel() : fWidth(0), fHeight(0), fPadding(1.2f),
						 black(GetColor(0, 0, 0)) {
	LOGD("Util", "UtilLabel()\n");
}

UtilLabel::~UtilLabel() {
	LOGD("Util", "~UtilLabel()\n");
}

UtilLabel *UtilLabel::getInstance() {
	if (selfUtilLabel) return selfUtilLabel;
	selfUtilLabel = new UtilLabel();
	if (selfUtilLabel && selfUtilLabel->init()) return selfUtilLabel;
	DX_SAFE_DELETE(selfUtilLabel);
	return nullptr;
}

void UtilLabel::destroyInstance() {
	if (!selfUtilLabel) return;

	delete (selfUtilLabel);
	selfUtilLabel = nullptr;
}

bool UtilLabel::init() {
	LOGD("Util", "UtilLabel::init()\n");

	// Number
	const string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ.,:;/-!?'()[]*%+=";
	int gW, gH = 0;
	for (int i = 0; i < str.length(); i++) {
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

	int gOffX = fWidth * scale * fPadding;
	int gOffY = fHeight * scale / 2;
	int gWidth = gOffX * str.length();
	if (align == UtilAlign::LEFT) x -= 0;
	if (align == UtilAlign::RIGHT) x -= gWidth;
	if (align == UtilAlign::CENTER) x -= gWidth / 2;
	y -= gOffY;

	DrawBox(x, y - gOffY, x + gOffX * str.length(), y + gOffY * 2, black, true);
	for (int i = 0; i < str.length(); i++) {
		const char c = str.at(i);
		if (0 < handleMap.count(c)) {
			DrawExtendGraph(x, y - gOffY,
							x + fWidth * scale,
							y + fHeight * scale,
							handleMap.find(c)->second, true);
		}
		x += gOffX;
	}
}