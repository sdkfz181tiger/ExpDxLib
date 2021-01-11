#ifndef _UTILLOCALSAVE_H_
#define _UTILLOCALSAVE_H_

#include "Utility.h"

class UtilLocalSave {

private:

public:
	UtilLocalSave();

	~UtilLocalSave();

	static UtilLocalSave *getInstance();

	void destroyInstance();

	bool init();

	void test();

	string getFullPath(string dirPath, string fileName);
};

#endif // _UTILLOCALSAVE_H_