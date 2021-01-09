#include "UtilJNI.h"

// Singleton Object
static UtilJNI *selfUtilJNI = nullptr;

// Java Virtual machine, JNI
static JavaVM *javaVM = nullptr;

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
	LOGD("JNI", "UtilJNI::init(%p), %ld\n", vm, pthread_self());
	javaVM = vm;// Java virtual machine
	JNIEnv *env;
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

	JNIEnv *env;
	if (javaVM->AttachCurrentThread(&env, NULL) != JNI_OK) {
		LOGD("JNI", "Why!!\n");
		return;
	}

	jclass classLoader = env->FindClass("java/lang/ClassLoader");
	if (classLoader == 0) {
		LOGD("JNI", "ClassLoader クラスを取得できませんでした。\n");
		return;
	}

	jmethodID loadClass = env->GetMethodID(classLoader, "loadClass",
										   "(Ljava/lang/String;)Ljava/lang/Class;");
	if (loadClass == 0) {
		LOGD("JNI", "loadClass 関数を取得できませんでした。\n");
	}

	jclass activityClass = env->FindClass("android/app/NativeActivity");
	jmethodID getClassLoader = env->GetMethodID(activityClass, "getClassLoader",
												"()Ljava/lang/ClassLoader;");
	if (getClassLoader == 0) {
		LOGD("JNI", "getClassLoader 関数を取得できませんでした。\n");
	}

//	jobject classLoaderInstance = env->CallObjectMethod(thiz, getClassLoader);
//	if (classLoaderInstance == 0) {
//		LOGD("JNI", "classLoaderInstance 関数を取得できませんでした。\n");
//	}

	LOGD("JNI", "Hello, someone there?\n");

	//javaVM->DetachCurrentThread();

	/*
	JNIEnv *env;
	jint ret = javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
	switch (ret){
		case (JNI_OK):
			LOGD("JNI", "JNI_OK!!\n");
			break;
		case (JNI_EDETACHED):
			LOGD("JNI", "JNI_EDETACHED!!\n");
			break;
		default:
			LOGD("JNI", "Other!!\n");
			return;
	}

	if(javaVM->AttachCurrentThread(&env, NULL) != JNI_OK){
		LOGD("JNI", "Why!!\n");
		return;
	}

	jclass cls = env->GetObjectClass(activity);
	jmethodID cns = env->GetMethodID(cls, "<init>", "()V");
	if (cns == nullptr) {
		LOGD("JNI", "Could not find constructor!!");
		return;
	}
	jobject obj = env->NewObject(cls, cns);
	jmethodID mid = env->GetMethodID(cls, "sayHello", "()V");
//	env->CallVoidMethod(obj, mid);

	LOGD("JNI", "Someone!!\n");

	javaVM->DetachCurrentThread();
	 */

	/*
	JNIEnv *env = nullptr;
	jint ret = javaVM->GetEnv((void **) &env, JNI_VERSION_1_6);
	switch (ret) {
		case JNI_OK :
			LOGD("Util", "JNI_OK\n");
			break;
		case JNI_EDETACHED:
			LOGD("Util", "JNI_EDETACHED\n");
			if (javaVM->AttachCurrentThread(&env, nullptr) < 0) {
				LOGD("Util", "Failed to get the environment using AttachCurrentThread()");
			} else {
				// Success : Attached and obtained JNIEnv
				LOGD("Util", "Success?\n");

				pthread_setspecific(g_key, env);

				jclass cls = env->FindClass("com/ozateck/chickader/MainActivity");
				if (cls == nullptr) {
					LOGD("Util", "Could not find class!!");
					return;
				}

				LOGD("Util", "Hello, someone there?\n");
			}
			break;
		default:
			LOGD("Util", "JNI_DEFAULT\n");
	}
	*/

	/*
	JNIEnv *env;
	javaVM->AttachCurrentThread(&env, nullptr);

	// Find class
	jclass cls = env->FindClass("com/ozateck/chickader/MainActivity");
	if (cls == nullptr) {
		LOGD("JNI", "Could not find class!!");
		//return;
	}

	javaVM->DetachCurrentThread();

	LOGD("Util", "Hello, someone there?\n");
	 */

	/*
	// Find constructor
	jmethodID cns = jniEnv->GetMethodID(cls, "<init>", "()V");
	if (cns == nullptr) {
		LOGD("JNI", "Could not find constructor!!");
		return;
	}
	jobject obj = jniEnv->NewObject(cls, cns);
	// Find method
	LOGD("JNI", "Well done!!");
	jmethodID mid = jniEnv->GetMethodID(cls, "sayHello", "()V");
	jniEnv->CallVoidMethod(obj, mid);
	 */
}