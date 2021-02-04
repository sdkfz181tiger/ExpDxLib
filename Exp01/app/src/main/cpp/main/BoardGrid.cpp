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
		center(Vec2(x, y)),
		gSize(0), gRows(0), gCols(0),
		minX(0), maxX(0), minY(0), maxY(0),
		cBlack(GetColor(0, 0, 0)),
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

	int width = size * cols;
	int height = size * rows;
	minX = center.x - width / 2;
	maxX = minX + width;
	minY = center.y - height / 2;
	maxY = minY + height;

	for (int r = 0; r < gRows; r++) {
		for (int c = 0; c < gCols; c++) {
			int x = minX + c * gSize + gSize / 2;
			int y = minY + r * gSize + gSize / 2;
			positions.emplace_back(x, y);
		}
	}

	return true;
}

void BoardGrid::update(const float delay) {
	// Tile
	int half = gSize / 2;
	for (int i = 0; i < positions.size(); i++) {
		Vec2 &pos = positions.at(i);
		DrawBox(pos.x, pos.y,
				pos.x + 4, pos.y + 4,
				cWhite, true);
	}
}

Vec2 &BoardGrid::getPos(int r, int c) {
	return positions.at(r * gCols + c);
}

Vec2 &BoardGrid::getRdmPos() {
	int i = UtilMath::getInstance()->getRandom(0, gRows * gCols - 1);
	return positions.at(i);
}