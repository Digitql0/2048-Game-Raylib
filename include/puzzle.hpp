#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <raylib.h>
#include <vector>
class puzzle {
	
public:
	puzzle(unsigned int dimensions);
	void render(float w, float h);
	void makeMove();
	bool gameOver();
private:
	bool game_over;	
	unsigned int dim;
	std::vector<std::vector<unsigned int>> grid;
	unsigned int highestNumber;
	void moveRow(std::vector<unsigned int>& row);
	void transposeGrid();
	void rotateClockwise();
	void rotateCounterClockwise();
	void init(unsigned int dimensions);
};

#endif
