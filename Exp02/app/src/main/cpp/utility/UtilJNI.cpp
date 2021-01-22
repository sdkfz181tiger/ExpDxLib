#include "UtilJNI.h"

// Singleton Object
static UtilJNI *selfUtilJNI = nullptr;

// Java Virtual machine
static string CLASS_NAME = "com/ozateck/chickader/MainActivity";
static JavaVM *javaVM = nullptr;
static pthread_key_t keyThread;
static jclass activity;

void nativeOnCreate(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onCreate!!");
}

void nativeOnStart(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onStart!!");
}

void nativeOnResume(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onResume!!");
}

void nativeOnPause(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onPause!!");
}

void nativeOnStop(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onStop!!");
}

void nativeOnDestroy(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onDestroy!!");
}

void nativeOnHttpSuccess(JNIEnv *env, jobject thiz, jstring fileName) {
	const char *strFileName = env->GetStringUTFChars(fileName, JNI_FALSE);
	//LOGD("JNI", "HttpSuccess:%s", strFileName);
	UtilJNI::getInstance()->callbackClient(CallbackType::SUCCESS, strFileName);// Callback
	env->ReleaseStringUTFChars(fileName, strFileName);
}

void nativeOnHttpProgress(JNIEnv *env, jobject thiz, jstring fileName) {
	const char *strFileName = env->GetStringUTFChars(fileName, JNI_FALSE);
	//LOGD("JNI", "HttpProgress:%s", strFileName);
	UtilJNI::getInstance()->callbackClient(CallbackType::PROGRESS, strFileName);// Callback
	env->ReleaseStringUTFChars(fileName, strFileName);
}

void nativeOnHttpError(JNIEnv *env, jobject thiz, jstring fileName, jstring err) {
	const char *strFileName = env->GetStringUTFChars(fileName, JNI_FALSE);
	const char *strErr = env->GetStringUTFChars(err, JNI_FALSE);
	//LOGE("JNI", "HttpError:%s, %s", strFileName, strErr);
	UtilJNI::getInstance()->callbackClient(CallbackType::ERROR, strFileName);// Callback
	env->ReleaseStringUTFChars(fileName, strFileName);
	env->ReleaseStringUTFChars(err, strErr);
}

static void detachThread(void *value) {
	LOGD("JNI", "threadDestroy!!");
	JNIEnv *env = (JNIEnv *) value;
	if (env == nullptr) return;
	javaVM->DetachCurrentThread();
	pthread_setspecific(keyThread, nullptr);
}

JNIEnv *Android_JNI_GetEnv(void) {
	JNIEnv *env;
	jint status = javaVM->AttachCurrentThread(&env, nullptr);
	if (status != JNI_OK) return nullptr;
	pthread_setspecific(keyThread, (void *) env);
	return env;
}

UtilJNI::UtilJNI() : callback(nullptr) {
	LOGD("JNI", "UtilJNI()\n");
}

UtilJNI::~UtilJNI() {
	LOGD("JNI", "~UtilJNI()\n");
}

UtilJNI *UtilJNI::getInstance() {
	if (selfUtilJNI) return selfUtilJNI;
	selfUtilJNI = new UtilJNI();
	if (selfUtilJNI) return selfUtilJNI;
	DX_SAFE_DELETE(selfUtilJNI);
	return nullptr;
}

void UtilJNI::destroyInstance() {
	if (!selfUtilJNI) return;

	delete (selfUtilJNI);
	selfUtilJNI = nullptr;
}

jint UtilJNI::init(JavaVM *vm) {
	LOGD("JNI", "UtilJNI::init(%p), %ld\n", javaVM, pthread_self());
	javaVM = vm;// Java virtual machine
	JNIEnv *env;
	if (javaVM->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) return JNI_ERR;
	if (pthread_key_create(&keyThread, detachThread) != JNI_OK) return JNI_ERR;
	if (this->registerMethods(env) != JNI_OK) return JNI_ERR;
	return JNI_VERSION_1_6;
}

jint UtilJNI::registerMethods(JNIEnv *env) {
	LOGD("JNI", "UtilJNI::registerMethods(%p), %ld\n", javaVM, pthread_self());
	jclass cls = env->FindClass(CLASS_NAME.c_str());
	if (cls == nullptr) return JNI_ERR;
	const JNINativeMethod methods[] = {
			{"nativeOnCreate",       "()V",
					reinterpret_cast<void *>(nativeOnCreate)},
			{"nativeOnStart",        "()V",
					reinterpret_cast<void *>(nativeOnStart)},
			{"nativeOnResume",       "()V",
					reinterpret_cast<void *>(nativeOnResume)},
			{"nativeOnPause",        "()V",
					reinterpret_cast<void *>(nativeOnPause)},
			{"nativeOnStop",         "()V",
					reinterpret_cast<void *>(nativeOnStop)},
			{"nativeOnDestroy",      "()V",
					reinterpret_cast<void *>(nativeOnDestroy)},
			{"nativeOnHttpSuccess",  "(Ljava/lang/String;)V",
					reinterpret_cast<void *>(nativeOnHttpSuccess)},
			{"nativeOnHttpProgress", "(Ljava/lang/String;)V",
					reinterpret_cast<void *>(nativeOnHttpProgress)},
			{"nativeOnHttpError",    "(Ljava/lang/String;Ljava/lang/String;)V",
					reinterpret_cast<void *>(nativeOnHttpError)}
	};
	int total = sizeof(methods) / sizeof(JNINativeMethod);
	if (env->RegisterNatives(cls, methods, total) != JNI_OK) return JNI_ERR;
	activity = (jclass) env->NewGlobalRef(cls);// Activity
	return JNI_OK;
}

void UtilJNI::callJNIVoid(const char *methodName, const char *url, const char *fileName) {
	//LOGD("JNI", "UtilJNI::callJNIVoid(%p), %ld\n", javaVM, pthread_self());
	JNIEnv *env = Android_JNI_GetEnv();
	if (env == nullptr) return;
	const char *sig = "(Ljava/lang/String;Ljava/lang/String;)V";
	const jmethodID mID = env->GetStaticMethodID(activity, methodName, sig);
	const jstring jUrl = env->NewStringUTF(url);
	const jstring jFileName = env->NewStringUTF(fileName);
	env->CallStaticVoidMethod(activity, mID, jUrl, jFileName);
	env->DeleteLocalRef(jUrl);
	env->DeleteLocalRef(jFileName);
}

string UtilJNI::callJNIStr(const char *methodName) {
	//LOGD("JNI", "UtilJNI::callJNIStr(%p), %ld\n", javaVM, pthread_self());
	JNIEnv *env = Android_JNI_GetEnv();
	if (env == nullptr) return "";
	const char *sig = "()Ljava/lang/String;";
	const jmethodID mID = env->GetStaticMethodID(activity, methodName, sig);
	const jstring jstr = (jstring) env->CallStaticObjectMethod(activity, mID);
	const char *cchar = env->GetStringUTFChars(jstr, JNI_FALSE);
	const string str = env->GetStringUTFChars(jstr, JNI_FALSE);
	env->ReleaseStringUTFChars(jstr, cchar);
	return str;
}

bool UtilJNI::callJNIBool(const char *methodName) {
	//LOGD("JNI", "UtilJNI::callJNIBool(%p), %ld\n", javaVM, pthread_self());
	JNIEnv *env = Android_JNI_GetEnv();
	if (env == nullptr) return false;
	const char *sig = "()Z";
	const jmethodID mID = env->GetStaticMethodID(activity, methodName, sig);
	const jboolean jflg = (jboolean) env->CallStaticBooleanMethod(activity, mID);
	return jflg == JNI_TRUE;
}

void UtilJNI::connectServer(const char *url, const char *fileName,
							function<void(CallbackType, const char *)> func) {
	this->callJNIVoid("connectServer", url, fileName);
	callback = func;// Callback
}

void UtilJNI::callbackClient(CallbackType type, const char *fileName) {
	if (!callback) return;
	callback(type, fileName);
}

string UtilJNI::getVersionCode() {
	return this->callJNIStr("getVersionCode");
}

string UtilJNI::getVersionName() {
	return this->callJNIStr("getVersionName");
}

string UtilJNI::getFilePath() {
	return this->callJNIStr("getFilePath");
}

bool UtilJNI::getDebugFlg() {
	return this->callJNIBool("getDebugFlg");
}