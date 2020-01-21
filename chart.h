/*
 * chart.h
 *
 *  Created on: Jan 20, 2020
 *      Author: osboxes
 */

#ifndef CHART_H_
#define CHART_H_

#include <string>
#include <iostream>
using namespace std;

int Option(string option);
void SetColor(float red, float green, float blue);
void DrawPoint(int size, int x, int y);
void DrawLine(int width, int x1, int y1, int x2, int y2);



#endif /* CHART_H_ */
