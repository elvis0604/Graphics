//---------------------------------------
// Program: surface3.cpp
// Purpose: Use Phong shading to display
//          quadratic surface model.
// Author:  John Gauch
// Date:    October 2008
//---------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
// Transformation variables
#define ROTATE 1
#define TRANSLATE 2

ifstream ifiledepth;
ifstream ifilecolor;
int xangle = 0;
int yangle = 0;
int zangle = 0;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int mode = ROTATE;

// Material properties
float Ka = 0.4;
float Kd = 0.4;
float Ks = 0.4;
float Kp = 0.5;

// Surface variables
#define SIZE 500
#define DEPTHSCALE 2
#define LINESCALE 5
#define COLORSCALE 255
float Px[SIZE + 1][SIZE + 1];
float Py[SIZE + 1][SIZE + 1];
float Pz[SIZE + 1][SIZE + 1];
float Nx[SIZE + 1][SIZE + 1];
float Ny[SIZE + 1][SIZE + 1];
float Nz[SIZE + 1][SIZE + 1];
float R[SIZE + 1][SIZE + 1];
float G[SIZE + 1][SIZE + 1];
float B[SIZE + 1][SIZE + 1];
#define STEP 0.1

//---------------------------------------
// Initialize material properties
//---------------------------------------
void init_material(float Ka, float Kd, float Ks, float Kp,
                   float Mr, float Mg, float Mb)
{
   // Material variables
   float ambient[] = { Ka * Mr, Ka * Mg, Ka * Mb, 1.0 };
   float diffuse[] = { Kd * Mr, Kd * Mg, Kd * Mb, 1.0 };
   float specular[] = { Ks * Mr, Ks * Mg, Ks * Mb, 1.0 };

   // Initialize material
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Kp);
}

//---------------------------------------
// Initialize light source
//---------------------------------------
void init_light(int light_source, float Lx, float Ly, float Lz,
                float Lr, float Lg, float Lb)
{
   // Light variables
   float light_position[] = { Lx, Ly, Lz, 0.0 };
   float light_color[] = { Lr, Lg, Lb, 1.0 };

   // Initialize light source
   glEnable(GL_LIGHTING);
   glEnable(light_source);
   glLightfv(light_source, GL_POSITION, light_position);
   glLightfv(light_source, GL_AMBIENT, light_color);
   glLightfv(light_source, GL_DIFFUSE, light_color);
   glLightfv(light_source, GL_SPECULAR, light_color);
   glLightf(light_source, GL_CONSTANT_ATTENUATION, 1.0);
   glLightf(light_source, GL_LINEAR_ATTENUATION, 0.0);
   glLightf(light_source, GL_QUADRATIC_ATTENUATION, 0.0);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

//---------------------------------------
// Initialize surface
//---------------------------------------
void init_surface(ifstream& ifile, float Xmin, float Xmax, float Ymin, float Ymax)
{
   // Initialize surface
	int i, j;
	string depth;

	for (i = 0; i <= SIZE; i++)
		for (j = 0; j <= SIZE; j++)
		{
			ifile >> depth;
			// Storing points
			Px[i][j] = Xmin + i * (Xmax - Xmin) / SIZE;
			Py[i][j] = Ymin + j * (Ymax - Ymin) / SIZE;
			Pz[i][j] = (stof(depth) / SIZE) / DEPTHSCALE;

			/*cout << "Storing X " << Px[i][j] << endl;
			cout << "Storing Y " << Py[i][j] << endl;
			cout << "Storing Z " << Pz[i][j] << endl;*/
		}
}

//---------------------------------------
// Initialize color
//---------------------------------------
void init_color(ifstream& ifile)
{
	int i, j;
	string red, green, blue;

	for (i = 0; i <= SIZE; i++)
		for (j = 0; j <= SIZE; j++)
		{
			ifile >> red >> green >> blue;
			// Storing points
			R[i][j] = stof(red) / COLORSCALE;
			G[i][j] = stof(green) / COLORSCALE;
			B[i][j] = stof(blue) / COLORSCALE;

			cout << "Storing R " << R[i][j] << endl;
			cout << "Storing G " << G[i][j] << endl;
			cout << "Storing B " << B[i][j] << endl;
		}
}

//---------------------------------------
// Initialize surface normals
//---------------------------------------
void init_normals()
{
   // Initialize surface normals
   for (int i=0; i<=SIZE; i++)
	   for (int j=0; j<=SIZE; j++)
	   {
		  // Get tangents S and T
		  float Sx = (i<SIZE) ? Px[i+1][j] - Px[i][j] : Px[i][j] - Px[i-1][j];
		  float Sy = (i<SIZE) ? Py[i+1][j] - Py[i][j] : Py[i][j] - Py[i-1][j];
		  float Sz = (i<SIZE) ? Pz[i+1][j] - Pz[i][j] : Pz[i][j] - Pz[i-1][j];
		  float Tx = (j<SIZE) ? Px[i][j+1] - Px[i][j] : Px[i][j] - Px[i][j-1];
		  float Ty = (j<SIZE) ? Py[i][j+1] - Py[i][j] : Py[i][j] - Py[i][j-1];
		  float Tz = (j<SIZE) ? Pz[i][j+1] - Pz[i][j] : Pz[i][j] - Pz[i][j-1];

		  // Calculate N = S cross T
		  Nx[i][j] = Sy*Tz - Sz*Ty;
		  Ny[i][j] = Sz*Tx - Sx*Tz;
		  Nz[i][j] = Sx*Ty - Sy*Tx;
		  float length = sqrt(Nx[i][j]*Nx[i][j]
					   + Ny[i][j]*Ny[i][j]
					   + Nz[i][j]*Nz[i][j]);
		  if (length > 0)
		  {
			 Nx[i][j] /= length;
			 Ny[i][j] /= length;
			 Nz[i][j] /= length;
		  }
	   }
}


//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   float radius = 2;
   glOrtho(-radius, radius, -radius, radius, -radius, radius);
   glEnable(GL_DEPTH_TEST);

   // Initialize smooth shading

   // Initialize surface
   init_surface(ifiledepth, -1.0, 1.0, -1.0, 1.0);
   init_color(ifilecolor);
}

//---------------------------------------
// Display for WIREFRAME
//---------------------------------------
void display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);

   // Initialize material properties
   init_material(Ka, Kd, Ks, 100 * Kp, 0.6, 0.4, 0.8);

	// Draw the surface LINESCALE is to make draw less line
	int i, j;
	for (i = 0; i < SIZE; i+=LINESCALE)
		for (j = 0; j < SIZE; j+=LINESCALE)
		{
			glBegin(GL_LINE_LOOP);
			glNormal3f(Nx[i][j], Ny[i][j], Nz[i][j]);
			glVertex3f(Px[i][j], Py[i][j], Pz[i][j]) ;
			glNormal3f(Nx[i + 1][j], Ny[i + 1][j], Nz[i + 1][j]);
			glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);
			glNormal3f(Nx[i + 1][j + 1], Ny[i + 1][j + 1], Nz[i + 1][j + 1]);
			glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);
			glNormal3f(Nx[i][j + 1], Ny[i][j + 1], Nz[i][j + 1]);
			glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
			glEnd();
		}
	glFlush();
}

//---------------------------------------
// Display for RGB
//---------------------------------------
void color_display()
{
   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(xpos / 500.0, ypos / 500.0, zpos / 500.0);
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);

	// Draw the surface LINESCALE is to make draw less line
	int i, j;
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
		{
			glBegin(GL_POLYGON);
			glColor3f(R[i][j], G[i][j], B[i][j]);
			glVertex3f(Px[i][j], Py[i][j], Pz[i][j]);
			glColor3f(R[i + 1][j], G[i + 1][j], B[i + 1][j]);
			glVertex3f(Px[i + 1][j], Py[i + 1][j], Pz[i + 1][j]);
			glColor3f(R[i + 1][j + 1], G[i + 1][j + 1], B[i + 1][j + 1]);
			glVertex3f(Px[i + 1][j + 1], Py[i + 1][j + 1], Pz[i + 1][j + 1]);
			glColor3f(R[i][j + 1], G[i][j + 1], B[i][j + 1]);
			glVertex3f(Px[i][j + 1], Py[i][j + 1], Pz[i][j + 1]);
			glEnd();
		}
	glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // Determine if we are in ROTATE or TRANSLATE mode
   if ((key == 'r') || (key == 'R'))
   {
      printf("Type x y z to decrease or X Y Z to increase ROTATION angles.\n");
      mode = ROTATE;
   }
   else if ((key == 't') || (key == 'T'))
   {
      printf
	 ("Type x y z to decrease or X Y Z to increase TRANSLATION distance.\n");
      mode = TRANSLATE;
   }

   // Determine if we are in WIREFRAME, RGB or PHONG mode
   if ((key == '1'))
   {
      printf("Type 1 2 3 to change to WIREFRAME, RGB or PHONG mode.\n");
	  cout << "IN WIREFRAME MODE" << endl;
      glutDisplayFunc(display);
   }
   else if ((key == '2'))
   {
      printf("Type 1 2 3 to change to WIREFRAME, RGB or PHONG mode.\n");
      cout << "IN RGB MODE" << endl;
      glutDisplayFunc(color_display);
   }
   else if ((key == '3'))
   {
      printf("Type 1 2 3 to change to WIREFRAME, RGB or PHONG mode.\n");
      cout << "IN PHONG MODE" << endl;
   }

   // Handle ROTATE
   if (mode == ROTATE)
   {
      if (key == 'x')
	 xangle -= 5;
      else if (key == 'y')
	 yangle -= 5;
      else if (key == 'z')
	 zangle -= 5;
      else if (key == 'X')
	 xangle += 5;
      else if (key == 'Y')
	 yangle += 5;
      else if (key == 'Z')
	 zangle += 5;
   }

   // Handle TRANSLATE
   if (mode == TRANSLATE)
   {
      if (key == 'x')
	 xpos -= 5;
      else if (key == 'y')
	 ypos -= 5;
      else if (key == 'z')
	 zpos -= 5;
      else if (key == 'X')
	 xpos += 5;
      else if (key == 'Y')
	 ypos += 5;
      else if (key == 'Z')
	 zpos += 5;
   }

   // Handle material properties
   if (key == 'a')
      Ka -= STEP;
   if (key == 'd')
      Kd -= STEP;
   if (key == 's')
      Ks -= STEP;
   if (key == 'p')
      Kp -= STEP;
   if (key == 'A')
      Ka += STEP;
   if (key == 'D')
      Kd += STEP;
   if (key == 'S')
      Ks += STEP;
   if (key == 'P')
      Kp += STEP;
   if (Ka < 0)
      Ka = 0;
   if (Kd < 0)
      Kd = 0;
   if (Ks < 0)
      Ks = 0;
   if (Kp < STEP)
      Kp = STEP;
   glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
	string data;
	string depth_file = "penny-depth.txt";
	string color_file = "penny-image.txt";
	// Open output file
	ifiledepth.open(depth_file);
	ifilecolor.open(color_file);

   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("Surface");
   init();
   printf("Type r to enter ROTATE mode or t to enter TRANSLATE mode.\n");

   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}

