#pragma once

#define WIDTH 200
#define HEIGHT 200
int occupied[WIDTH+1][HEIGHT+1]; // -1 : black, 0 :line, 1:green, 2:flood fill called
int time_constant = 0; // when use srand()
int player_life = 3; // life
int zombie_killed = 0;
int direction; // current direction
int object_size = 10;

float ratio() { // area / total(%)
	int r = 0;
	for (int i = 1; i < WIDTH; i ++) {
		for (int j = 1; j < HEIGHT; j++)
			if (occupied[i][j] == 1) r++; // -1 : black, 0 :line, 1:white 
	}
	return (float) r / (WIDTH-1) / (HEIGHT+1) / 99 * 10000;
}