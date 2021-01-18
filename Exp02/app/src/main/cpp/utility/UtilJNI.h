#ifndef _UTILJNI_H_
#define _UTILJNI_H_

#include "Utility.h"

enum class CallbackType {
	DEFAULT, SUCCESS, PROGRESS, ERROR
};

class UtilJNI {

private:
	function<void(CallbackType)> callback;

public:
	UtilJNI();

	~UtilJNI();

	static UtilJNI *getInstance();

	void destroyInstance();

	jint init(JavaVM *vm);

	jint registerMethods(JNIEnv *env);

	void callJNIVoid(const char *methodName, const char *url, const char *fileName);

	string callJNIStr(const char *methodName);

	void connectServer(const char *url, const char *fileName,
			function<void(CallbackType)> func);

	void callbackClient(CallbackType type);

	string getVersionCode();

	string getVersionName();

	string getFilePath();
};

#endif // _UTILJNI_H_