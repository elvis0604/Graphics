/*
 * main.cpp
 *
 *  Created on: Jan 20, 2020
 *      Author: osboxes
 */

#include "chart.h"

int main()
{
	string option;
	cout << "Enter option and data: ";
	cin >> option;
	int selected_option = Option(option);
	cout << selected_option << endl;
	return 0;
}



