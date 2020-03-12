//---------------------------------------
// Program: shading.cpp
// Purpose: Functions for Phong shading
// Author:  John Gauch
// Date:    March 2013
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif





// Put following inside init() function
// glShadeModel(GL_SMOOTH);
// glEnable(GL_NORMALIZE);
// init_light(GL_LIGHT0, 0, 1, 1, 0.5, 0.5, 0.5);
// init_light(GL_LIGHT1, 0, 0, 1, 0.5, 0.5, 0.5);
// init_light(GL_LIGHT2, 0, 1, 0, 0.5, 0.5, 0.5);

// Put following inside display() function
// init_material(Ka, Kd, Ks, 100 * Kp, 0.8, 0.6, 0.4);
