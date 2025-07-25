#include <iostream>
#include <raylib.h>
#include "puzzle.hpp"

const int width = 500;
const int height = 500;
const int dim = 4;
const float tileHeight = (float)height / dim;
const float tileWidth = (float)width / dim;

puzzle Game(dim);

int main() {

	InitWindow(width, height, "Hi");
	SetTargetFPS(60);

  	std::cout << rand() % 20 << std::endl;

	while (!WindowShouldClose()) {

		if (!Game.gameOver()) {
			Game.makeMove();
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		Game.render(tileWidth, tileHeight);
		EndDrawing();
	}

	std::cout << "Hello World" << std::endl;
}
