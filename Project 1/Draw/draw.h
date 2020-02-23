/*
 * draw.h
 *
 *  Created on: Jan 25, 2020
 *      Author: osboxes
 */

#ifndef DRAW_H_
#define DRAW_H_
#include <iostream>
#include <fstream>
#include <GL/glut.h>
using namespace std;

void Draw(int argc, char *argv[]);

//drawing chart functions
void DrawChart(ifstream& ifile);

//utility functions
void SetColor(float red, float green, float blue);
void SetLine(int width, float x1, float y1, float x2, float y2);
void SetPoint(int size, float x, float y);
void SetArea(int n, ifstream& ifile);

//openGL settings
void init();
void display();


#endif /* DRAW_H_ */
