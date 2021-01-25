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

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	LOGD("JNI", "JNI_OnLoad!!");
	return UtilJNI::getInstance()->init(vm);
}