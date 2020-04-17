//---------------------------------------
// Program: texture3.cpp
// Purpose: Texture map brick photograph
//          onto a cube model.
// Author:  John Gauch
// Date:    April 2011
//---------------------------------------
#include <math.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "libim/im_color.h"

// Global variables 
int xdim, ydim;

const int COUNT = 20;
const float RADIUS = 0.25;

// array of structs

struct Cube
{
   float Px;
   float Py;
   float Pz;
   float Vx;
   float Vy;
   float Vz;
   float Ax;
   float Ay;
   float Az;
   float Radius;
   // texture
   unsigned char *texture;
};

Cube cube[COUNT];

//---------------------------------------
// Util funcs self-explain
//---------------------------------------

float random_float(float a, float b) 
{
   float random = ((float) rand()) / (float) RAND_MAX;
   float diff = b - a;
   float r = random * diff;
   return a + r;
}

string generate_image()
{
   string image_string = "cats_dogs/";
   image_string += (rand() % 2 == 0 ? "cat" : "dog") + (to_string(rand() % 10) + ".jpg");
   cout << "Generated: " << image_string << endl;
   return image_string;
}

//---------------------------------------
// Initialize texture image
//---------------------------------------
void init_texture(char *name, unsigned char *&texture, int &xdim, int &ydim)
{
   // Read jpg image
   im_color image;
   image.ReadJpg(name);
   //printf("Reading image %s\n", name);
   xdim = 1; while (xdim < image.R.Xdim) xdim*=2; xdim /=2;
   ydim = 1; while (ydim < image.R.Ydim) ydim*=2; ydim /=2;
   image.Interpolate(xdim, ydim);
   //printf("Interpolating to %d by %d\n", xdim, ydim);

   // Copy image into texture array
   texture = (unsigned char *)malloc((unsigned int)(xdim*ydim*3));
   int index = 0;
   for (int y = 0; y < ydim; y++)
      for (int x = 0; x < xdim; x++)
      {
         texture[index++] = (unsigned char)(image.R.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.G.Data2D[y][x]);
         texture[index++] = (unsigned char)(image.B.Data2D[y][x]);
      }
}

void idle()
{
   for(int i = 0; i < COUNT; i++)
   {
      //Gravity
      cube[i].Py += cube[i].Vy;

      if(cube[i].Py < -5)  //Reset the cube to the top with random velocity
      {
         cube[i].Py = random_float((3 + RADIUS), (5 - RADIUS));
         cube[i].Vy = random_float(-0.01, -0.003);
      }
   }

   glutPostRedisplay();
}

void timer(int i)
{
   for(int i = 0; i < COUNT; i++)
   {
      cube[i].Ax += cube[i].Ax + 1;
   }

   glutPostRedisplay();
   glutTimerFunc(1000, timer, 0);
}

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Init view
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, -100.0, 100.0);
   glEnable(GL_DEPTH_TEST);

   srand(time(NULL));

   for(int i = 0; i < COUNT; i++)
   {
      //init cube location, velocity, angle
      cube[i].Px = random_float((-2 + RADIUS), (2 - RADIUS));
      cube[i].Py = random_float((3 + RADIUS), (10 - RADIUS));
      cube[i].Pz = random_float((-2 + RADIUS), (2 - RADIUS));  
      cube[i].Vx = 0;
      cube[i].Vy = random_float(-0.01, -0.005);
      cube[i].Vz = 0;
      cube[i].Ax = random_float(0, 45);
      cube[i].Ay = random_float(0, 45);
      cube[i].Az = 0;
      cube[i].Radius = RADIUS;
      
      //init cube texture using randomize generator
      init_texture((char *)generate_image().c_str(), cube[i].texture, xdim, ydim);
   }

   //init_texture((char *)"cats_dogs/cat0.jpg", texture, xdim, ydim);
   glEnable(GL_TEXTURE_2D);
   //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//---------------------------------------
// Function to draw 3D block
//---------------------------------------
void block(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
   // Define 8 vertices
   float ax = xmin, ay = ymin, az = zmax;
   float bx = xmax, by = ymin, bz = zmax;
   float cx = xmax, cy = ymax, cz = zmax;
   float dx = xmin, dy = ymax, dz = zmax;

   float ex = xmin, ey = ymin, ez = zmin;
   float fx = xmax, fy = ymin, fz = zmin;
   float gx = xmax, gy = ymax, gz = zmin;
   float hx = xmin, hy = ymax, hz = zmin;

   // Draw 6 faces
   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(dx, dy, dz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(hx, hy, hz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(hx, hy, hz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(gx, gy, gz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 1.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(bx, by, bz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(cx, cy, cz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 3.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(ax, ay, az);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(ex, ey, ez);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(fx, fy, fz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(bx, by, bz);
   glEnd();

   glBegin(GL_POLYGON);  // Max texture coord 3.0
   glTexCoord2f(0.0, 0.0);
   glVertex3f(gx, gy, gz);
   glTexCoord2f(1.0, 0.0);
   glVertex3f(cx, cy, cz);
   glTexCoord2f(1.0, 1.0);
   glVertex3f(dx, dy, dz);
   glTexCoord2f(0.0, 1.0);
   glVertex3f(hx, hy, hz);
   glEnd();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   float temp_xmin, temp_xmax, temp_ymin, temp_ymax, temp_zmin, temp_zmax, temp_radius;

   // Draw objects
   for(int i = 0; i < COUNT; i++) 
   {
      glPushMatrix();   //For individual rotation
      //Calculate cube dimension
      temp_radius = cube[i].Radius;
      temp_xmin = cube[i].Px - temp_radius;
      temp_xmax = cube[i].Px + temp_radius;
      temp_ymin = cube[i].Py - temp_radius;
      temp_ymax = cube[i].Py + temp_radius;
      temp_zmin = cube[i].Pz - temp_radius;
      temp_zmax = cube[i].Pz + temp_radius;

      //Apply texture
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, cube[i].texture);
      
      glTranslatef(cube[i].Px, cube[i].Py, cube[i].Pz);
      glRotatef(cube[i].Ax, 1.0, 0.0, 0.0);
      glRotatef(cube[i].Ay, 0.0, 1.0, 0.0);
      glTranslatef(-(cube[i].Px), -(cube[i].Py), -(cube[i].Pz));

      //Actual draw
      block(temp_xmin, temp_ymin, temp_zmin, temp_xmax, temp_ymax, temp_zmax);
      glPopMatrix();
   }
   glFlush();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Texture");
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutTimerFunc(0, timer, 0);

   init();
   glutMainLoop();
   return 0;
}


