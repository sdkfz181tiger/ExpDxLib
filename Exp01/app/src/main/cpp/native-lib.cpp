#include "DxLib.h"

int android_main(void) {

	const int D_WIDTH = 1080;
	const int D_HEIGHT = 1920;
	const int C_DEPTH = 16;
	SetGraphMode(D_WIDTH, D_HEIGHT, C_DEPTH);

	// Initialize
	if (DxLib_Init() == -1) return -1;

	printfDx("Hello DxLib!\n");

	int C_WHITE = GetColor(255, 255, 255);
	int C_RED = GetColor(255, 0, 0);
	int C_GREEN = GetColor(0, 255, 0);
	int C_BLUE = GetColor(0, 0, 255);

	DrawLine(0, 0, D_WIDTH, D_HEIGHT, C_GREEN);
	DrawLine(D_WIDTH, 0, 0, D_HEIGHT, C_GREEN);

	WaitKey();

	DxLib_End();

	return 0;
}