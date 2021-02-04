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
	bool getBool(const string &key, bool def);

	void setBool(const string &key, const bool flg);

	int getNum(const string &key, int def);

	void setNum(const string &key, const int num);

	string getString(const string &key, string def);

	void setString(const string &key, const string str);
};

#endif // _UTILLOCALSAVE_H_