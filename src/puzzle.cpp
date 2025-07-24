#include "puzzle.hpp"
#include <cstdlib>
#include <raylib.h>

puzzle::puzzle(unsigned int dimensions) : dim(dimensions) {	
	for (int i = 0; i < dimensions; ++i) {
		std::vector<unsigned int> new_buffer;
		for (int j = 0; j < dimensions; ++j) {
			new_buffer.push_back(0);
		}
		grid.push_back(new_buffer);
	}

	grid[2][1] = 2;
	grid[0][0] = 2;
}

bool puzzle::gameOver(){
	return game_over;
}

void puzzle::makeMove() {
	bool success = false;

	if (IsKeyPressed(KEY_A)) {

		//Merge all Cells
		for (int i = 0; i < grid.size(); ++i) {
			unsigned int A;
			unsigned int B;
			for (int j = 0; j < grid[i].size(); ++j) {
				if (A == 0) {
					A = grid[j][i];
				} else {
					B = grid[j][i];

					if (A == B) {
						grid[j][i-1] = 0;
						grid[j][i] = grid[j][i] * 2;
						A = 0;
						B = 0;
						success = true;
					}

				}
			}

			//Compact Cells
			for (int j = grid[i].size(); j >= 0; ++j) {
				if (grid[j][i] != 0) {
					for (int a = 0; a < grid[i].size(); ++a) {
						if (a >= j) {
							break;
						} else if (grid[a][i] == 0) {
							grid[a][i] = grid[j][i];
							grid[j][i] = 0;
							break;
						}
					}
				}
			}
		}

	}

	if (success == true) {

		//TODO: Board Filled ?
		//TODO: 2048 reached ?

		unsigned int i;
		unsigned int j;
		unsigned int v;
		do {
			float d = rand() % 1;
			if (d <= 0.9) {
				v = 2;
			}

			i = rand() % grid.size();
			j = rand() % grid[i].size();
		} while (grid[j][i] != 0);
		grid[j][i] = v;
	}
}
