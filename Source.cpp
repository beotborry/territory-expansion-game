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
#include "Area.h"

//#define WIDTH 600
//#define HEIGHT 500
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
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) return;
	else if (occupied[x][y] == -1) {
		occupied[x][y] = 2;
	}
	else return;

	floodfill(x + 1, y);
	floodfill(x - 1, y);
	floodfill(x, y + 1);
	floodfill(x, y - 1);
}


void fill_area() {
	floodfill(0, 0);
}

void draw_string(void * font, const char* str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(str); i++) glutBitmapCharacter(font, str[i]);
}

void draw_area() {
	for (int i = 0; i <= WIDTH; i++)
		for (int j = 0; j <= HEIGHT; j++) {
			if (occupied[i][j] == 1) { // fill area
				glBegin(GL_QUADS);
				glColor3f(0, 1, 0);
				glVertex2f(i + 0.5, j + 0.5);
				glVertex2f(i + 0.5, j - 0.5);
				glVertex2f(i - 0.5, j - 0.5);
				glVertex2f(i - 0.5, j + 0.5);
				glEnd();
			}
			if (occupied[i][j] == 0) { // fill line
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 0);
				glVertex2f(i + 0.5,j);
				glVertex2f(i + 0.354, j - 0.354);
				glVertex2f(i, j - 0.5);
				glVertex2f(i - 0.354, j - 0.354);
				glVertex2f(i - 0.5,j);
				glVertex2f(i - 0.354, j + 0.354);
				glVertex2f(i, j + 0.5);
				glVertex2f(i + 0.354, j + 0.354);
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
		else if (key == GLUT_KEY_DOWN)
			level = (level + 1) % 4;
	}
	else if (gamemode == 1) {
		if (direction == GLUT_KEY_UP && key == GLUT_KEY_DOWN) {}
		else if (direction == GLUT_KEY_DOWN && key == GLUT_KEY_UP) {}
		else if (direction == GLUT_KEY_RIGHT && key == GLUT_KEY_LEFT) {}
		else if (direction == GLUT_KEY_LEFT && key == GLUT_KEY_RIGHT) {}
		else direction = key;
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
	if (gamemode == 2) {
		if ((int)key == 13) {
			gamemode = 0;
			player_life = 3; // life
			zombie_killed = 0;
			zombies.clear();

			for (int i = 0; i < WIDTH + 1; i++)  // initialize occupied as -1
				for (int j = 0; j < HEIGHT + 1; j++)
					occupied[i][j] = -1;// -1 : black, 0 : line, 1 : white 

			p.setX(WIDTH / 2); p.setY(HEIGHT / 2);

			for (int i = WIDTH / 2 - WIDTH / 10; i <= WIDTH / 2 + WIDTH / 10; i++) // declare initial area
				for (int j = HEIGHT / 2 - HEIGHT / 10; j < HEIGHT / 2 + HEIGHT / 10; j++)
					occupied[i][j] = 1;

			direction = 0;
		}
	}
}
void select_level() {
	glColor3f(1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_18, "SELECT LEVEL", WIDTH / 3, HEIGHT + HEIGHT / 10.0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "EASY", WIDTH / 3, HEIGHT - HEIGHT / 10.0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "NORMAL", WIDTH / 3, HEIGHT - 3 * HEIGHT / 10.0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "HARD", WIDTH / 3, HEIGHT - 5 * HEIGHT / 10.0);
	draw_string(GLUT_BITMAP_HELVETICA_18, "HELL", WIDTH / 3, HEIGHT - 7 * HEIGHT / 10.0);

	switch (level) {
	case EASY:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(WIDTH/600.0 * 180.0, HEIGHT  - HEIGHT / 10.0 + HEIGHT * 6 / 500);
		glEnd();
		break;
	case NORMAL:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(WIDTH / 600.0 * 180.0, HEIGHT - 3*HEIGHT / 10.0  + HEIGHT * 6 / 500);
		glEnd();
		break;
	case HARD:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(WIDTH / 600.0 * 180.0, HEIGHT - 5 * HEIGHT / 10.0  + HEIGHT * 6 / 500);
		glEnd();
		break;
	case HELL:
		glPointSize(15.0f);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 0);
		glVertex2f(WIDTH / 600.0 * 180.0, HEIGHT -7* HEIGHT / 10.0 + HEIGHT * 6 / 500);
		glEnd();
		break;
	}
}
void draw_outline() {
	glColor3f(1, 1, 1);
	draw_string(GLUT_BITMAP_HELVETICA_12, "LIFE", 0, HEIGHT + HEIGHT / 5.0 - HEIGHT / 50);
	draw_string(GLUT_BITMAP_HELVETICA_12, "LEVEL", WIDTH / 3, HEIGHT + HEIGHT / 5.0 - HEIGHT / 50);
	draw_string(GLUT_BITMAP_HELVETICA_12, "RATIO", WIDTH * 2.0 / 3, HEIGHT + HEIGHT / 5.0 - HEIGHT / 50);

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f(0, HEIGHT +2);
	glVertex2f(WIDTH, HEIGHT +2); // underline
	glVertex2f(WIDTH * 195.0 / 600.0, HEIGHT + HEIGHT/5);
	glVertex2f(WIDTH * 195.0 / 600.0, HEIGHT + 2.5 + 1); // 1st vertical line
	glVertex2f(WIDTH * 395.0 / 600.0, HEIGHT + HEIGHT/5);
	glVertex2f(WIDTH * 395.0 / 600.0, HEIGHT + 2.5 + 1); // 2nd vertical line
	glEnd();

	glColor3f(0, 1, 1);
	// show player life
	glBegin(GL_POINTS);
	glPointSize(5.0f);
	for (int i = 0; i < player_life; i++) {
		glVertex2f(WIDTH / 12.0 * (i+1), HEIGHT + 0.1 * HEIGHT);
	}
	glEnd();
	
	switch (level) {
	case EASY:
		draw_string(GLUT_BITMAP_HELVETICA_18, "EASY", WIDTH * 250 / 600.0 + 5, HEIGHT + HEIGHT / 10.0);
		break;
	case NORMAL:
		draw_string(GLUT_BITMAP_HELVETICA_18, "NORMAL", WIDTH * 250 / 600.0 + 5, HEIGHT + HEIGHT / 10.0);
		break;
	case HARD:
		draw_string(GLUT_BITMAP_HELVETICA_18, "HARD", WIDTH * 250 / 600.0 + 5, HEIGHT + HEIGHT / 10.0);
		break;
	case HELL:
		draw_string(GLUT_BITMAP_HELVETICA_18, "HELL", WIDTH * 250 / 600.0 + 5, HEIGHT + HEIGHT / 10.0);
		break;
	}

	//print occupied area ratio
	//need to address memory leakage
	char* c = new char[7];
	if (ratio() > 99.99) c[0] = '1'; else c[0] = ' ';
	c[1] = (int)(ratio() / 10) - 10* (int)(ratio()/100);
	c[1] += 48;
	c[2] = (int)(ratio() / 1) - 10 * (int)(ratio() / 10);
	c[3] = '.';
	c[4] = (int)(ratio() / 0.1) - 10 * (int)(ratio() / 1);
	c[5] = (int)(ratio() / 0.01) - 10 * (int)(ratio() / 0.1);
	c[2] += 48;
	c[4] += 48;
	c[5] += 48;
	c[6] = '%';

	glRasterPos2f(WIDTH * 450 / 600.0, HEIGHT + HEIGHT / 10.0);
	for (int i = 0; i < 7; i++) 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
}
void player_move() {
	if (direction == GLUT_KEY_UP && (p.getY() + 1) < HEIGHT + 1) {
		if (occupied[p.getX()][p.getY() + 1] == 0)	p.player_dead();
		else p.setY(p.getY() + 1);
	}
	else if (direction == GLUT_KEY_DOWN && (p.getY() - 1) > 0) {
		if (occupied[p.getX()][p.getY() - 1] == 0) p.player_dead();
		else p.setY(p.getY() - 1);
	}
	else if (direction == GLUT_KEY_LEFT && (p.getX() - 1) > 0) {
		if (occupied[p.getX() - 1][p.getY()] == 0) p.player_dead();
		else p.setX(p.getX() - 1);
	}
	else if (direction == GLUT_KEY_RIGHT && (p.getX() + 1) < WIDTH) {
		if (occupied[p.getX() + 1][p.getY()] == 0) p.player_dead();
		else p.setX(p.getX() + 1);
	}
}
void idle() {
	if (gamemode == 0) {}
	else if (gamemode == 1) {
		finish = clock();
		if (finish - start > 100 / 5) {
			start = finish;
			bool s;
			if (occupied[p.getX()][p.getY()] == 0) s = true;
			else s = false;
			player_move();
			if (occupied[p.getX()][p.getY()] == 1 && s) {
				for (int i = 0; i < WIDTH+1; i++)
					for (int j = 0; j < HEIGHT+1; j++)
						if (occupied[i][j] == 0) occupied[i][j] = 1;
				fill_area();
				for (int i = 0; i < WIDTH+1; i ++)
					for (int j = 0; j < HEIGHT+1; j ++)
						if (occupied[i][j] == -1) occupied[i][j] = 1;
				for (int i = 0; i < WIDTH+1; i ++)
					for (int j = 0; j < HEIGHT+1; j ++)
						if (occupied[i][j] == 2) occupied[i][j] = -1;
			}

			if (occupied[p.getX()][p.getY()] == -1 || occupied[p.getX()][p.getY()] == 2)   occupied[p.getX()][p.getY()] = 0; // black to yellow

			for (auto z : zombies) {
				if (occupied[z.getX()][z.getY()] == 0 && z.exist()) p.player_dead();

				if (occupied[z.getX()][z.getY()] == 1 && z.exist() == true) {
					z.zombie_die();
				}
				else if (z.exist())z.move();

				newzombies.push_back(z);
			}
			zombies.clear();
			for (auto z : newzombies) {
				zombies.push_back(z);
			}
			newzombies.clear();
		}
	}
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gamemode == 0)
		select_level();
	else if (gamemode == 1 && player_life > 0 && ratio() < 70) {
		draw_outline();
		draw_area();
		p.drawPlayer();
		for (auto zombie : zombies) {
			if (zombie.exist())
				zombie.draw_zombie();
		}
		glColor3f(1, 1, 0);
		draw_string(GLUT_BITMAP_HELVETICA_12, "Zombie(s) Killed : ", WIDTH / 3.0, HEIGHT - HEIGHT / 100.0 - 1);
		glRasterPos2f(WIDTH / 3.0 + WIDTH / 5, HEIGHT - HEIGHT / 100.0 - 1);
		char c[4];
		c[0] = zombie_killed / 1000 + 48;
		c[1] = (zombie_killed % 1000) / 100 + 48;
		c[2] = (zombie_killed % 100) / 10 + 48;
		c[3] = (zombie_killed % 10) / 1 + 48;
		for (int i = 0; i < 4; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c[i]);
	}
	else if (gamemode == 1 && (player_life == 0 || ratio() >= 70))
		gamemode++;
	else if (gamemode == 2){
		draw_outline();
		draw_string(GLUT_BITMAP_HELVETICA_18, "RESTART : PRESS ENTER KEY", WIDTH / 5 + 10, HEIGHT / 6.0 * 3.0);
		if (player_life == 0) draw_string(GLUT_BITMAP_HELVETICA_18, "GAME OVER", WIDTH / 2.5 + 10, HEIGHT / 5.0 * 3.0);
		else draw_string(GLUT_BITMAP_HELVETICA_18, "WIN", WIDTH / 2.5 + 10, HEIGHT / 5.0 * 3.0);
	}
	glutPostRedisplay();
	glutSwapBuffers();
}




int main(int argc, char** argv) {
	//initialize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(650, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Territory Expansion Game");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT + HEIGHT / 5.0);

	//register Callback
	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(idle);
	//enter GLUT event processing cycle
	glutMainLoop();

}