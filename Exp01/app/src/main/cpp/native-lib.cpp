#include "utility/Utility.h"

int android_main(void) {

	// Display: Pixel2: 1080x1920
	const int D_WIDTH  = 1080;     // Display width
	const int D_HEIGHT = 1920;     // Display height
	const int C_DEPTH  = 16;       // Color depth 16 or 32
	const int W_TIME   = 1000 / 2; // FPS
	SetGraphMode(D_WIDTH, D_HEIGHT, C_DEPTH);
	SetOutApplicationLogValidFlag(true);

	// Initialize
	if (DxLib_Init() == -1) return -1;

	int fontHandle = LoadFontDataToHandle("assets/AtariClassic.ttf", 0);
	LOGD("fontHandle:%d", fontHandle);

	const int cX = D_WIDTH / 2;
	const int cY = D_HEIGHT / 2;
	const int cWhite = GetColor(255, 255, 255);

	// Graph
	const int rGra = LoadGraph("images/y_reimu_x1.png");
	int rGraW, rGraH;
	GetGraphSize(rGra, &rGraW, &rGraH);
	LOGD("W, H:%d, %d", rGraW, rGraH);

	// MainLoop
	while (ProcessMessage() == 0){
		ClearDrawScreen();
		SetDrawScreen(DX_SCREEN_BACK);

		// Test
		DrawStringToHandle(100, 100, "HELLO!!", cWhite, fontHandle);
		UtilDebug::getInstance()->drawGrid();
		UtilDebug::getInstance()->drawFPS();

		// Graph
		DrawGraph(cX, cY, rGra, true);
		DrawExtendGraph(cX, cY, cX+rGraW*10, cY+rGraH*10, rGra, true);

		ScreenFlip();
		WaitTimer(W_TIME);
	}

	DxLib_End();
	return 0;
}