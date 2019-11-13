# include <stdio.h>
# include <math.h>
# include <GL/glut.h>

// Declare GLU quadric objects, sphere, cylinder, and disk
extern GLUquadricObj* sphere = NULL, * cylind = NULL, * disk = NULL;

void myinit()
{
	// Procedure to initialize the working environment.
	glClearColor(0.0, 0.0, 0.0, 1.0);				     // Set the background color BLACK
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the Depth & Color Buffers
	glEnable(GL_DEPTH_TEST);

	// Create quadratic objects
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

void draw_axes()
{
	// Draw a white sphere to represent the original
	glColor3f(0.9, 0.9, 0.9);
	gluSphere(sphere, 2.0, 12, 12);			// radius=2.0
											// composing of 12 slices
											// composing of 8 stacks

	// Draw three axes in colors, yellow, meginta, and cyan

	// Draw Z axis
	glColor3f(0.0, 0.95, 0.95);
	gluCylinder(cylind, 0.5, 0.5,     // radius of top and bottom circle 
		12.0,					      // height of the cylinder 
		12,                           // use 12-side polygon approximating circle
		3);                           // Divide it into 3 sections 
	glPushMatrix();

	// Draw Y axis
	glRotatef(-90.0, 1.0, 0.0, 0.0);  // Rotate about x by -90', z becomes y
	glColor3f(0.95, 0.0, 0.95);
	gluCylinder(cylind, 0.5, 0.5,     // radius of top and bottom circle
		7.0,                          // height of the cylinder
		12,                           // use 12-side polygon approximating circle
		3);                           // Divide it into 3 sections
	glPopMatrix();

	// Draw X axis 
	glColor3f(0.95, 0.95, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);   // Rotate about y  by 90', x becomes z
	gluCylinder(cylind, 0.5, 0.5,     // radius of top and bottom circle
		7.0,                          // height of the cylinder
		12,                           // use 12-side polygon approximating circle
		3);                           // Divide it into 3 sections

	glPopMatrix(); // Restore the original modelview matrix
}

void draw_floor()
{
	for (int i = -100; i < 81; i++)
		for (int j = -100; j < 81; j++)
		{
			if ((i + j) % 2 == 0)
				glColor3f(0.2, 0.2, 0.5);
			else
				glColor3f(0.1, 0.1, 0.4);

			glBegin(GL_POLYGON);
			glVertex3f(i + 5, -4, j + 5);
			glVertex3f(i + 5, -4, j + 4);
			glVertex3f(i + 4, -4, j + 4);
			glVertex3f(i + 4, -4, j + 5);
			glEnd();
		}
}