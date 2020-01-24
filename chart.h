/*
 * chart.h
 *
 *  Created on: Jan 20, 2020
 *      Author: osboxes
 */

#ifndef CHART_H_
#define CHART_H_

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Option();
void ChartFormatPoint(int n, int space, vector<int> arr, ofstream& ofile);

void SetColor(float red, float green, float blue, ofstream& ofile);
int LinearInterpolation(int x, int low, int high);


#endif /* CHART_H_ */
