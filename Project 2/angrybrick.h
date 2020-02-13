/*
 * angrybrick.h
 *
 *  Created on: Feb 7, 2020
 *      Author: osboxes
 */

#ifndef ANGRYBRICK_H_
#define ANGRYBRICK_H_

#include <iostream>
#include <GL/glut.h>
using namespace std;

void Draw(int argc, char *argv[]);
void init();

void cube();

void display();
void idle();
void timer(int i);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);

#endif /* ANGRYBRICK_H_ */
