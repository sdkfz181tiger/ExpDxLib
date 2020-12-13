#include "utility/Utility.h"

int android_main(void) {

	// Display: Pixel2: 1080x1920
	const int D_WIDTH  = 1080;     // Display width
	const int D_HEIGHT = 1920;     // Display height
	const int C_DEPTH  = 16;       // Color depth 16 or 32
	const int W_TIME   = 1000 / 60;// FPS
	SetGraphMode(D_WIDTH, D_HEIGHT, C_DEPTH);
	SetOutApplicationLogValidFlag(true);

	// Initialize
	if (DxLib_Init() == -1) return -1;

	// MainLoop
	while (ProcessMessage() == 0){
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		UtilDebug::getInstance()->drawGrid();
		UtilDebug::getInstance()->drawFPS();

		ScreenFlip();
		WaitTimer(W_TIME);
	}

	DxLib_End();
	return 0;
}