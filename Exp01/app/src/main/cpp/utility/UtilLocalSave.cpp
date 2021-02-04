#include "UtilLocalSave.h"

// Singleton Object
static UtilLocalSave *selfUtilLocalSave = nullptr;

UtilLocalSave::UtilLocalSave() : fileName("data.json") {
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
	if (!this->isOpen()) this->resetData();
	this->loadData();
	return true;
}

void UtilLocalSave::resetData() {
	LOGD("Util", "resetData()\n");
	const string fullPath = this->getFullPath();
	json data = R"({})"_json;
	string str = data.dump();
	size_t size = static_cast<streamsize>(str.length());
	ofstream ofstr(fullPath.c_str());
	ofstr.write(str.c_str(), size);
	ofstr.close();
}

void UtilLocalSave::loadData() {
	LOGD("Util", "loadData()\n");
	const string fullPath = this->getFullPath();
	ifstream ifstr;
	ifstr.open(fullPath.c_str(), ios::in);
	string line, str;
	while (!ifstr.eof()) {
		getline(ifstr, line);
		str += line;
	}
	jsonObj = json::parse(str);
}

void UtilLocalSave::saveData() {
	LOGD("Util", "saveData()\n");
	const string fullPath = this->getFullPath();
	string str = jsonObj.dump();
	size_t size = static_cast<streamsize>(str.length());
	ofstream ofstr(fullPath.c_str());
	ofstr.write(str.c_str(), size);
	ofstr.close();
}

bool UtilLocalSave::isOpen() {
	const string fullPath = this->getFullPath();
	ifstream ifstr;
	ifstr.open(fullPath.c_str(), ios::in);
	bool flg = ifstr.is_open();
	ifstr.close();
	return flg;
}

string UtilLocalSave::getFullPath() {
	string str = UtilJNI::getInstance()->getFilePath() + "/";
	string fullPath;
	size_t len = str.length();
	for (size_t i = len - 1; 0 <= i && i != string::npos; i = str.rfind('/')) {
		fullPath.insert(0, "/" + str.substr(i + 1, str.length()));
		str = str.substr(0, i);
	}
	return fullPath + fileName;
}

bool UtilLocalSave::getBool(const string &key, bool def) {
	if (jsonObj.count(key) <= 0) {
		jsonObj[key] = def;
	}
	return jsonObj.find(key).value();
}

void UtilLocalSave::setBool(const string &key, bool flg) {
	if (jsonObj[key] == flg) return;
	jsonObj[key] = flg;
	this->saveData();
}

int UtilLocalSave::getNum(const string &key, int def) {
	if (jsonObj.count(key) <= 0) {
		jsonObj[key] = def;
	}
	return jsonObj.find(key).value();
}

void UtilLocalSave::setNum(const string &key, const int num) {
	if (jsonObj[key] == num) return;
	jsonObj[key] = num;
	this->saveData();
}

string UtilLocalSave::getString(const string &key, string def) {
	if (jsonObj.count(key) <= 0) {
		jsonObj[key] = def;
	}
	return jsonObj.find(key).value();
}

void UtilLocalSave::setString(const string &key, const string str) {
	if (jsonObj[key] == str) return;
	jsonObj[key] = str;
	this->saveData();
}