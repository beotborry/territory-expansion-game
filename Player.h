#pragma once
#include <iostream>
#include "GL/glut.h"
#include "area.h"

#define WIDTH 600
#define HEIGHT 600

class Player {
public:

	Player() {
		for (int i = 0; i < 605; i++)  // occupied 모두 -1로 초기화
			for (int j = 0; j < 605; j++)
				occupied[i][j] = -1;// -1 : black, 0 :line, 1:white 
		
		pos_x = WIDTH / 2;
		pos_y = HEIGHT / 2;
		for (int i = 250; i <= 350; i += 5) //declare intial area
			for (int j = 250; j < 350; j += 5)
				occupied[i][j] = 1;
	}	
	void drawPlayer() { // player의 현재 위치 draw
		glPointSize(size);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(pos_x, pos_y);
		glEnd();
	}
	//getter&setter
	int getX() {
		return pos_x;
	}
	int getY() {
		return pos_y;
	}
	int getSize() {
		return size;
	}
	void setX(int x) {
		pos_x = x;
	}
	void setY(int y) {
		pos_y = y;
	}
	void player_dead(){ // player 사망
		for (int i = 0; i < 601; i++) 
			for (int j = 0; j < 601; j++)
				if(occupied[i][j] == 0) occupied[i][j] = -1;

		pos_x = WIDTH / 2;
		pos_y = HEIGHT / 2;
		direction = 0;
		player_life--;

	}
private:
	int pos_x;
	int pos_y;
	int size = 10;
};