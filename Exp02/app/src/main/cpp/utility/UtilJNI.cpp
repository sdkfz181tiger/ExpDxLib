#include "UtilJNI.h"

// Singleton Object
static UtilJNI *selfUtilJNI = nullptr;

// Java Virtual machine
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

static void detachThread(void *value) {
	/* The thread is being destroyed, detach it from the Java VM
	 * and set the mThreadKey value to NULL as required */
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

jint Android_JNI_SetupThread(void) {
	if (Android_JNI_GetEnv() != nullptr) return JNI_OK;
	return JNI_ERR;
}

UtilJNI::UtilJNI() {
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
	//if (Android_JNI_SetupThread() != JNI_OK) return JNI_ERR;
	if (this->registerMethods(env) != JNI_OK) return JNI_ERR;
	return JNI_VERSION_1_6;
}

jint UtilJNI::registerMethods(JNIEnv *env) {
	LOGD("JNI", "UtilJNI::registerMethods(%p), %ld\n", javaVM, pthread_self());
	jclass cls = env->FindClass("com/ozateck/chickader/MainActivity");
	if (cls == nullptr) return JNI_ERR;
	const JNINativeMethod methods[] = {
			{"nativeOnCreate",  "()V", reinterpret_cast<void *>(nativeOnCreate)},
			{"nativeOnStart",   "()V", reinterpret_cast<void *>(nativeOnStart)},
			{"nativeOnResume",  "()V", reinterpret_cast<void *>(nativeOnResume)},
			{"nativeOnPause",   "()V", reinterpret_cast<void *>(nativeOnPause)},
			{"nativeOnStop",    "()V", reinterpret_cast<void *>(nativeOnStop)},
			{"nativeOnDestroy", "()V", reinterpret_cast<void *>(nativeOnDestroy)}
	};
	int total = sizeof(methods) / sizeof(JNINativeMethod);
	if (env->RegisterNatives(cls, methods, total) != JNI_OK) return JNI_ERR;
	activity = (jclass) env->NewGlobalRef(cls);// Activity
	return JNI_OK;
}

string UtilJNI::test() {
	LOGD("JNI", "UtilJNI::test(%p), %ld\n", javaVM, pthread_self());
	JNIEnv *env = Android_JNI_GetEnv();
	if (env == nullptr) return "";
	//Android_JNI_SetupThread();

	// Static
	jmethodID mID1 = env->GetStaticMethodID(activity,
											"sayHello", "()V");
	env->CallStaticVoidMethod(activity, mID1);

	jmethodID mID2 = env->GetStaticMethodID(activity,
											"sayGood", "()V");
	env->CallStaticVoidMethod(activity, mID2);

	jmethodID mID3 = env->GetStaticMethodID(activity,
											"sayNice", "()V");
	env->CallStaticVoidMethod(activity, mID3);

	jmethodID mID4 = env->GetStaticMethodID(activity,
											"sayYahoo", "()Ljava/lang/String;");
	const jstring jstr = (jstring) env->CallStaticObjectMethod(activity, mID4);
	const char *cstr = env->GetStringUTFChars(jstr, 0);
	const string result = cstr;
	env->ReleaseStringUTFChars(jstr, cstr);

	LOGD("JNI", "Hello, someone there? :%s\n", result.c_str());
	return result;
}