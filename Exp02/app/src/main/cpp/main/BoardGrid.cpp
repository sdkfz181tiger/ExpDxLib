#include "BoardGrid.h"

BoardGrid *BoardGrid::createBoard(float x, float y,
								  int size, int rows, int cols) {
	// New
	BoardGrid *board = new BoardGrid(x, y);
	if (board && board->init(size, rows, cols)) return board;
	DX_SAFE_DELETE(board);
	return nullptr;
}

BoardGrid::BoardGrid(float x, float y) :
		pos(Vec2(x, y)),
		gSize(0), gRows(0), gCols(0),
		cWhite(GetColor(255, 255, 255)),
		cRed(GetColor(225, 65, 100)),
		cGreen(GetColor(110, 140, 50)),
		cBlue(GetColor(75, 60, 155)) {
	LOGD("Main", "BoardGrid()\n");
}

BoardGrid::~BoardGrid() {
	LOGD("Main", "~BoardGrid()\n");
}

bool BoardGrid::init(int size, int rows, int cols) {
	gSize = size;
	gRows = rows;
	gCols = cols;
	return true;
}

void BoardGrid::update(const float delay) {
	// Draw
	this->draw();
}

void BoardGrid::draw() {

	int width = gSize * gCols;
	int height = gSize * gRows;
	int minX = pos.x - width / 2;
	int minY = pos.y - height / 2;
	int maxX = pos.x + width / 2;
	int maxY = pos.y + height / 2;

	for (int r = 0; r < gRows; r++) {
		for (int c = 0; c < gCols; c++) {
			int i = c + r * gCols;
			if (i % 2 != 0) continue;
			int x = minX + c * gSize;
			int y = minY + r * gSize;
			DrawBox(x, y, x + gSize, y + gSize, cGreen, true);
		}
	}
	/*
	for (int r = 1; r < gRows; r++)
		DrawLine(minX, minY + r * gSize, maxX, minY + r * gSize, cWhite);
	for (int c = 1; c < gCols; c++)
		DrawLine(minX + c * gSize, minY, minX + c * gSize, maxY, cWhite);
	DrawBox(minX, minY, maxX, maxY, cWhite, false);
	 */
}