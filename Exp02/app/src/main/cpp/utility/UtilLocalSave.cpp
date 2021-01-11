#include "UtilLocalSave.h"

// Singleton Object
static UtilLocalSave *selfUtilLocalSave = nullptr;

UtilLocalSave::UtilLocalSave() {
	LOGD("Util", "UtilLocalSave()\n");
}

UtilLocalSave::~UtilLocalSave() {
	LOGD("Util", "~UtilLocalSave()\n");
}

UtilLocalSave *UtilLocalSave::getInstance() {
	if (selfUtilLocalSave) return selfUtilLocalSave;
	selfUtilLocalSave = new UtilLocalSave();
	if (selfUtilLocalSave && selfUtilLocalSave->init()) return selfUtilLocalSave;
	DX_SAFE_DELETE(selfUtilLocalSave);
	return nullptr;
}

void UtilLocalSave::destroyInstance() {
	if (!selfUtilLocalSave) return;

	delete (selfUtilLocalSave);
	selfUtilLocalSave = nullptr;
}

bool UtilLocalSave::init() {
	LOGD("Util", "UtilLocalSave::init()\n");
	return true;
}

void UtilLocalSave::test() {
	LOGD("Util", "UtilLocalSave::test()\n");
	// Open file
	string filePath = UtilJNI::getInstance()->getFilePath();
	string fullPath = this->getFullPath(filePath, "hoge.txt");
	LOGD("Util", "fullPath::%s\n", fullPath.c_str());

	int handle = FileRead_open(fullPath.c_str(), true);
	if (handle < 0) return;
	LOGD("Util", "open:%d\n", handle);
	FileRead_close(handle);
}

string UtilLocalSave::getFullPath(string dirPath, string fileName) {
	string str = dirPath;
	string fullPath;
	size_t len = str.length();
	for (size_t i = len - 1; 0 <= i && i != string::npos; i = str.rfind('/')) {
		fullPath.insert(0, "/" + str.substr(i + 1, str.length()));
		str = str.substr(0, i);
	}
	return fullPath + fileName;
}