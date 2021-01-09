#include "UtilJNI.h"

// Singleton Object
static UtilJNI *selfUtilJNI = nullptr;

// Java Virtual machine, JNI
static JavaVM javaVM = nullptr;
static pthread_key_t threadKey;

void nativeOnCreate(JNIEnv *env, jobject thiz) {
	LOGD("JNI", "onCreate!?");
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
	LOGD("JNI", "UtilJNI::init()\n");
	javaVM = vm;// Java virtual machine
	JNIEnv *env;
	if ((*javaVM)->GetEnv(javaVM, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		LOGE("Failed to get the environment using GetEnv()");
		return -1;
	}


	javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
	if (env == nullptr) return JNI_ERR;
	if (this->registerMethods(env) != JNI_OK) return JNI_ERR;
	return JNI_VERSION_1_6;
}

jint UtilJNI::registerMethods(JNIEnv *env) {
	LOGD("JNI", "UtilJNI::registerMethods()\n");
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
	return JNI_OK;
}

void UtilJNI::test() {
	LOGD("JNI", "UtilJNI::test(%p), %ld\n", javaVM, pthread_self());
	if (javaVM == nullptr) return;



	LOGD("JNI", "Hello, someone there?\n");
}