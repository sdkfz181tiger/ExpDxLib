#include <jni.h>
#include "GameManager.h"

int android_main(void) {

	// Initialize
	if (DxLib_Init() == -1) return -1;

	// Display: Pixel2: 1080x1920
	const int dWidth = UtilDx::getInstance()->getDispWidth();
	const int dHeight = UtilDx::getInstance()->getDispHeight();
	const int dDepth = UtilDx::getInstance()->getDispDepth();

	// GameManager
	GameManager *gameManager = new GameManager(dWidth, dHeight, dDepth);

	const int fps = 50;
	const int wait = 1000 / fps;

	int now = GetNowCount();

	// MainLoop
	while (ProcessMessage() == 0 && !UtilDx::getInstance()->getQuitFlg()) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		// Delay
		int passed = GetNowCount() - now;
		float delay = float(passed) * 0.001f;
		now = GetNowCount();

		// Touch, Update
		gameManager->touchInput();
		gameManager->update(delay);

		// Wait, Flip
		if (passed < wait) WaitTimer(wait - passed);
		ScreenFlip();
	}

	// Delete
	DX_SAFE_DELETE(gameManager);

	InitSoundMem();
	InitGraph();
	DxLib_End();
	return 0;
}

//==========
// JNI

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