#include "puzzle.hpp"
#include <algorithm>
#include <raylib.h>
#include <string>

puzzle::puzzle(unsigned int dimensions) : dim(dimensions) {	
	init(dimensions);
}

void puzzle::init(unsigned int dimensions) {
	for (int i = 0; i < dimensions; ++i) {
		std::vector<unsigned int> new_buffer;
		for (int j = 0; j < dimensions; ++j) {
			new_buffer.push_back(0);
		}
		grid.push_back(new_buffer);
	}

	for (int i = 0; i < 2; i++) {
		int min;
		int max;
		int x;
		int y;
		do {
			min = 0;
			max = dim - 1;
			x = min + rand() % (max - min + 1);
			y = min + rand() % (max - min + 1);
		} while (grid[y][x] != 0);

		grid[y][x] = 2;
	}

	highestNumber = 2;
}

bool puzzle::gameOver(){
	return game_over;
}

void puzzle::makeMove() {
	std::vector<std::vector<unsigned int>> oldgrid = grid;

	if (IsKeyPressed(KEY_W)) {
    rotateCounterClockwise();
    for (auto& row : grid) {
        moveRow(row);
    }
    rotateClockwise();
} 

if (IsKeyPressed(KEY_S)) {
    rotateClockwise();
    for (auto& row : grid) {
        moveRow(row);
    }
    rotateCounterClockwise();
}

	if (IsKeyPressed(KEY_A)) {
		for (auto& row : grid) {
			moveRow(row);
		}
	}

	if (IsKeyPressed(KEY_D)) {
		for (auto& row : grid) {
			std::reverse(row.begin(), row.end());
			moveRow(row);
			std::reverse(row.begin(), row.end());
		}
	}

	bool difference = false;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (oldgrid[i][j] != grid[i][j]) {
				difference = true;
			}
		}
	}

	if (difference) {
		int min;
		int max;
		int x;
		int y;
		do {
			min = 0;
			max = dim - 1;
			x = min + rand() % (max - min + 1);
			y = min + rand() % (max - min + 1);
		} while (grid[y][x] != 0);

		min = 0;
		max = 100;
		int percentage = min + rand() % (max - min + 1);

		if (percentage <= 90) {
			grid[y][x] = 2;
		} else {
			grid[y][x] = 4;
		}
	}

	if (IsKeyPressed(KEY_SPACE)) {
		grid.clear();
		init(dim);
	}
}

void puzzle::render(float w, float h) {
	int fontSize = 100;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			DrawRectangleLines(j * w, i * h, w, h, BLACK);
			unsigned char a = (unsigned char)( (float)grid[i][j] / (float)highestNumber * (255/4*3) + 255/4);
			if (grid[i][j] == 0) a = 0;
			Color myColor = {255, 255 / 2, 0, a};
			DrawRectangle(j * w, i * h, w, h, myColor);
			std::string str = std::to_string(grid[i][j]);
			const char* text = str.c_str();
			DrawText(text, j * w + w / 2 - (MeasureText(text, fontSize) / 2), i * h + h / 2 - fontSize / 2, fontSize, RED);
		}
	}
}

void puzzle::moveRow(std::vector<unsigned int>& row) {
	row.erase(std::remove(row.begin(), row.end(), 0), row.end());

	for (int i = 0; i + 1 < row.size(); i++) {
		if (row[i] == row[i + 1]) {
			row[i] *= 2;
			if (row[i] > highestNumber) {
				highestNumber = row[i];
			}
			row[i + 1] = 0;
		}
	}

	row.erase(std::remove(row.begin(), row.end(), 0), row.end());
	while (row.size() < dim) row.push_back(0);
}

void puzzle::transposeGrid() {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = i + 1; j < grid[i].size(); j++) {
			std::swap(grid[i][j], grid[j][i]);
		}
	}
}

void puzzle::rotateClockwise() {
	transposeGrid(); 
	for (auto& row : grid)
		std::reverse(row.begin(), row.end()); 
}

void puzzle::rotateCounterClockwise() {
	for (auto& row : grid)
		std::reverse(row.begin(), row.end());
	transposeGrid();
}
