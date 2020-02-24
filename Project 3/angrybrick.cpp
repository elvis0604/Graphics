/*
 * angrybrick.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: osboxes
 */

#include "angrybrick.h"

GLenum mode = GL_POLYGON;

enum Direction { shootright, shootleft, neither };

enum Bounce { bounceleft, bounceright, nobounce };

float size = 7.5;
float mousex = 50, mousey = 50, mousez = 50;
float mousex_final = 0, mousey_final = 0;
float step = 0.7;

int ANGLE = 10;
float SIZE = 500;
float SCREENSIZEX = SIZE;
float SCREENSIZEY = SIZE;
float GRAVITY = 0.1;
float VELX = 0, VELY = 0;
float SPEED = 0;
float MAXDISTANCE = 0;

bool MOUSEHOLD = true;

Direction dir = neither;
Bounce bounce = nobounce;

#define MINVIEWX -100
#define MAXVIEWX 100
#define MINVIEWY -100
#define MAXVIEWY 100
#define MINVIEWZ -100
#define MAXVIEWZ 100

void init()
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(MINVIEWX, MAXVIEWX,
			MINVIEWY, MAXVIEWY,
			MINVIEWZ, MAXVIEWZ);
	//Calculate max distance we can get from our view
	MAXDISTANCE = sqrt(pow(MAXVIEWX - MINVIEWX, 2) + pow(MAXVIEWY - MINVIEWY, 2));
	glEnable(GL_DEPTH_TEST);
}

void timer(int i)
{
	glutPostRedisplay();

	//Rotating
	ANGLE = (ANGLE + 1) % 360;

	glutTimerFunc(50, timer, 0);
}

void Draw(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(SCREENSIZEX, SCREENSIZEY);
	glutInitWindowPosition(250, 250);
	glutCreateWindow("ANGRY BRICK");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	//glutMotionFunc(motion);
	glutIdleFunc(idle);
	glutTimerFunc(0, timer, 0);


	init();
	glutMainLoop();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		//cout << "x: " << x << " y: " << y << endl;
		mousex = ((x / SCREENSIZEX) * (MAXVIEWX - MINVIEWX)) + MINVIEWX;
		mousey = ((y / SCREENSIZEY) * (MINVIEWY - MAXVIEWY)) + MAXVIEWY;
		cout << "mouse x ini: " << mousex << " mouse y ini: " << mousey << endl;

		//Reset the cube
		VELX = 0, VELY = 0, SPEED = 0;
		bounce = nobounce;
		dir = neither;

		MOUSEHOLD = true;
	}

	if (state == GLUT_UP)
	{
		//cout << "x: " << x << " y: " << y << endl;
		mousex_final = ((x / SCREENSIZEX) * (MAXVIEWX - MINVIEWX)) + MINVIEWX;
		mousey_final = ((y / SCREENSIZEY) * (MINVIEWY - MAXVIEWY)) + MAXVIEWY;
		cout << "mouse x final: " << mousex_final << " mouse y final: " << mousey_final << endl;

		MOUSEHOLD = false;

		float distance = sqrt(pow(mousex_final - mousex, 2) + pow(mousey_final - mousey, 2));
		SPEED = (distance / MAXDISTANCE);	//Calculate speed depending on how far apart your mouse click is
		cout << "distance: " << distance << endl;
		cout << "max distance: " << MAXDISTANCE << endl;
		cout << "speed: " << SPEED << endl;

		//Hacky check if we are shooting left or right
		if(mousex > mousex_final) //Shooting to the left side
			dir = shootleft;
		else if(mousex < mousex_final) //Shooting to the right side
			dir = shootright;
		else if(mousex == mousex_final) //Neither
			dir = neither;
	}
	glutPostRedisplay();
}

void motion(int x, int y)
{
	// Handle mouse motion
	mousex = ((x / SCREENSIZEX) * (MAXVIEWX - MINVIEWX)) + MINVIEWX;
	mousey = ((y / SCREENSIZEY) * (MINVIEWY - MAXVIEWY)) + MAXVIEWY;
	cout << "mouse x: " << mousex << " mouse y: " << mousey << endl;
	glutPostRedisplay();
}


void idle()
{
	if(bounce == nobounce)
	{
		float theta = 0;
		theta = atan ((mousey - mousey_final) / (mousex - mousex_final));	//Calculate angle for velocity

		VELX = cos(theta) * SPEED;
		VELY = sin(theta) * SPEED;
	}

	if(MOUSEHOLD == false)
	{
		if(dir == shootleft && dir != neither)
		{
			mousex += VELX;
			mousey += VELY;
		} else if (dir == shootright && dir != neither)
		{
			mousex -= VELX;
			mousey -= VELY;
		}
		mousey -= GRAVITY;
	}

	//Rightside bounce
	if (mousex > MAXVIEWX)
	{
		mousex = MAXVIEWX;
		VELX *= -step;
		VELY *= -step;
		bounce = bounceright;
	}//Leftside bounce
	if (mousex < MINVIEWX)
	{
		mousex = MINVIEWX;
		VELX *= -step;
		VELY *= -step;
		bounce = bounceleft;
	}

	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Draw the cube
	cube();
	glFlush();
}

void cube()
{
	// Define 8 vertices
	float ax = mousex - size;
	float ay = mousey - size;
	float az = mousez + size;
	float bx = mousex + size;
	float by = mousey - size;
	float bz = mousez + size;
	float cx = mousex + size;
	float cy = mousey + size;
	float cz = mousez + size;
	float dx = mousex - size;
	float dy = mousey + size;
	float dz = mousez + size;
	float ex = mousex - size;
	float ey = mousey - size;
	float ez = mousez - size;
	float fx = mousex + size;
	float fy = mousey - size;
	float fz = mousez - size;
	float gx = mousex + size;
	float gy = mousey + size;
	float gz = mousez - size;
	float hx = mousex - size;
	float hy = mousey + size;
	float hz = mousez - size;

	//Translate to origin then rotate then translate back
	glTranslatef(mousex, mousey, mousez);
	glRotatef(ANGLE, 1.0, 0.5, 0);
	glTranslatef(-mousex, -mousey, -mousez);

	// Draw 6 faces
	glBegin(mode);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(ax, ay, az);
	glVertex3f(bx, by, bz);
	glVertex3f(cx, cy, cz);
	glVertex3f(dx, dy, dz);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(ax, ay, az);
	glVertex3f(dx, dy, dz);
	glVertex3f(hx, hy, hz);
	glVertex3f(ex, ey, ez);
	glEnd();

	glBegin(mode);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(ax, ay, az);
	glVertex3f(ex, ey, ez);
	glVertex3f(fx, fy, fz);
	glVertex3f(bx, by, bz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(fx, fy, fz);
	glVertex3f(ex, ey, ez);
	glVertex3f(hx, hy, hz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(cx, cy, cz);
	glVertex3f(bx, by, bz);
	glVertex3f(fx, fy, fz);
	glEnd();

	glBegin(mode);
	glColor3f(1.0, 0.5, 0.0);
	glVertex3f(gx, gy, gz);
	glVertex3f(hx, hy, hz);
	glVertex3f(dx, dy, dz);
	glVertex3f(cx, cy, cz);
	glEnd();
}



