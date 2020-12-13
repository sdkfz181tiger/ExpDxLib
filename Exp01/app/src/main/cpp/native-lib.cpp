#include "DxLib.h"

#include "utility/UtilMath.h"

int android_main(void) {

	const int C_WHITE = GetColor(255, 255, 255);
	const int C_BLACK = GetColor(0, 0, 0);
	const int C_RED   = GetColor(255, 0, 0);
	const int C_GREEN = GetColor(0, 255, 0);
	const int C_BLUE  = GetColor(0, 0, 255);

	// Display: Pixel2: 1080x1920
	const int D_WIDTH  = 1080;// Display width
	const int D_HEIGHT = 1920;// Display height
	const int C_DEPTH  = 16;  // Color depth 16 or 32
	const int FPS = 1;
	SetGraphMode(D_WIDTH, D_HEIGHT, C_DEPTH);
	SetOutApplicationLogValidFlag(true);

	// Initialize
	if (DxLib_Init() == -1) return -1;

	// Test
	UtilMath::getInstance();

	// MainLoop
	while (ProcessMessage() == 0){
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		DrawLine(0, 0, D_WIDTH, D_HEIGHT, C_GREEN);
		DrawLine(D_WIDTH, 0, 0, D_HEIGHT, C_GREEN);

		ScreenFlip();
		WaitTimer(1000/FPS);
	}

	DxLib_End();
	return 0;
}