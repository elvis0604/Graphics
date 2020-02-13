/*
 * angrybrick.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: osboxes
 */

#include "angrybrick.h"

GLenum mode = GL_POLYGON;
float ax,ay,az,bx,by,bz,cx,cy,cz,dx,dy,dz,ex,ey,ez,fx,fy,fz,gx,gy,gz,hx,hy,hz = 0;
float size = 7.5;
float mousex = 50, mousey = 50, mousez = 50;
float angle = 10;
float SCREENSIZEX = 500;
float SCREENSIZEY = 500;

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
	glRotatef(angle, 0.5, 1, 0);
}

void timer(int i)
{
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void Draw(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(SCREENSIZEX, SCREENSIZEY);
	glutInitWindowPosition(250, 250);
	glutCreateWindow("Chart");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	//timer(0);
	init();
	glutMainLoop();
}

void mouse(int button, int state, int x, int y)
{
	//mousex = (x / SCREENSIZEX + MINVIEWX) * (MAXVIEWX - MINVIEWX);

	if (state == GLUT_DOWN)
	{
		cout << "x: " << x << " y: " << y << endl;
		mousex = ((x / SCREENSIZEX) * (MAXVIEWX - MINVIEWX)) + MINVIEWX;
		mousey = ((y / SCREENSIZEY) * (MINVIEWY - MAXVIEWY)) + MAXVIEWY;
		cout << "mouse x: " << mousex << " mouse y: " << mousey << endl;
	}

	/*if (state == GLUT_UP)
	{
		cout << "x: " << x << " y: " << y << endl;
		mousex = ((x / SCREENSIZEX) * (MAXVIEWX - MINVIEWX)) + MINVIEWX;
		mousey = ((y / SCREENSIZEY) * (MINVIEWY - MAXVIEWY)) + MAXVIEWY;
		cout << "mouse x: " << mousex << " mouse y: " << mousey << endl;
	}*/

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

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //glPushMatrix();
   //glRotatef(angle, 1, 0, 0);
   cube();
   //glPopMatrix();
   glutSwapBuffers();
   //angle += 0.3;
   //glFlush();
}

void cube()
{
   // Define 8 vertices
	ax = mousex - size;
	ay = mousey - size;
	az = mousez + size;
	bx = mousex + size;
	by = mousey - size;
	bz = mousez + size;
	cx = mousex + size;
	cy = mousey + size;
	cz = mousez + size;
	dx = mousex - size;
	dy = mousey + size;
	dz = mousez + size;
	ex = mousex - size;
	ey = mousey - size;
	ez = mousez - size;
	fx = mousex + size;
	fy = mousey - size;
	fz = mousez - size;
	gx = mousex + size;
	gy = mousey + size;
	gz = mousez - size;
	hx = mousex - size;
	hy = mousey + size;
	hz = mousez - size;

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



