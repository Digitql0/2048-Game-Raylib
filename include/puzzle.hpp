#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <raylib.h>
#include <vector>
class puzzle {
	
public:
	puzzle(unsigned int dimensions);
	void makeMove();
	void render(float w, float h);
	bool gameOver();
private:
	bool game_over;	
	unsigned int dim;
	std::vector<std::vector<unsigned int>> grid;
};

#endif
