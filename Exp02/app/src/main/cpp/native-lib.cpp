#include <jni.h>
#include "GameManager.h"

int android_main(void) {

	// Initialize
	if (DxLib_Init() == -1) return -1;

	// Display
	const int dWidth = UtilDx::getInstance()->getDispWidth();
	const int dHeight = UtilDx::getInstance()->getDispHeight();
	const int dDepth = UtilDx::getInstance()->getDispDepth();
	const int fps = UtilDx::getInstance()->getFPS();
	const int wait = 1000 / fps;
	float delay = 0.0f;

	// GameManager
	GameManager *gameManager = new GameManager(dWidth, dHeight, dDepth);

	// MainLoop
	while (ProcessMessage() == 0 && !UtilDx::getInstance()->getQuitFlg()) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		int now = GetNowCount();

		gameManager->touchInput();// Touch
		gameManager->update(delay);// Update

		int passed = GetNowCount() - now;
		if (wait < passed) {
			delay = float(passed) * 0.001f;
			WaitTimer(wait);
		} else {
			delay = float(wait - passed) * 0.001f;
			WaitTimer(wait - passed);
		}
		ScreenFlip();// Flip
	}

	// Delete
	DX_SAFE_DELETE(gameManager);

	InitSoundMem();
	InitGraph();
	DxLib_End();
	return 0;
}

//==========
// JNI(Java -> C++)

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_chickader_MainActivity_nativeOnCreate(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onCreate!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_chickader_MainActivity_nativeOnStart(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onStart!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_chickader_MainActivity_nativeOnResume(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onResume!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_chickader_MainActivity_nativeOnPause(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onPause!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_chickader_MainActivity_nativeOnStop(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onStop!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_chickader_MainActivity_nativeOnDestroy(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onDestroy!!");
}

void findClass(JNIEnv *env) {
	// Class
	jclass cls = env->FindClass("com/ozateck/chickader/MainActivity");
	if (cls == 0) {
		LOGD("JNI", "Could not find class!!");
		return;
	}
	jmethodID cns = env->GetMethodID(cls, "<init>", "()V");
	if (cns == nullptr) {
		LOGD("JNI", "Could not find init method!!");
		return;
	}
	LOGD("JNI", "Well done!!");
	jobject obj = env->NewObject(cls, cns);
	jmethodID mid = env->GetMethodID(cls, "sayHello", "()V");
	env->CallVoidMethod(obj, mid);
}

JavaVM *javaVM = nullptr;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	LOGD("JNI", "JNI_OnLoad!!");
	javaVM = vm;
	JNIEnv *env = nullptr;
	jint ret = vm->GetEnv((void **) &env, JNI_VERSION_1_4);
	switch (ret) {
		case JNI_OK :
			LOGD("JNI", "JNI:Success!!");
			findClass(env);// Find class
			break;
		case JNI_ERR:
			LOGE("JNI", "JNI:Unknown error!!");
			break;
		default:
			LOGE("JNI", "JNI:Other error!!");
			break;
	}
	return JNI_VERSION_1_4;
}