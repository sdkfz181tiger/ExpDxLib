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

	const int cX = D_WIDTH / 2;
	const int cY = D_HEIGHT / 2;
	const int fps = 16;
	const int wait = 1000 / fps;
	int now = GetNowCount();

	// Graph
	const int rGra = LoadGraph("images/y_reimu_x1.png");
	int rGraW, rGraH;
	GetGraphSize(rGra, &rGraW, &rGraH);
	DrawExtendGraph(cX, cY, cX + rGraW * 5, cY + rGraH * 5, rGra, true);

	// MainLoop
	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		// Label
		UtilLabel::getInstance()->drawStr("HELLO DXLIB!!", cX, cY,
		                                  5, UtilAlign::CENTER);

		// Delay
		int passed = GetNowCount() - now;
		float delay = float(passed) / float(wait);
		UtilDebug::getInstance()->drawGrid();
		UtilDebug::getInstance()->drawFPS(delay);
		now = GetNowCount();
		WaitTimer(wait);

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

//==========
// JNI

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnCreate(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onCreate!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnStart(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onStart!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnResume(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onResume!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnPause(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onPause!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnStop(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onStop!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnDestroy(
		JNIEnv *env, jclass clz) {
	LOGD("JNI", "onDestroy!!");
	// Destroy all utilities
	UtilDebug::getInstance()->destroyInstance();
	UtilLabel::getInstance()->destroyInstance();
	UtilMath::getInstance()->destroyInstance();
}