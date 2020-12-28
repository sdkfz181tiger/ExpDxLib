#include <jni.h>
#include "GameManager.h"

int android_main(void) {

	// Initialize
	if (DxLib_Init() == -1) return -1;

	// Display: Pixel2: 1080x1920
	const int D_WIDTH = 1080;
	const int D_HEIGHT = 1920;
	const int C_DEPTH = 16;

	// GameManager
	GameManager *gameManager = new GameManager(D_WIDTH, D_HEIGHT, C_DEPTH);

	const int fps = 32;
	const int wait = 1000 / fps;
	int now = GetNowCount();

	// MainLoop
	while (ProcessMessage() == 0 && !UtilDx::getInstance()->getQuitFlg()) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		// Delay
		int passed = GetNowCount() - now;
		float delay = floor((float(passed) / float(wait)) * 100.0f) * 0.01f;
		now = GetNowCount();

		// Touch, Update
		gameManager->touchInput();
		gameManager->update(delay);

		// Wait, Flip
		WaitTimer(wait);
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