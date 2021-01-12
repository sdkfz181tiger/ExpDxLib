#ifndef _UTILLOCALSAVE_H_
#define _UTILLOCALSAVE_H_

#include "Utility.h"

class UtilLocalSave {

private:
	const string fileName;
	json jsonObj;

public:
	UtilLocalSave();

	~UtilLocalSave();

	static UtilLocalSave *getInstance();

	void destroyInstance();

	bool init();

private:
	void resetData();

	void loadData();

	void saveData();

	bool isOpen();

	string getFullPath();

public:
	bool getBool(const string &key);

	void setBool(const string &key, const bool flg);

	string getString(const string &key);

	void setString(const string &key, const string &str);
};

#endif // _UTILLOCALSAVE_H_