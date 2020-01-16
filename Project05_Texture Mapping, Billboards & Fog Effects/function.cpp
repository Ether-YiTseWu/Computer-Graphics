#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

#include "function.h"
#include "parameter.h"

#define CRT_SECURE_NO_WARNINGS
GLUquadricObj* sphere = NULL, * cylind = NULL, * disk;
int style = 4, flag_texture = 0, flag_fogColor = 0;	// 4-windows mode

void Create_Texture_Circle()
{
	int  y, x, i, temp;
	for (y = 0; y < 64; y++)
	{
		for (x = 0; x < 64; x++)
		{
			circle[y][x][0] = 100;
			circle[y][x][1] = 100;
			circle[y][x][2] = 100;
			circle[y][x][3] = 255;
		}
	}
	for (y = 16, x = 0; y < 48; y++)
	{
		if (y <= 20 && y >= 17)
			x = x + 2;
		else if (y == 22 || y == 25 || y == 31)
			x = x + 1;
		else if (y == 42 || y == 39 || y == 33)
			x = x - 1;
		else if (y <= 47 && y >= 44)
			x = x - 2;
		temp = x;
		for (x = 0; x < temp; x++)
		{
			circle[y][x][0] = 150;
			circle[y][x][1] = 150;
			circle[y][x][2] = 150;
			circle[y][x][3] = 255;
		}
		for (x = 64 - temp; x < 64; x++)
		{
			circle[y][x][0] = 150;
			circle[y][x][1] = 150;
			circle[y][x][2] = 150;
			circle[y][x][3] = 255;
		}
		x = temp;
	}

	for (x = 16, y = 0; x < 48; x++)
	{
		if (x <= 20 && x >= 17)
			y = y + 2;
		else if (x == 22 || x == 25 || x == 31)
			y = y + 1;
		else if (x == 42 || x == 39 || x == 33)
			y = y - 1;
		else if (x <= 47 && x >= 44)
			y = y - 2;
		temp = y;
		for (y = 0; y < temp; y++)
		{
			circle[y][x][0] = 200;
			circle[y][x][1] = 200;
			circle[y][x][2] = 200;
			circle[y][x][3] = 255;
		}
		for (y = 64 - temp; y < 64; y++)
		{
			circle[y][x][0] = 200;
			circle[y][x][1] = 200;
			circle[y][x][2] = 200;
			circle[y][x][3] = 255;
		}
		y = temp;
	}
	for (i = 0; i < 61; i++)
	{
		for (y = i; y < 4 + i; y++)
		{
			for (x = i; x < 4 + i; x++)
			{
				circle[y][x][0] = 255;
				circle[y][x][1] = 255;
				circle[y][x][2] = 255;
				circle[y][x][3] = 255;
			}
		}
	}
	for (i = 0; i < 61; i++)
	{
		for (y = i; y < 4 + i; y++)
		{
			for (x = 60 - i; x < 64 - i; x++)
			{
				circle[y][x][0] = 255;
				circle[y][x][1] = 255;
				circle[y][x][2] = 255;
				circle[y][x][3] = 255;
			}
		}
	}
}
void Create_Texture_Waterwave()
{
	int x, y, i;

	for (x = 0; x < 64; x++)
		for (y = 0; y < 32; y++)
		{
			waterwave[x][y][0] = 0;
			waterwave[x][y][1] = 100;
			waterwave[x][y][2] = 255;
			waterwave[x][y][3] = 255;
		}

	x = 0;	y = 4;
	while (y <= 28)
	{
		for (i = x; i < 32; i++)
		{
			waterwave[i][y][0] = 200;
			waterwave[i][y][1] = 255;
			waterwave[i][y][2] = 255;
			waterwave[i][y][3] = 255;
		}
		y++;
		if (y < 9)
			x += 3;
		else if (y == 9)
			x++;
		else if (y == 10)
			x += 2;
		else if (y == 11)
			x++;
		else if (y == 12)
			x += 2;
		else if (y == 13)
			x++;
		else if (y == 14)
			x += 2;
		else if (y == 16)
			x++;
		else if (y == 19)
			x++;
		else if (y == 21)
			x++;
		else if (y == 23)
			x++;
		else if (y == 26)
			x++;
		else
			x++;
	}
	x = 0;	y = 0;
	while (y <= 24)
	{
		for (i = x; i < 32; i++)
		{
			waterwave[i][y][0] = 0;
			waterwave[i][y][1] = 100;
			waterwave[i][y][2] = 255;
			waterwave[i][y][3] = 255;
		}
		y++;
		if (y < 5)
			x += 3;
		else if (y == 5)
			x++;
		else if (y == 6)
			x += 2;
		else if (y == 7)
			x++;
		else if (y == 8)
			x += 2;
		else if (y == 9)
			x++;
		else if (y == 10)
			x += 2;
		else if (y == 11)
			x++;
		else if (y == 14)
			x++;
		else if (y == 16)
			x++;
		else if (y == 18)
			x++;
		else if (y == 21)
			x++;
		else
			x++;
	}

	for (x = 63; x > 31; x--)
		for (y = 0; y < 32; y++)
			for (i = 0; i < 4; i++)
				waterwave[x][y][i] = waterwave[63 - x][y][i];

	for (y = 32; y < 64; y++)
		for (x = 0; x < 64; x++)
			for (i = 0; i < 4; i++)
			{
				if (x >= 47)
					waterwave[x][y][i] = waterwave[x - 47][y - 32][i];
				else
					waterwave[x][y][i] = waterwave[x + 16][y - 32][i];
			}
}
void Create_Texture_Land()
{
	int x, y, i;

	for (y = 0; y < 32; y++)
		for (x = 0; x < 32; x++)
		{
			land[x][y][0] = 240;
			land[x][y][1] = 240;
			land[x][y][2] = 240;
			land[x][y][3] = 255;
		}


	for (x = 24; x < 32; x++)
	{
		land[x][0][0] = 255;
		land[x][0][1] = 200;
		land[x][0][2] = 200;
		land[x][0][3] = 255;

		land[0][x][0] = 255;
		land[0][x][1] = 200;
		land[0][x][2] = 200;
		land[0][x][3] = 255;
	}
	for (x = 26; x < 32; x++)
	{
		land[x][1][0] = 255;
		land[x][1][1] = 200;
		land[x][1][2] = 200;
		land[x][1][3] = 255;

		land[1][x][0] = 255;
		land[1][x][1] = 200;
		land[1][x][2] = 200;
		land[1][x][3] = 255;
	}
	for (x = 27; x < 32; x++)
	{
		for (y = 2; y < 4; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 28; x < 32; x++)
	{
		for (y = 4; y < 7; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 29; x < 32; x++)
	{
		for (y = 7; y < 9; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 30; x < 32; x++)
	{
		for (y = 9; y < 12; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 31; x < 32; x++)
	{
		for (y = 12; y < 16; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}

	for (y = 16; y < 32; y++)
		for (x = 16; x < 32; x++)
		{
			land[x][y][0] = 200;
			land[x][y][1] = 160;
			land[x][y][2] = 255;
			land[x][y][3] = 255;
		}
	for (y = 20; y < 32; y++)
		for (x = 20; x < 32; x++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 255;
			land[x][y][3] = 255;
		}

	for (x = 63; x > 31; x--)
	{
		for (y = 0; y < 32; y++)
			for (i = 0; i < 4; i++)
				land[x][y][i] = land[63 - x][y][i];
	}

	/* Create the rest half part */
	for (y = 32; y < 64; y++)
		for (x = 0; x < 64; x++)
			for (i = 0; i < 4; i++)
				land[x][y][i] = land[x][63 - y][i];
}
void Create_Texture_Star()
{
	int x, y, i;

	for (x = 0; x < 64; x++)
		for (y = 0; y < 64; y++)
		{
			star[x][y][0] = 255;
			star[x][y][1] = 255;
			star[x][y][2] = 255;
			star[x][y][3] = 255;
		}

	x = 31;	y = 60;
	while (x >= 12)
	{
		for (i = y; i > 4; i--)
		{
			star[x][i][0] = 100;
			star[x][i][1] = 100;
			star[x][i][2] = 255;
			star[x][i][3] = 255;
		}
		y -= 3;
		x--;
	}
	x = 31;	y = 20;
	while (x >= 12)
	{
		for (i = y; i > 4; i--)
		{
			star[x][i][0] = 255;
			star[x][i][1] = 255;
			star[x][i][2] = 255;
			star[x][i][3] = 255;
		}
		y -= 1;
		x--;
	}
	x = 4;	y = 40;
	while (y >= 18)
	{
		for (i = x; i < 32; i++)
		{
			star[i][y][0] = 100;
			star[i][y][1] = 100;
			star[i][y][2] = 255;
			star[i][y][3] = 255;
		}
		y -= 1;
		if ((y % 2) == 1)
			x += 2;
		else
			x++;
	}

	for (x = 63; x > 31; x--)
		for (y = 0; y < 64; y++)
			for (i = 0; i < 4; i++)
				star[x][y][i] = star[63 - x][y][i];
}
void Draw_UnitCube(int index)
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, TextureID[index]);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < 6; i++)
	{
		glNormal3fv(normal[i]);
		glColor3dv(color[i]);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(vertex[face_[i][0]]);
		glTexCoord2f(0.0, 8.0);
		glVertex3fv(vertex[face_[i][1]]);
		glTexCoord2f(8.0, 8.0);
		glVertex3fv(vertex[face_[i][2]]);
		glTexCoord2f(8.0, 0.0);
		glVertex3fv(vertex[face_[i][3]]);
		glEnd();
	}
}
// Procedure to initialize the working environment.
void make_check()
{
	int   i, j, c;

	for (i = 0; i < TSIZE; i++)
		for (j = 0; j < TSIZE; j++) {
			if (j > i / 2 && j <= 64 - i / 2) 
				c = 255;
			else c = 0;
			checkboard[i][j][0] = c / 8;
			checkboard[i][j][1] = c / 2;
			checkboard[i][j][2] = c / 4;
			if (c == 255) 

				checkboard[i][j][3] = 255;
			else 
				checkboard[i][j][3] = 0;
		}
	//Generate trunk
	for (i = 0; i < TSIZE / 3; i++) 
	{
		for (j = 0; j < TSIZE / 2 - 4; j++) 
			checkboard[i][j][3] = 0;
		for (j = TSIZE / 2 + 4; j < TSIZE; j++) 
			checkboard[i][j][3] = 0;
	}
}
void brick_pattern()
{
	int  y, x, i;

	for (y = 0; y < 12; y++) {    /*----Create the first row of bricks----*/
		for (x = 0; x < 2; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 2; x < 30; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 30; x < 34; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 34; x < 62; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 62; x < 64; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}
	}

	for (y = 12; y < 16; y++)     /*--Create the cement between two breick layers */
		for (x = 0; x < 64; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

	for (y = 16; y < 28; y++) {    /*--Create the 2nd layer of bricks---*/
		for (x = 0; x < 14; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 14; x < 18; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 18; x < 46; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 46; x < 50; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 50; x < 64; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}
	}

	for (y = 28; y < 32; y++) /*---Add another layer of cement----*/
		for (x = 0; x < 64; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

	for (y = 32; y < 64; y++)
		for (x = 0; x < 64; x++)
			for (i = 0; i < 4; i++) brick[y][x][i] = brick[y - 32][x][i];
}
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);      // set the background color BLACK
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Depth & Color Buffers

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);  // Enable depth buffer for shading computing
	glEnable(GL_NORMALIZE);

	// Enable lighting effects
	glEnable(GL_LIGHTING);

	// Define light0
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);

	// Define light1
	glEnable(GL_LIGHT1);      // Turn on light1 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lit_specular);

	// Define some global lighting status
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glViewport(0, 0, 499, 499);

	// Create Texture One
	make_check();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(2, textName);
	glBindTexture(GL_TEXTURE_2D, textName[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkboard);

	// Create Texture Two
	brick_pattern();

	glBindTexture(GL_TEXTURE_2D, textName[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TSIZE, TSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, brick);


	Create_Texture_Circle();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, TextureID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, circle);

	Create_Texture_Star();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, TextureID[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, star);

	Create_Texture_Land();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, land);

	Create_Texture_Waterwave();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, TextureID[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, waterwave);

	// Set up fog conditions
	glFogi(GL_FOG_MODE, GL_LINEAR);   // fog factor=GL_LINEAR,GL_EXP,or GL_EXP2
	glFogf(GL_FOG_DENSITY, 0.1);      // fog opacity(density)= 0.1
	glFogf(GL_FOG_START, 1.0);        // Setup two ends for GL_LINEAR
	glFogf(GL_FOG_END, 36.0);
	glFogfv(GL_FOG_COLOR, fog_color); // set the fog color

	if (sphere == NULL)
	{
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricNormals(sphere, GLU_SMOOTH);
	}
	if (cylind == NULL)
	{
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	if (disk == NULL)
	{
		disk = gluNewQuadric();
		gluQuadricDrawStyle(disk, GLU_FILL);
		gluQuadricNormals(disk, GLU_SMOOTH);
	}
}
void compute_ab_axes(void)
{
	float  w0, w2;
	double len;

	/*----Get w0 and w2 from the modelview matrix mtx[] ---*/
	w0 = mtx[2]; w2 = mtx[10];

	len = sqrt(w0 * w0 + w2 * w2);
	/*---- Define the a and b axes for billboards ----*/
	b[0] = 0.0; b[1] = 1.0; b[2] = 0.0;
	a[0] = w2 / len; a[1] = 0.0; a[2] = -w0 / len;
}
void draw_billboard(float x, float z, float w, float h)
{
	float  v0[3], v1[3], v2[3], v3[3];

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Compute the 4 vertices of the billboard
	v0[0] = x - (w / 2) * a[0]; v0[1] = 0.0; v0[2] = z - (w / 2) * a[2];
	v1[0] = x + (w / 2) * a[0]; v1[1] = 0.0; v1[2] = z + (w / 2) * a[2];
	v2[0] = x + (w / 2) * a[0]; v2[1] = h; v2[2] = z + (w / 2) * a[2];
	v3[0] = x - (w / 2) * a[0]; v3[1] = h; v3[2] = z - (w / 2) * a[2];

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3fv(v0);
	glTexCoord2f(1.0, 0.0); glVertex3fv(v1);
	glTexCoord2f(1.0, 1.0); glVertex3fv(v2);
	glTexCoord2f(0.0, 1.0); glVertex3fv(v3);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
}

void sun()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Define the current eye position and the eye-coordinate system
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(head, 0.0, 1.0, 0.0);    // Transformation in Eye coord. sys
	glRotatef(roll, 0.0, .0, 1.0);
	glRotatef(Epitch, 1.0, 0.0, 0.0);
	glTranslatef(0.0, up, 0.0);
	glTranslatef(-right, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -zoom);

	// Draw the Directional light -------------
	glLightfv(GL_LIGHT1, GL_POSITION, lit1_position);  // fixed position in eye space
	glTranslatef(-0.5, 1.0, -2.0);
	glDisable(GL_LIGHTING);
	glColor3f(0.80, 0.80, 0.0);
	glutSolidSphere(0.3, 12, 12);
}
void make_view(int x)
{
	sun();

	switch (x)
	{
	case 1:       // X direction parallel viewing
		gluLookAt(eyeDx, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 2:       // Y direction parallel viewing
		gluLookAt(0.0, eyeDy, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
		break;
	case 3:	      // z direction parallel viewing
		gluLookAt(0.0, 0.0, eyeDz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		break;
	case 4:       // Perspective
		gluLookAt(32.0, 13.0, 20.0, 4.0, 4.0, 0.0, 0.0, 1.0, 0.0);
		break;
	}
}
void make_projection(int x)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (x == 4)
		gluPerspective(90.0, (double)width / (double)height, 1.5, 50.0);
	else
		glOrtho(-40.0, 40.0, -40.0 * (float)height / (float)width, 40.0 * (float)height / (float)width,
			-0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void my_reshape(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)w / (double)h, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void draw_cube()
{
	int    i;
	float  range;

	for (i = 0; i < 6; i++) {     /* draw the six faces one by one */
		range = 1.0;
		glNormal3fv(normal[i]);
		glBegin(GL_POLYGON);  /* Draw the face */
		glTexCoord2f(0.0, 0.0); glVertex3fv(points[face[i][0]]);
		glTexCoord2f(0.0, range); glVertex3fv(points[face[i][1]]);
		glTexCoord2f(range, range); glVertex3fv(points[face[i][2]]);
		glTexCoord2f(range, 0.0); glVertex3fv(points[face[i][3]]);
		glEnd();
	}
}
void draw_obstacles()
{
	int    i;
	float  range;
	glPushMatrix();
	// obstacle's texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, TextureID[0]); // textName 裡面的數字會更改Texture
	// Obstacles 1
	glPushMatrix();
	glTranslatef(38, 1, -5);
	glRotatef(-40, 0, 1, 0);
	glScalef(2, 3, 40);
	draw_cube();
	glPopMatrix();

	// obstacle's texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, TextureID[0]); // textName 裡面的數字會更改Texture
	// Obstacles 2
	glPushMatrix();
	glTranslatef(10, 1, 25);
	glRotatef(-130, 0, 1, 0);
	glScalef(2, 3, 25);
	draw_cube();
	glPopMatrix();

}

void display()
{
	int   i, j;

	// Animate textures
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glRotatef(textAng, 0, 0, 1);
	glTranslatef(ds, dt, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	// Draw the POINT light---------------
	glPushMatrix();
	glTranslatef(16.0, 0.0, 16.0);          // Move to [8, 0, 8]
	glPushMatrix();
	glTranslatef(lit2_position[0], lit2_position[1], lit2_position[2]);
	glColor3f(1.0, 1.0, 1.0);
	glutWireSphere(0.5, 2, 2);
	glPopMatrix();

	glEnable(GL_LIGHTING);      // Turn on lighting
	glLightfv(GL_LIGHT2, GL_POSITION, lit2_position);  // Redefine position and direction of light2
	glLightfv(GL_LIGHT2, GL_AMBIENT, lit2_AMBIENT);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lit2_DIFFUSE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lit2_SPECULAR);
	glPopMatrix();

	//-----------------------------------------------------------------------------------------------------------------
	// On/Off Texture Mapping
	if (flag_texture % 2 == 0)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);

	// Draw the floor
	glMaterialfv(GL_FRONT, GL_DIFFUSE, flr_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, flr_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, flr_ambient);

	glBindTexture(GL_TEXTURE_2D, textName[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (i = -35; i < 35; i++) {
		for (j = -35; j < 35; j++) {
			glNormal3f(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(i * 4.0 + 0.0, 0.0, j * 4.0 + 0.0);
			glTexCoord2f(4.0, 0.0);
			glVertex3f(i * 4.0 + 0.0, 0.0, j * 4.0 + 4.0);
			glTexCoord2f(4.0, 4.0);
			glVertex3f(i * 4.0 + 4.0, 0.0, j * 4.0 + 4.0);
			glTexCoord2f(0.0, 4.0);
			glVertex3f(i * 4.0 + 4.0, 0.0, j * 4.0 + 0.0);
			glEnd();
		}
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, obstacle_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obstacle_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obstacle_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, obstacle_shininess);

	// BillBoard
	glGetFloatv(GL_MODELVIEW_MATRIX, mtx);
	compute_ab_axes();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, lit2_DIFFUSE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textName[0]);

	draw_billboard(-2.0 * 4.0, 3.0 * 4.0, 5.0, 8.0);
	draw_billboard(6.0 * 4.0, 5.0 * 4.0, 5.0, 8.0);
	draw_billboard(5.0 * 4.0, -1.0 * 4.0, 5.0, 8.0);
	draw_billboard(-3.0 * 4.0, 6.0 * 4.0, 5.0, 8.0);
	draw_billboard(2.0 * 4.0, 3.0 * 4.0, 5.0, 8.0);
	draw_billboard(4.0 * 4.0, -6.0 * 4.0, 5.0, 8.0);
	draw_billboard(6.0 * 4.0, -6.0 * 4.0, 5.0, 8.0);
	draw_billboard(6.0 * 4.0, -4.0 * 4.0, 5.0, 8.0);
	draw_billboard(3.0 * 4.0, -2.0 * 4.0, 5.0, 8.0);

	// obstacles
	draw_obstacles();
	glPopMatrix();

	// Define robot material properties
	if (countRobotMa % 3 == 0)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, robot_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robot_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robot_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, robot_shininess);
	}
	else if (countRobotMa % 3 == 1)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, robot1_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robot1_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robot1_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, robot1_shininess);
	}
	else if (countRobotMa % 3 == 2)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, robot2_ambient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, robot2_specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, robot2_diffuse);
		glMaterialf(GL_FRONT, GL_SHININESS, robot2_shininess);
	}

	if (countRobotEmi % 2 == 0)
		robotEmission[1] = 0.0;
	else if (countRobotEmi % 2 == 1)
		robotEmission[1] = 0.05;
	glMaterialfv(GL_FRONT, GL_EMISSION, robotEmission);

	// Robot's Texture
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, TextureID[1]); // textName 裡面的數字會更改Texture

	// Draw the legs
	glPushMatrix();						// initial coordinate system 
	glPushMatrix();						// initial coordinate system 
	glPushMatrix();						// initial coordinate system  

	glTranslatef(position[0], position[1] - 2, position[2] + 1);
	glRotatef(self_ang, 0, 1, 0);
	gluSphere(sphere, 1, 7, 7);
	glPushMatrix();	                    // right Knee coordinate system 
	glTranslatef(0, -1, 0);
	glRotatef(knee_ang_small, 0, 0, 1);
	glScalef(1, 2, 1);
	draw_cube();						// right small legs
	glPopMatrix();                      // Knee coordinate system 
	glTranslatef(0, 1, 0);
	glRotatef(knee_ang_big, 0, 0, 1);
	glScalef(1, 2, 1);
	draw_cube();						// right big legs

	glPopMatrix();					    // initial coordinate system
	glTranslatef(position[0], position[1] - 2, position[2] - 1);
	glRotatef(self_ang, 0, 1, 0);
	gluSphere(sphere, 1, 7, 7);
	glPushMatrix();	                    // left Knee coordinate system 
	glTranslatef(0, -1, 0);
	glRotatef(knee_ang_small, 0, 0, 1);
	glScalef(1, 2, 1);
	draw_cube();						// left small legs
	glPopMatrix();                      // left Knee coordinate system 
	glTranslatef(0, 1, 0);
	glRotatef(knee_ang_big, 0, 0, 1);
	glScalef(1, 2, 1);
	draw_cube();						// left big legs


	// Draw the robot body which is a cube
	glPopMatrix();					   // initial coordinate system  
	glTranslatef(position[0], position[1] + 2, position[2]);
	glRotatef(self_ang, 0.0, 1.0, 0.0);
	glScalef(5, 4, 5);
	draw_cube();

	// Draw the SPOT LIGHT 
	glTranslatef(0.2, 1.1, 0);
	glRotatef(lit_angle+90, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(0.2, 8, 8);
	glEnable(GL_LIGHTING);							  // Turn on lighting
	glLightfv(GL_LIGHT0, GL_POSITION, lit_position);  // Redefine position and direction of light0
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lit2_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lit_cutoff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, lit_exponent);

	// Draw the head
	glPopMatrix();					   // initial coordinate system  
	glTranslatef(position[0], position[1] + 5, position[2]);
	glRotatef(self_ang, 0.0, 1.0, 0.0);
	glPushMatrix();                    // head coordinate system 
	glPushMatrix();                    // head coordinate system 
	glScalef(3, 2, 3);
	draw_cube();

	// Draw the hands
	glPopMatrix();					   // head coordinate system 
	glColor3f(0.6, 0.6, 0);
	glTranslatef(0, -2.5, 2.5);
	gluSphere(sphere, 0.3, 7, 7);
	glPushMatrix();	                   // hand swing coordinate system                           
	glColor3f(0.0, 0.6, 0.6);
	glPopMatrix();	                   // hand swing coordinate system
	glRotatef(swing_ang, 0.0, 0.0, 1.0);
	glTranslatef(0, -1.0, 0);
	glScalef(1, 2, 2);
	gluCylinder(cylind, 0.5, 0.5, 0.5, 26, 3);

	glPopMatrix();                     // head coordinate system 
	glColor3f(0.6, 0.6, 0);
	glTranslatef(0, -2.5, -2.5);
	gluSphere(sphere, 0.3, 7, 7);
	glPushMatrix();	                   // hand swing coordinate system                           
	glColor3f(0.0, 0.6, 0.6);
	glPopMatrix();	                   // hand swing coordinate system 
	glRotatef(swing_ang, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, -1.0);
	glScalef(1, 2, 2);
	gluCylinder(cylind, 0.5, 0.5, 0.5, 26, 3);

	glDisable(GL_TEXTURE_2D);
	// Swap the back buffer to the front
	glutSwapBuffers();
	glFlush(); // Display the results
}

// Display callback procedure to draw the scene
void display_()
{
	// Drawing style  5:4-windows, 4:perspective, 3:z direction, 2:y direction, 1:x-dirtection
	switch (style)
	{
	case 5:
		glViewport(width / 2, 0, width / 2, height / 2);
		make_view(4);
		make_projection(4);
		display();

		glViewport(0, height / 2, width / 2, height / 2);
		make_view(1);
		make_projection(1);
		display();
		//make_view(1);

		glViewport(0, 0, width / 2, height / 2);
		make_view(3);
		display();

		glViewport(width / 2, height / 2, width / 2, height / 2);
		make_view(2);
		display();
		//make_view(2);

		//make_view(3);
		break;

	case 4:
		glViewport(0, 0, width, height);
		make_view(4);
		make_projection(4);
		display();
		break;

	case 3:
		glViewport(0, 0, width, height);
		make_view(3);
		make_projection(1);
		display();
		break;

	case 2:
		glViewport(0, 0, width, height);
		make_view(2);
		make_projection(1);
		display();
		break;

	case 1:
		glViewport(0, 0, width, height);
		make_view(1);
		make_projection(1);
		display();
		break;
	}
	//glutSwapBuffers();		// Swap the back buffer to the front
	return;
}

//  Keyboard callback func. When a 'q' key is pressed, exit.
void key_func(unsigned char key, int x, int y)
{
	float tmpFogColor[] = { 0.15, 0.20, 0.20, 0.50 };

	if (key == '`' || key == '~')
		exit(0);
	if (key == 'r' || key == 'R')
		head = roll = Epitch = Wpitch = up = right = zoom = ds = dt = textAng = 0.0, lit_cutoff = 37.0, lit_exponent = 4.0, lit1_position[0] = 10;
	if (key == 'q')
		lit_exponent += 0.5;
	if (key == 'e')
		lit_exponent -= 0.5;
	if (key == 't')
		lit_cutoff += 0.5;
	if (key == 'y')
		lit_cutoff -= 0.5;
	// Rotate light position
	if (key == ' ')
		lit_angle += 5.0;
	if (key == 'u')
		lit1_position[0] += 0.5;
	if (key == 'i')
		lit1_position[0] -= 0.5;
	// On/off Robot Emission
	if (key == 'o')
		countRobotEmi++;
	// Change Robot Material
	if (key == 'p')
		countRobotMa++;
	// Walking
	if (key == 'w')
	{
		position[0] += Step * cos(self_ang * PI / 180.0);
		position[2] -= Step * sin(self_ang * PI / 180.0);
	}
	// move car back b-key
	else if (key == 's')
	{
		position[0] -= Step * cos(self_ang * PI / 180.0);
		position[2] += Step * sin(self_ang * PI / 180.0);
	}
	// make a left turn
	else if (key == 'a')
	{
		self_ang += 10.0;
		if (self_ang > 360.0)
			self_ang -= 360.0;
	}
	// make a right turn
	else if (key == 'd')
	{
		self_ang += -10.0;
		if (self_ang < 0.0)
			self_ang += 360.0;
	}

	if (key == 'n' || key == 'N')
		right += 0.5;
	else if (key == 'b' || key == 'B')
		right -= 0.5;
	if (key == 'x' || key == 'X')
		up += 0.5;
	else if (key == 'z' || key == 'Z')
		up -= 0.5;
	if (key == 'c' || key == 'C')
		zoom -= 0.5;
	else if (key == 'v' || key == 'V')
		zoom += 0.5;

	if (key == 'g')
		Epitch += 10.0;
	else if (key == 'f')
		Epitch -= 10.0;
	if (key == 'j')
		head += 10.0;
	else if (key == 'h')
		head -= 10.0;
	if (key == 'k')
		roll += 10.0;
	else if (key == 'l')
		roll -= 10.0;

	if (key == '1')
		countSun ++;
	if (key == '2')
		countPoint ++;
	if (key == '3')
		countSpot ++;
	if (key == '4')
		countFogMode++;
	if (key == '5')
		flag_texture++;
	if (key == '6')
		style = 1;
	if (key == '7')
		style = 2;
	if (key == '8')
		style = 3;
	if (key == '9')
		style = 4;
	if (key == '0')
		style = 5;

	if (key == 'm' or key == 'M')
		flag_fogColor++;
	if (flag_fogColor % 2 == 0)
		fog_color[0] = 0.3, fog_color[1] = 0.3, fog_color[2] = 0.6, fog_color[3] = 0.5;
	else
		fog_color[0] = 0.01, fog_color[1] = 0.01, fog_color[2] = 0.01, fog_color[3] = 0.20;
	glFogfv(GL_FOG_COLOR, fog_color);

	if (key == ',') 
	{
		textAng += 1.0;
		if (textAng > 360.0) 
			textAng -= 360.0;
	}
	if (key == '.')
		ds += 2.0;
	if (key == '/')
		dt += 2.0;

	if (countSun % 2 == 0)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	if (countPoint % 2 == 0)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
	if (countSpot % 2 == 0)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);

	if (countFogMode % 4 == 0)
		glDisable(GL_FOG);
	else
	{
		glEnable(GL_FOG);
		if (countFogMode % 4 == 1)
			glFogi(GL_FOG_MODE, GL_LINEAR);
		else if (countFogMode % 4 == 2)
			glFogi(GL_FOG_MODE, GL_EXP);
		else if (countFogMode % 4 == 3)
			glFogi(GL_FOG_MODE, GL_EXP2);
	}

	display_();
}