/*
 * draw.cpp
 *
 *  Created on: Jan 25, 2020
 *      Author: osboxes
 */
#include "draw.h"

void init()
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(0, 500.0, 0, 500.0, 0, 500.0);
}

//selector and then display corresponding to selected chart
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	ifstream ifile;
	string option, filename;

	cout << "What type of chart do you want to draw?" << endl;
	cout << "Type 'point', 'column', 'line', 'area' to choose: ";
	cin >> option;

	if(option == "point")
	{
		ifile.open("point.txt");
	}
	else if(option == "line")
	{
		ifile.open("line.txt");
	}
	else if(option == "column")
	{
		ifile.open("column.txt");
	}
	else if(option == "area")
	{
		ifile.open("area.txt");
	}

	DrawChart(ifile);
	glFlush();
}

void Draw(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
}

//actual drawing type of charts
void DrawChart(ifstream& ifile)
{
	string data;
	while(ifile >> data)
	{
		if(data == "set_color")
		{
			string red, green, blue;
			ifile >> red >> green >> blue;
			SetColor(stof(red), stof(green), stof(blue));
		}
		else if(data == "draw_line")
		{
			string width, x1, y1, x2, y2;
			ifile >> width >> x1 >> y1 >> x2 >> y2;
			SetLine(stoi(width), stof(x1), stof(y1), stof(x2), stof(y2));
		}
		else if(data == "draw_point")
		{
			string size, x, y;
			ifile >> size >> x >> y;
			SetPoint(stoi(size), stof(x), stof(y));
		}
		else if(data == "draw_polygon")
		{
			string n;
			ifile >> n;
			SetArea(stoi(n), ifile);
		}
	}
}

//utility functions for drawing
void SetColor(float red, float green, float blue)
{
	glColor3f(red, green, blue);
}

void SetLine(int width, float x1, float y1, float x2, float y2)
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);
	glEnd();
}

void SetPoint(int size, float x, float y)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

void SetArea(int n, ifstream& ifile)
{
	glBegin(GL_POLYGON);
	while (n > 0)
	{
		string x, y;
		ifile >> x >> y;
		glVertex3f(stof(x), stof(y), 0);
		n--;
	}
	glEnd();
}

