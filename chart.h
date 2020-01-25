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
void ChartFormatLine(int n, int space, vector<int> arr, ofstream& ofile);
void ChartFormatColumn(int n, int space, vector<int> vec, ofstream& ofile);
void ChartFormatArea(int n, int space, vector<int> vec, ofstream& ofile);
int DrawChart(int n, int space, ofstream& ofile);

void SetColor(float red, float green, float blue, ofstream& ofile);
int LinearInterpolation(int x, int low, int high, int mspace);


#endif /* CHART_H_ */
