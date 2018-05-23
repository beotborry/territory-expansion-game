#pragma once
#include <iostream>
#include "GL/glut.h"
#include "area.h"


class Zombie {
public:
	Zombie() {
		static int t = 0;
		this->Zombie_ID = t;
		srand(time(NULL) + t++);
		int x = (rand() % 100) * 5;
		int y = (rand() % 100) * 5;
		while (occupied[x][y] == 1 && (x == 0) || (y == 500)) {
			int x = (rand() % 100) * 5;
			int y = (rand() % 100) * 5;
		}
		pos_x = x;
		pos_y = y;
	}
	Zombie(const Zombie& z) {
      this->pos_x = z.pos_x;
      this->pos_y = z.pos_y;
      this->size = z.size;
   }
	void zombie_die() {
		zombie_killed++;
		static int t = 0;
		this->Zombie_ID = t;
		srand(time(NULL) + t++);
		int x = (rand() % 100) * 5;
		int y = (rand() % 100) * 5;
		while (occupied[x][y] == 1 && (x == 0) || (y == 500)) {
			int x = (rand() % 100) * 5;
			int y = (rand() % 100) * 5;
		}
		pos_x = x;
		pos_y = y;
	}
   void draw_zombie() {
      glPointSize(size);
      glBegin(GL_POINTS);
      glColor3f(1, 0, 0);
      glVertex2f(pos_x, pos_y);
      glEnd();
   }
   void move() {
		   Zombie_Dir = rand() % 4;
	   if (Zombie_Dir == 0) {
		   if ((pos_y + size / 2) < 505 && occupied[pos_x][pos_y+(size)]!=1) 
			   this->pos_y += 5;
		   else  this->pos_y -= 5;
	   }
	   else if (Zombie_Dir == 1) {
		   if ((pos_y - size / 2) > 0 && occupied[pos_x][pos_y - (size)] != 1)   this->pos_y -= 5;
		   else this->pos_y += 5;
	   }
	   else if (Zombie_Dir == 2) {
		   if ((pos_x - size / 2) > 0 && occupied[pos_x-(size)][pos_y] != 1)   this->pos_x -= 5;
		   else this->pos_x += 5;
	   }
	   else if (Zombie_Dir == 3) {
		   if ((pos_x + size / 2) < WIDTH && occupied[pos_x + (size)][pos_y] != 1)  this->pos_x += 5;
		   else this->pos_x -= 5;
	   }
   }
   int getX() { return pos_x; }
   int getY() { return pos_y; }

private:
   int pos_x;
   int pos_y;
   int size = 10;
   int Zombie_Dir;
   int Zombie_ID;
};
