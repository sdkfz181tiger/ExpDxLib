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

json UtilJson::read(const char *fileName) {
	LOGD("Util", "UtilJson::read()\n");
	// Read
	const int jHandle = FileRead_open(fileName);
	if (jHandle == -1) return json::object();
	char jLine[256];
	stringstream jStr;
	while (FileRead_eof(jHandle) == 0) {
		FileRead_gets(jLine, 256, jHandle);
		jStr << jLine;
	}
	FileRead_close(jHandle);
	return json::parse(jStr.str());;
}