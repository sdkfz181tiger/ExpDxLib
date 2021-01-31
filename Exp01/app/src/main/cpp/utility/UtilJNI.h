#ifndef _UTILJNI_H_
#define _UTILJNI_H_

#include "Utility.h"

enum class CallbackType {
	DEFAULT, SUCCESS, PROGRESS, ERROR
};

class UtilJNI {

private:
	function<void(CallbackType, const char *)> callbackGitHub;

public:
	UtilJNI();

	~UtilJNI();

	static UtilJNI *getInstance();

	void destroyInstance();

	jint init(JavaVM *vm);

	jint registerMethods(JNIEnv *env);

	void callJNIVoid(const char *methodName);

	void callJNIVoid(const char *methodName, const char *url, const char *fileName);

	string callJNIStr(const char *methodName);

	int callJNIInt(const char *methodName);

	bool callJNIBool(const char *methodName);

	void connectAdMob();

	void connectGitHub(const char *url, const char *fileName,
					   function<void(CallbackType, const char *)> func);

	void callbackClient(CallbackType type, const char *fileName);

	string getVersionCode();

	string getVersionName();

	string getFilePath();

	int getScreenWidth();

	int getScreenHeight();

	int getAdHeight();

	bool getDebugFlg();
};

#endif // _UTILJNI_H_