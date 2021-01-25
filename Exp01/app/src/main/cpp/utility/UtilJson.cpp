#include "UtilJson.h"

// Singleton Object
static UtilJson *selfUtilJson = nullptr;

UtilJson::UtilJson() {
	LOGD("Util", "UtilJson()\n");
}

UtilJson::~UtilJson() {
	LOGD("Util", "~UtilJson()\n");
}

UtilJson *UtilJson::getInstance() {
	if (selfUtilJson) return selfUtilJson;
	selfUtilJson = new UtilJson();
	if (selfUtilJson && selfUtilJson->init()) return selfUtilJson;
	DX_SAFE_DELETE(selfUtilJson);
	return nullptr;
}

void UtilJson::destroyInstance() {
	if (!selfUtilJson) return;

	delete (selfUtilJson);
	selfUtilJson = nullptr;
}

bool UtilJson::init() {
	LOGD("Util", "UtilJson::init()\n");
	return true;
}

json UtilJson::loadJson(const char *fileName) {
	LOGD("Util", "UtilJson::loadJson()\n");
	// Read
	const int handle = FileRead_open(fileName);
	if (handle == 0) return json::object();
	char line[256];
	string str;
	while (FileRead_eof(handle) == 0) {
		FileRead_gets(line, 256, handle);
		str += line;
	}
	FileRead_close(handle);
	return json::parse(str);
}