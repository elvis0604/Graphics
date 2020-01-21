/*
 * chart.cpp
 *
 *  Created on: Jan 20, 2020
 *      Author: osboxes
 */

#include "chart.h"

int Option(string option)
{
	if(option == "set_color")
		return 1;
	else if(option == "draw_point")
		return 2;
	else if(option == "draw_line")
		return 3;
	else if(option == "draw_polygon")
		return 4;
	else
		return 0;
}

void SetColor(float red, float green, float blue)
{
	cout << "Setting color" << endl;
	cout << "Red: " << red << "Green: " << green << "Blue: " << blue << endl;
}

//todo size is OpenGL related for drawing points
void DrawPoint(int size, int x, int y)
{}

//todo width is OpenGL related for drawing lines
void DrawLine(int width, int x1, int y1, int x2, int y2)
{}
