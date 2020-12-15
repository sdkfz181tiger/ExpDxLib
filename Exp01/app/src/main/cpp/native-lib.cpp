#include <jni.h>
#include "utility/Utility.h"

int android_main(void) {

	// Display: Pixel2: 1080x1920
	const int D_WIDTH = 1080;     // Display width
	const int D_HEIGHT = 1920;     // Display height
	const int C_DEPTH = 16;       // Color depth 16 or 32
	const int W_TIME = 1000 / 16;// FPS
	SetGraphMode(D_WIDTH, D_HEIGHT, C_DEPTH);
	SetOutApplicationLogValidFlag(true);

	// Initialize
	if (DxLib_Init() == -1) return -1;

	const int cX = D_WIDTH / 2;
	const int cY = D_HEIGHT / 2;
	const int cWhite = GetColor(255, 255, 255);

	// Graph
	const int rGra = LoadGraph("images/y_reimu_x1.png");
	int rGraW, rGraH;
	GetGraphSize(rGra, &rGraW, &rGraH);

	// MainLoop
	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		// Debug
		UtilDebug::getInstance()->drawGrid();
		UtilDebug::getInstance()->drawFPS();

		// Graph
		DrawGraph(cX, cY, rGra, true);
		DrawExtendGraph(cX, cY, cX + rGraW * 5, cY + rGraH * 5, rGra, true);

		// Label
		UtilLabel::getInstance()->drawStr("HELLO DXLIB!!", cX, 100, 5, UtilLabelAlign::CENTER);

		ScreenFlip();
		WaitTimer(W_TIME);
	}

	DxLib_End();
	return 0;
}

//==========
// JNI

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnCreate(
		JNIEnv *env, jclass clz) {
	LOGD("JNI:%s", "onCreate!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnStart(
		JNIEnv *env, jclass clz) {
	LOGD("JNI:%s", "onStart!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnResume(
		JNIEnv *env, jclass clz) {
	LOGD("JNI:%s", "onResume!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnPause(
		JNIEnv *env, jclass clz) {
	LOGD("JNI:%s", "onPause!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnStop(
		JNIEnv *env, jclass clz) {
	LOGD("JNI:%s", "onStop!!");
}

extern "C" JNIEXPORT void JNICALL
Java_com_ozateck_mydxlib01_MainActivity_nativeOnDestroy(
		JNIEnv *env, jclass clz) {
	LOGD("JNI:%s", "onDestroy!!");
}