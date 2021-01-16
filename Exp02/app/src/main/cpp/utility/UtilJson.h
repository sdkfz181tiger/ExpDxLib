#ifndef _UTILJSON_H_
#define _UTILJSON_H_

#include "Utility.h"

class UtilJson {

private:

public:
	UtilJson();

	~UtilJson();

	static UtilJson *getInstance();

	void destroyInstance();

	bool init();

	json loadJson(const char *fileName);

	json parseJson(const char *str);
};

#endif // _UTILJSON_H_