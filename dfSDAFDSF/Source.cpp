#define _CRT_SECURE_NO_WARNINGS

#include<gl/glut.h>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
#define up 1
#define down -1
#define right 2
#define left -2

int Mainfont = (int)GLUT_BITMAP_TIMES_ROMAN_24;
int gridx = 40, gridy = 40;
int FPS = 10;
int slength = 5;
bool food = true;
int foodx, foody;
short direction = right;
bool gameover = false;
int score = 0;
int start = 0;
int posx[60] = { 20,20,20,20,20 }, posy[60] = { 20,19,18,17,16 };

//random positions for food
void random(int& x, int& y)
{
	int maxx = gridx - 2;
	int maxy = gridy - 2;
	int minn = 1;
	srand(time(NULL));
	x = minn + rand() % (maxx - minn);
	y = minn + rand() % (maxy - minn);
}


void unit(int x, int y)
{

	if (x == 0 || y == 0 || x == gridx - 1 || y == gridy - 1)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(0, 0, 0);
	}
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1, y);
	glVertex2f(x + 1, y + 1);
	glVertex2f(x, y + 1);
	glEnd();
}
void drawgrid()
{
	for (int x = 0; x < gridx; x++)
	{
		for (int y = 0; y < gridy; y++)
		{
			unit(x, y);
		}
	}
}


void drawFood()
{
	if (food)
		random(foodx, foody);
	food = false;
	glColor3f(1.0, 0.0, 0.0);
	glRectf(foodx, foody, foodx + 1, foody + 1);//Draw rectangle for food
}

void drawsnake()
{
	for (int i = slength - 1; i > 0; i--)
	{
		posx[i] = posx[i - 1];
		posy[i] = posy[i - 1];
	}
	if (direction == up)
		posy[0]++;
	else if (direction == down)
		posy[0]--;
	else if (direction == right)
		posx[0]++;
	else if (direction == left)
		posx[0]--;
	for (int i = 0; i < slength; i++)
	{
		if (i == 0)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.0, 1.0);
		glRectd(posx[i], posy[i], posx[i] + 1, posy[i] + 1);
	}
	for (int j = 1; j < slength; j++)
	{
		if (posx[j] == posx[0] && posy[j] == posy[0])
			gameover = true;
	}

	if (posx[0] == 0 || posx[0] == gridx - 1 || posy[0] == 0 || posy[0] == gridy - 1)
		gameover = true;
	if (posx[0] == foodx && posy[0] == foody)
	{
		score++;
		slength++;
		if (slength > 60)
			slength = 60;
		food = true;
	}
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, gridx, 0.0, gridy, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (direction != down)
			direction = up;
		break;
	case GLUT_KEY_DOWN:
		if (direction != up)
			direction = down;
		break;
	case GLUT_KEY_RIGHT:
		if (direction != left)
			direction = right;
		break;
	case GLUT_KEY_LEFT:
		if (direction != right)
			direction = left;
		break;
	}

}

void restartGame() {
	slength = 5;
	food = true;
	direction = right;
	score = 0;
	start = 1;
	// go to level 1
	gameover = false;
	// reset snake position
	for (int i = 0; i < slength; i++) {
		posx[i] = 20;
		posy[i] = 20 - i;
	}
}
void renderText(float x, float y, void* font, std::string s) {
	glRasterPos2f(x, y);
	for (int i = 0; i < s.size(); i++) {
		glutBitmapCharacter(font, s[i]);
	}
}
void firstpage()
{
	glColor3f(1.000, 1.000, 0.000);
	renderText(15, 35, (void*)Mainfont, "Snake Game");

	glColor3f(0.000, 1.000, 0.000);
	renderText(10, 25, (void*)Mainfont, "Press SPACE to START");
	renderText(10, 22, (void*)Mainfont, "Press ESC to Exit");

	glColor3f(1.000, 1.000, 1.000);
	renderText(10, 19, (void*)Mainfont, "Use arrow keys to control the snake");
	renderText(10, 17, (void*)Mainfont, "Eat red blocks to increase length");
	renderText(10, 15, (void*)Mainfont, "Avoid hitting the walls and yourself");

}
void drawgameover() {
	glColor3d(1, 0, 0);
	renderText(15, 24, (void*)Mainfont, "Game Over");
	glColor3d(1, 1, 1);
	renderText(10, 22, (void*)Mainfont, "Press SPACE to START Again");
	glColor3d(1, 1, 1);
	renderText(10, 20, (void*)Mainfont, "Press ESC to Exit The game");
}

float xPosSquare = 2.0;
float yPosSquare = 2.0;
float squareSize = 0.1;

void drawBlueSquare()
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(-squareSize / 0.3 + xPosSquare, -squareSize / 0.3 + yPosSquare);
	glVertex2f(squareSize / 0.3 + xPosSquare, -squareSize / 0.3 + yPosSquare);
	glVertex2f(squareSize / 0.3 + xPosSquare, squareSize / 0.3 + yPosSquare);
	glVertex2f(-squareSize / 0.3 + xPosSquare, squareSize / 0.3 + yPosSquare);
	glEnd();
	
}
bool checkCollision()
{
	for (int i = 0; i < slength; i++) {
		float distance = sqrt(pow(posx[i] - xPosSquare, 2) + pow(posy[i] - yPosSquare, 2));

		if (distance < (squareSize / 2 + 0.4)) {
			gameover = true;
			return true;
		}
	}
	return false;
}
void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}
void drawscore() {
	char s[50];
	sprintf(s, "Your Score is : %d", score);
	glColor3f(1, 1, 1);
	renderText(4, 36, (void*)Mainfont, s);
}
void drawleveltwotransition() {
	glColor3f(0, 1, 0);
	renderText(10, 20, (void*)Mainfont, "click number 2 to go to level two ");
	renderText(10, 18, (void*)Mainfont, "Press ESC to Exit The game");
}
void drawlevelthreetransition() {
	glColor3f(0, 1, 0);
	renderText(17, 20, (void*)Mainfont, "click number 3 to go to level Three ");
	renderText(10, 18, (void*)Mainfont, "Press ESC to Exit The game");
}
void drawlevelvictorytransition() {
	glColor3f(0, 1, 0);
	renderText(17, 20, (void*)Mainfont, "Victory!!!!!!!!!!!!!!");
	renderText(10, 18, (void*)Mainfont, "Space to restart");
	renderText(10, 16, (void*)Mainfont, "Press ESC to Exit The game");
}

void processKeys(unsigned char key, int x, int y) {
	switch (key) {
	case ' ':
		start = 1;
		if (start == 1 || start == 0) // only in the first gameover
			restartGame();
		break;
	case '2':
		start = 2;
		break;
	case '3':
		start = 3;
		break;
	case 27:
		exit(0);
	}
}

int l2,l3; //use to draw level two transition and level three transition
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	if (gameover)
	{
		FPS = 10;
		drawgameover();
	}
	else if (start == 0) {
		firstpage();
		// first page that appears to the user when he opens the game remember
	}
	else if (start == 1 || l2 == 1 || l3 == 1) {
		if (start == 1)
			FPS = 10;
		if (l2 == 1 && start == -1)
		{
			drawleveltwotransition();
			FPS = 20;
		}
		if (l3 == 1 && start == -2)
		{
			drawlevelthreetransition();
			FPS = 30;
		}
		if (start == 1 || start == 2 || start == 3) {
			glColor3f(1, 1, 1);
			if (start == 1)
				renderText(31, 36, (void*)Mainfont, "Level one");
			if (start == 2)
				renderText(31, 36, (void*)Mainfont, "Level two");
			if (start == 3)
				renderText(31, 36, (void*)Mainfont, "Level Three");
			drawscore();
			drawgrid();
			drawsnake();
			drawFood();
			if (start == 2 || start == 3) {
				drawBlueSquare();
				float speed = 0.5;
				float distance = sqrt(pow(xPosSquare - posx[0], 2) + pow(yPosSquare - posy[0], 2));

				if (distance > 0.01) {

					float deltaX = (posx[0] - xPosSquare) / distance;
					float deltaY = (posy[0] - yPosSquare) / distance;

					xPosSquare += deltaX * speed;
					yPosSquare += deltaY * speed;

				}
				if (checkCollision())
				{
					drawgameover();
					xPosSquare = 2;
					yPosSquare = 2;
					gameover = true;
				}
			}
		}
	}
	if (score == 5 && start == 1)
	{
		l2 = 1;
		start = -1;
		score = 0;
		 xPosSquare = 2.0;
		 yPosSquare = 2.0;
		 slength = 5;
		 for (int i = 0; i < 5; i++)
		 {
			 posx[i] = 20;
		 }
		 for (int i = 0; i < 5; i++)
		 {
			 posy[i] = 20 - i;
		 }
		
	}
	if (score == 10 && start == 2)
	{
		l3 = 1;
		start = -2;
		score = 0;
		xPosSquare = 2.0;
		yPosSquare = 2.0;
		slength = 5;
		for (int i = 0; i < 5; i++)
		{
			posx[i] = 20;
		}
		for (int i = 0; i < 5; i++)
		{
			posy[i] = 20 - i;
		}
	}
	if (score == 15 && start == 3)
	{
		start = 4;
	}
	if (start == 4)
	{
		drawlevelvictorytransition();
		drawscore();
	}
	
	glFlush();
	glutSwapBuffers();
}

void myinit1() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Snake Game");
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	myinit1();

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);

	glutTimerFunc(0, timer, 0);

	glutKeyboardFunc(processKeys);

	glutSpecialFunc(keyboard);


	glutMainLoop();

}