#ifndef _UTILJNI_H_
#define _UTILJNI_H_

#include "Utility.h"

class UtilJNI {

private:

public:
	UtilJNI();

	~UtilJNI();

	static UtilJNI *getInstance();

	void destroyInstance();

	jint init(JavaVM *vm);

	jint registerMethods(JNIEnv *env);

	void test();
};

#endif // _UTILJNI_H_