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
    vector<int> vec;
    string path = "../openGLchart/";

    int maxScreenSize = 500;
    int offset = 4;
	int space = 46;	//space in between data point original: 46
	int n = 0; //n number of data point

	cout << "What type of chart do you want to generate?" << endl;
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
        vec.push_back(stoi(data));
    }

	space = (maxScreenSize / n) - offset;
	cout << "Space between point = " << space << endl;

	if(option == "point")
	{
		ofstream ofile(path + "point.txt");
		ChartFormatPoint(n, space, vec, ofile);
		cout << "point.txt generated" << endl;
		ofile.close();
	    return ;
	}
	else if(option == "line")
	{
		ofstream ofile(path + "line.txt");
		ChartFormatLine(n, space, vec, ofile);
		cout << "line.txt generated" << endl;
		ofile.close();
		return ;
	}
	else if(option == "column")
	{
		ofstream ofile(path + "column.txt");
		ChartFormatColumn(n, space, vec, ofile);
		cout << "column.txt generated" << endl;
		ofile.close();
		return ;
	}
	else if(option == "area")
	{
		ofstream ofile(path + "area.txt");
		ChartFormatArea(n, space, vec, ofile);
		cout << "area.txt generated" << endl;
		ofile.close();
		return ;
	}
	else if(option == "all")
	{
		ofstream ofilePoint(path + "point.txt");
		ChartFormatPoint(n, space, vec, ofilePoint);
		cout << "point.txt generated" << endl;
		ofilePoint.close();
		ofstream ofileLine(path + "line.txt");
		ChartFormatLine(n, space, vec, ofileLine);
		cout << "line.txt generated" << endl;
		ofileLine.close();
		ofstream ofileColumn(path + "column.txt");
		ChartFormatColumn(n, space, vec, ofileColumn);
		cout << "column.txt generated" << endl;
		ofileColumn.close();
		ofstream ofileArea(path + "area.txt");
		ChartFormatArea(n, space, vec, ofileArea);
		cout << "area.txt generated" << endl;
		ofileArea.close();
		return ;
	}
	else
		cout << "Cannot find that type of chart. Please restart the application." << endl;

	ifile.close();
}

void ChartFormatPoint(int n, int space, vector<int> vec, ofstream& ofile)
{
	int width = 6;
	int offset_start = 16; //for both x and y
	int spacing_vertical = offset_start;
	int min = *min_element(vec.begin(), vec.end());
	int max = *max_element(vec.begin(), vec.end());
	int max_spacing_horizontal = 0;
	int offset = 2;

	max_spacing_horizontal = DrawChart(n, space, ofile);

	SetColor(1, 0, 0, ofile);
	for(int x : vec)
	{
		spacing_vertical += space;
		ofile << "draw_point " << width
				<< " " << spacing_vertical
				<< " " << LinearInterpolation(x, min, max, max_spacing_horizontal + offset - offset_start) + offset_start
				<< endl;
	}
}

void ChartFormatLine(int n, int space, vector<int> vec, ofstream& ofile)
{
	int size = 6;
	int offset_start = 16; //for both x and y
	int spacing_vertical = offset_start;
	int min = *min_element(vec.begin(), vec.end());
	int max = *max_element(vec.begin(), vec.end());
	int max_spacing_horizontal = 0;
	int offset = 2;

	max_spacing_horizontal = DrawChart(n, space, ofile);

	SetColor(1, 0, 0, ofile);
	for(unsigned long z = 0; z < vec.size(); z++)
	{
		spacing_vertical += space;
		if(z < vec.size() - 1)
		{
			ofile << "draw_line " << size
					<< " " << spacing_vertical
					<< " " << LinearInterpolation(vec[z], min, max, max_spacing_horizontal + offset - offset_start) + offset_start
					<< " " << spacing_vertical + space
					<< " " << LinearInterpolation(vec[z + 1], min, max, max_spacing_horizontal + offset - offset_start) + offset_start
					<< endl;
		}
	}
}

void ChartFormatColumn(int n, int space, vector<int> vec, ofstream& ofile)
{
	int edges = 4;
	int offset_start = 16; //for both x and y
	int spacing_vertical = offset_start;
	int min = *min_element(vec.begin(), vec.end());
	int max = *max_element(vec.begin(), vec.end());
	int max_spacing_horizontal = 0;
	int offset = 2;
	int offset_corner = 11;

	max_spacing_horizontal = DrawChart(n, space, ofile);

	SetColor(1, 0, 0, ofile);
	for(int x : vec)
	{
		spacing_vertical += space;
		int interpolated_val = LinearInterpolation(x, min, max, max_spacing_horizontal + offset - offset_start) + offset_start;
		ofile << "draw_polygon " << edges
				<< " " << spacing_vertical - offset_corner << " " << interpolated_val
				<< " " << spacing_vertical + offset_corner << " " << interpolated_val
				<< " " << spacing_vertical + offset_corner << " " << offset_start
				<< " " << spacing_vertical - offset_corner << " " << offset_start
				<< " " << endl;
	}
}

void ChartFormatArea(int n, int space, vector<int> vec, ofstream& ofile)
{
	int edges = 4;
	int offset_start = 16; //for both x and y
	int spacing_vertical = offset_start;
	int min = *min_element(vec.begin(), vec.end());
	int max = *max_element(vec.begin(), vec.end());
	int max_spacing_horizontal = 0;
	int offset = 2;

	max_spacing_horizontal = DrawChart(n, space, ofile);

	SetColor(1, 0, 0, ofile);
	for(int z = 0; z < n - 1; z++)
	{
		spacing_vertical += space;
		int interpolated_val = LinearInterpolation(vec[z], min, max,
				max_spacing_horizontal + offset - offset_start) + offset_start;
		int next_interpolated_val = LinearInterpolation(vec[z + 1], min, max,
				max_spacing_horizontal + offset - offset_start) + offset_start;
		ofile << "draw_polygon " << edges
				<< " " << spacing_vertical << " " << offset_start
				<< " " << spacing_vertical << " " << interpolated_val
				<< " " << spacing_vertical + space << " " << next_interpolated_val
				<< " " << spacing_vertical + space << " " << offset_start
				<< endl;
	}
}

int DrawChart(int n, int space, ofstream& ofile)	//return the furtherest coordinate in horizontal line
{
	int width = 1;
	int offset_start = 16;
	int line_start_horizontal = 10;
	int line_end_horizontal = 484;
	int first_line_end_vertical = 484;
	int line_start_vertical = 10;
	int line_end_vertical = 16;
	int spacing_vertical = offset_start, spacing_horizontal = offset_start;
	SetColor(1.0, 1.0, 1.0, ofile);
	//draw horizontal lines
	for(int i = 0; i <= n; i++)	//i <= n since skipping the (0,0) data point
	{
		ofile << "draw_line " << width
				<< " " << line_start_horizontal << " " << spacing_horizontal
				<< " " << line_end_horizontal << " " << spacing_horizontal << endl;
		if(i < n)
			spacing_horizontal = spacing_horizontal + space;
	}
	//draw vertical lines
	for(int j = 0; j <= n; j++) //j <= n since skipping the (0,0) data point
	{
		if(j == 0)	//draw the y coordinate
		{
			ofile << "draw_line " << width
					<< " " << spacing_vertical << " " << line_start_vertical
					<< " "  << spacing_vertical << " " << first_line_end_vertical << endl;
		}
		else
		{
			ofile << "draw_line " << width
					<< " " << spacing_vertical << " " << line_start_vertical
					<< " "  << spacing_vertical << " " << line_end_vertical << endl;
		}

		spacing_vertical = spacing_vertical + space;
	}

	return spacing_horizontal;
}

int LinearInterpolation(int x, int low, int high, int mspace)
{
	return ((float) mspace * ((float) (x - 0) / (float) (high - 0)));
}

void SetColor(float red, float green, float blue, ofstream& ofile)
{
	ofile << "set_color " << red << " " << green << " " << blue << endl;
}

