/*
pixel : (5,5) ~ (595, 500)
*/

#include <iostream>
#include "GL/glut.h"
#include <cstring>
#include <ctime>
#include <random>
#include "Player.h"
#include "Zombie.h"
#include <vector>
#include <string.h>
#include "area.h"
#define WIDTH 600
#define HEIGHT 600
#define EASY 0
#define NORMAL 1
#define HARD 2
#define HELL 3


using namespace std;


int gamemode = 0;
int level = 0; // level variable


Player p;
vector<Zombie> zombies;
vector<Zombie> newzombies;

clock_t start = clock();
clock_t finish;


void floodfill(int x, int y) {
	if (occupied[x][y] == -1) {
		occupied[x][y] = 1;
		floodfill(x + 5, y);
		floodfill(x - 5, y);
		floodfill(x, y + 5);
		floodfill(x, y - 5);
		cout << x << y << endl;
	}
	
}
void fill_area() {
	/*if ((last_key == GLUT_KEY_UP && direction == GLUT_KEY_LEFT)|| last_key == GLUT_KEY_LEFT && direction == GLUT_KEY_UP)
	floodfill(p.getX() + 5, p.getY() - 5
	if ((last_key == GLUT_KEY_DOWN && direction == GLUT_KEY_LEFT) || last_key == GLUT_KEY_LEFT && direction == GLUT_KEY_DOWN)
	floodfill(p.getX() + 5, p.getY() + 5);
	if ((last_key == GLUT_KEY_UP && direction == GLUT_KEY_RIGHT) || last_key == GLUT_KEY_RIGHT && direction == GLUT_KEY_UP)
	floodfill(p.getX() - 5, p.getY() - 5);
	if ((last_key == GLUT_KEY_DOWN && direction == GLUT_KEY_RIGHT) || last_key == GLUT_KEY_RIGHT && direction == GLUT_KEY_DOWN)
	floodfill(p.getX() + 5, p.getY() + 5);*/
}
void draw_string(void * font, const char* str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(str); i++) glutBitmapCharacter(font, str[i]);
}

void draw_area() {
	for (int i = 0; i <= WIDTH; i++)
		for (int j = 0; j <= HEIGHT; j++) {
			if (occupied[i][j] == 1) { //area fill
				glPointSize(10.0f);
				glBegin(GL_QUADS);
				glColor3f(0, 1, 0);
				glVertex2f(i + 2.5, j + 2.5);
				glVertex2f(i + 2.5, j - 2.5);
				glVertex2f(i - 2.5, j - 2.5);
				glVertex2f(i - 2.5, j + 2.5);

				glEnd();
			}
			if(occupied[i][j] == 0) { //line fill
				glPointSize(10.0f);
				glBegin(GL_QUADS);
				glColor3f(1, 1, 0);
				glVertex2f(i + 2.5, j + 2.5);
				glVertex2f(i + 2.5, j - 2.5);
				glVertex2f(i - 2.5, j - 2.5);
				glVertex2f(i - 2.5, j + 2.5);

				glEnd();
			}

		}
}
void processSpecialKeys(int key, int x, int y) {
	if (gamemode == 0) {
		if (key == GLUT_KEY_UP) {
			if (level == EASY)
				level = HELL;
			else level -= 1;
		}
		else if (key == GLUT_KEY_DOWN) {
			level = (level + 1) % 4;
		}
	}

	else if (gamemode == 1) {
			if (direction == GLUT_KEY_UP && key == GLUT_KEY_DOWN){}
			else if (direction == GLUT_KEY_DOWN && key == GLUT_KEY_UP){}
			else if (direction == GLUT_KEY_RIGHT && key == GLUT_KEY_LEFT){}
			else if (direction == GLUT_KEY_LEFT && key == GLUT_KEY_RIGHT){}
			else {
				if (key != direction) {
					last_key[1] = last_key[0];
					last_key[0] = direction;
				}
					direction = key;
				
			}
		//cout << direction << last_key << endl;
	}
}
void processNormalKeys(unsigned char key, int x, int y) {
	if (gamemode == 0) {
		if ((int)key == 13) {
			gamemode = 1;
			switch (level) {
			case EASY:
				for (int i = 0; i < 2; i++)
					zombies.push_back(Zombie());
				break;
			case NORMAL:
				for (int i = 0; i < 4; i++)
					zombies.push_back(Zombie());
				break;
			case HARD:
				for (int i = 0; i < 6; i++)
					zombies.push_back(Zombie());
				break;
			case HELL:
				for (int i = 0; i < 8; i++)
					zombies.push_back(Zombie());
				break;
			}
		}
	}
}
void select_level() {
	glColor3f(1, 1, 1);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "SELECT LEVEL", 200, 550);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "EASY", 200, 450);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "NORMAL", 200, 350);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "HARD", 200, 250);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "HELL", 200, 150);

	switch (level) {
	case EASY:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(180, 456);
		glEnd();
		break;
	case NORMAL:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(180, 356);
		glEnd();
		break;
	case HARD:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(180, 256);
		glEnd();
		break;
	case HELL:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(180, 156);
		glEnd();
		break;

	}
}
void draw_outline() {
	glColor3f(1, 1, 1);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "LIFE", 0, 590);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "LEVEL", 200, 590);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "RATIO", 400, 590);

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(0, 507.5);
	glVertex2f(600, 507.5); // underline
	glVertex2f(195, 600);
	glVertex2f(195, 507.5); // 1st vertical line
	glVertex2f(395, 600);
	glVertex2f(395, 507.5); // 2nd vertical line
	glEnd();

	glColor3f(0, 1, 1);
	glBegin(GL_POINTS);
	glPointSize(5.0f);
	for (int i = 0; i < player_life; i++) {
		glVertex2f(50 * i + 50, 550);
	}
	glEnd();
	switch (level) {
	case EASY:
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "EASY", 220, 550);
		break;
	case NORMAL:
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "NORMAL", 220, 550);
		break;
	case HARD:
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "HARD", 220, 550);
		break;
	case HELL:
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "HELL", 220, 550);
		break;
	}
	char* c = new char[6];
	c[0] = (int)(ratio() / 10);
	c[0] += 48;
	
	c[1] = (int)(ratio() / 1) - 10*(int)(ratio() / 10);
	c[2] = '.';
	c[3] = (int)(ratio() / 0.1) - 10 * (int)(ratio() / 1);
	c[4] = (int)(ratio() / 0.01) - 10 * (int)(ratio() / 0.1);
	c[1] += 48;
	c[3] += 48;
	c[4] += 48;
	c[5] = '%';
	if (c[0]==48) c[0] = ' ';

	glRasterPos2f(420, 550);
	for (int i = 0; i < 6; i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);

}
void player_move() {
	if (direction == GLUT_KEY_UP && (p.getY() + p.getSize() / 2) < 505){
		
		if (occupied[p.getX()][p.getY()] == 1 && occupied[p.getX()][p.getY() + 5] == -1) {
			last_key[0] = 0; last_key[1] = 0;
		}		
		if (occupied[p.getX()][p.getY() + 5] == 0) 	p.player_dead();
		else p.setY(p.getY() + 5);
	}
	else if (direction == GLUT_KEY_DOWN && (p.getY() - p.getSize() / 2) > 0) {
		if (occupied[p.getX()][p.getY()] == 1 && occupied[p.getX()][p.getY() - 5] == -1) {
			last_key[0] = 0; last_key[1] = 0;
		}
		if (occupied[p.getX()][p.getY() - 5] == 0) p.player_dead();
		else p.setY(p.getY() - 5);
	}
	else if (direction == GLUT_KEY_LEFT && (p.getX() - p.getSize() / 2) > 0) {
		if (occupied[p.getX()][p.getY()] == 1 && occupied[p.getX()-5][p.getY()] == -1) {
			last_key[0] = 0; last_key[1] = 0;
		}
		if (occupied[p.getX() - 5][p.getY()] == 0) p.player_dead();
		else p.setX(p.getX() - 5);
	}
	else if (direction == GLUT_KEY_RIGHT && (p.getX() + p.getSize() / 2) < WIDTH) {
		if (occupied[p.getX()][p.getY()] == 1 && occupied[p.getX()+5][p.getY()] == -1) {
			last_key[0] = 0; last_key[1] = 0;
		}
		if (occupied[p.getX()+5][p.getY()] == 0) p.player_dead();
		else p.setX(p.getX() + 5);
	}
}
void idle() {
	if (gamemode == 0) {}
	else if (gamemode == 1) {
		finish = clock();
		if (finish - start > 100 / 5) {
			start = finish;
			player_move();
			if (occupied[p.getX()][p.getY()] == 1)
			{	for (int i = 0; i < 601; i++) 
					for (int j = 0; j < 601; j++)
						if (occupied[i][j] == 0) occupied[i][j] = 1;
			}

			if (occupied[p.getX()][p.getY()] == -1)	occupied[p.getX()][p.getY()] = 0;

			for (auto z : zombies) {
				if (occupied[z.getX()][z.getY()] == 0) p.player_dead();

				if (occupied[z.getX()][z.getY()] == 1) z.zombie_die();
				else z.move();
				
			newzombies.push_back(z);
			}
			zombies.clear();
			for (auto z : newzombies) {
				zombies.push_back(z);
			}
			newzombies.clear();
			//cout << player_life << endl;
		}
	}
}

void renderScene() {
	//Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gamemode == 0) {
		select_level();
	}
	else if (gamemode == 1 && player_life > 0 && ratio() < 99) {
		draw_outline();
		glColor3f(1, 1, 1);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "Zombie(s) killed : ", 200, 490);
		glRasterPos2f(280, 490);
		char c[4];
		c[0] = zombie_killed / 1000 +48;
		c[1] = (zombie_killed % 1000) / 100 +48;
		c[2] = (zombie_killed % 100) / 10 +48;
		c[3] = (zombie_killed % 10) / 1 +48;

		for (int i = 0; i < 4; i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c[i]);
		//cout << p.pos_x << ' ' << p.pos_y << endl;
		draw_area();
		p.drawPlayer();
		for (auto zombie : zombies)
			zombie.draw_zombie();
	}
	else if (gamemode == 1 && (player_life == 0 || ratio() >= 70)) {
		draw_outline();
		if(player_life == 0 ) draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER", 200, 300);
		else draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "WIN", 200, 300);
	}
	glutPostRedisplay();
	glutSwapBuffers();
}




int main(int argc, char** argv) {
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(650, 300);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Territory Expansion Game");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	//register Callback
	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(idle);
	//enter GLUT event processing cycle
	glutMainLoop();

}