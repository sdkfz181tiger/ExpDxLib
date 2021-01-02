#include <jni.h>
#include "GameManager.h"

int android_main(void) {

	// Initialize
	if (DxLib_Init() == -1) return -1;

	// Display: Pixel2: 1080x1920
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
		//WaitTimer(20);

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