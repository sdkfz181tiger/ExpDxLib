#ifndef _UTILJNI_H_
#define _UTILJNI_H_

#include "Utility.h"

class UtilJNI {

public:
	UtilJNI();

	~UtilJNI();

	static UtilJNI *getInstance();

	void destroyInstance();

	jint init(JavaVM *vm);

	jint registerMethods(JNIEnv *env);

	void callJNIVoid(const char *methodName, const char *url, const char *fileName);

	string getJNIStr(const char *methodName);

	string getVersionCode();

	string getVersionName();

	string getFilePath();

	void connectServer(const char *url, const char *fileName);
};

#endif // _UTILJNI_H_