/*
 * chart.cpp
 *
 *  Created on: Jan 20, 2020
 *      Author: osboxes
 */

#include "chart.h"

void Option()
{
	ifstream ifile;
	string option, data, filename;
    vector<int> arr;

	int space = 46;	//space in between data point
	int n = 0; //n number of data point

	cout << "What type of chart do you want to make?" << endl;
	cout << "Type 'point', 'column', 'line', 'area' to choose: ";
	cin >> option;

	cout << "Please type the name of the text data file: ";
	cin >> filename;
	ifile.open(filename.c_str());

	if(!ifile)
	{
		cout << "Cannot open the file. Please try again." << endl;
		cout << "Please type the name of the text data file: ";
		cin >> filename;
		ifile.open(filename.c_str());
	}

    while (ifile >> data)
    {
        n++;
        arr.push_back(stoi(data));
    }

	if(option == "point")
	{
		ofstream ofile("point.txt");
		ChartFormatPoint(n, space, arr, ofile);
	    return ;
	}
	else if(option == "column")
		return ;
	else if(option == "line")
		return ;
	else if(option == "area")
		return ;
	else
		cout << "Cannot find that type of chart. Please restart the application." << endl;

	ifile.close();
}

void ChartFormatPoint(int n, int space, vector<int> arr, ofstream& ofile)
{
	int width = 1;
	int size = 6;
	int line_start_horizontal = 10;
	int line_end_horizontal = 484;
	int line_start_vertical = 10;
	int line_end_vertical = 16;
	int start = 16;
	int spacing_vertical = start, spacing_horizontal = start, point_start = start;
	int min = *min_element(arr.begin(), arr.end());
	int max = *max_element(arr.begin(), arr.end());

	SetColor(1.0, 1.0, 1.0, ofile);
	//draw horizontal lines
	for(int i = 0; i <= n; i++)	//i <= n since skipping the (0,0) data point
	{
		ofile << "draw_line " << width << " " << line_start_horizontal
				<< " " << spacing_horizontal << " " << line_end_horizontal
				<< " " << spacing_horizontal << endl;

		spacing_horizontal = spacing_horizontal + space;
	}
	//draw vertical lines
	for(int j = 0; j <= n; j++) //j <= n since skipping the (0,0) data point
	{
		ofile << "draw_line " << width << " " << spacing_vertical
				<< " " << line_start_vertical << " "  << spacing_vertical
				<< " " << line_end_vertical << endl;

		spacing_vertical = spacing_vertical + space;
	}

	SetColor(0.5, 1.0, 0.5, ofile);

	for(int x : arr)
	{
		point_start += space;
		ofile << "draw_point " << size << " " << point_start
				<< " " << LinearInterpolation(x, min, max) + start << endl;
	}
}

int LinearInterpolation(int x, int low, int high)
{
	float screenSize = 470;
	return (screenSize * ((float) (x - 0) / (float) (high - 0)));
}

void SetColor(float red, float green, float blue, ofstream& ofile)
{
	ofile << "set_color " << red << " " << green << " " << blue << endl;
}

