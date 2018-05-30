#pragma once
#include <iostream>
#include "GL/glut.h"
#include "area.h"

//#define WIDTH 600
//#define HEIGHT 600

class Player {
public:

	Player() {
		for (int i = 0; i < WIDTH + 1; i++) { // initialize occupied as -1
			for (int j = 0; j < HEIGHT + 1; j++)
				occupied[i][j] = -1;// -1 : black, 0 : line, 1 : white 
		}
		pos_x = WIDTH / 2;
		pos_y = HEIGHT / 2;
		for (int i = WIDTH/2 - WIDTH/10; i <= WIDTH / 2 + WIDTH / 10; i++) // declare intial area
			for (int j = HEIGHT / 2 -   HEIGHT / 10; j < HEIGHT / 2 + HEIGHT / 10; j ++)
				occupied[i][j] = 1;
	}	
	void drawPlayer() { // draw player current position
		glPointSize(object_size);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(pos_x, pos_y);
		glEnd();
	}
	int getX() {
		return pos_x;
	}
	int getY() {
		return pos_y;
	}
	void setX(int x) {
		pos_x = x;
	}
	void setY(int y) {
		pos_y = y;
	}
	void player_dead() {
		for (int i = 0; i < WIDTH + 1; i++) 
			for (int j = 0; j < HEIGHT + 1; j++)
				if(occupied[i][j] == 0) occupied[i][j] = -1;

		pos_x = WIDTH / 2;
		pos_y = HEIGHT / 2;
		direction = 0;
		player_life--;
	}
private:
	int pos_x;
	int pos_y;
};