#include "vertices_OB.h";
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Func.h"

#define Step  0.5
GLUquadricObj* sphere = NULL, * cylind = NULL, * disk;

float speed = 10.0;
int style = 5;	// 4-windows mode

// The following seven functions is the same as the functions in HW02
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);      // set the background color BLACK
										   // Clear the Depth & Color Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);	// Create quadratic objects
	if (sphere == NULL) {
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricNormals(sphere, GLU_SMOOTH);
	}
	if (cylind == NULL) {
		cylind = gluNewQuadric();
		gluQuadricDrawStyle(cylind, GLU_FILL);
		gluQuadricNormals(cylind, GLU_SMOOTH);
	}
	if (disk == NULL) {
		disk = gluNewQuadric();
		gluQuadricDrawStyle(disk, GLU_FILL);
		gluQuadricNormals(disk, GLU_SMOOTH);
	}

	// Compute cos(5.0) and sin(5.0)
	cv = cos(5.0 * PI / 180.0);
	sv = sin(5.0 * PI / 180.0);
	// Copy eye position
	eye[0] = Eye[0];
	eye[1] = Eye[1];
	eye[2] = Eye[2];
}
void draw_floor()
{
	int  i, j;

	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			if ((i + j) % 2 == 0) glColor3f(0.8, 0.8, 0.8);
			else glColor3f(0.2, 0.2, 0.4);
			glBegin(GL_POLYGON);
			glVertex3f((i - 5.0) * 10.0, -2.2, (j - 5.0) * 10.0);
			glVertex3f((i - 5.0) * 10.0, -2.2, (j - 4.0) * 10.0);
			glVertex3f((i - 4.0) * 10.0, -2.2, (j - 4.0) * 10.0);
			glVertex3f((i - 4.0) * 10.0, -2.2, (j - 5.0) * 10.0);
			glEnd();
		}
}
void draw_cube()
{
	int    i;

	for (i = 0; i < 6; i++) {
		glColor3fv(colors[i]);  /* Set color */
		glBegin(GL_POLYGON);  /* Draw the face */
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
}
void draw_obstacles()
{
	// Obstacles 1
	glPushMatrix();
	glTranslatef(-32, -0.5, -20);
	glRotatef(-90, 0, 1, 0);
	glScalef(2, 3, 40);
	for (int i = 0; i < 6; i++)
	{
		glColor3fv(colorsObstacles[i]);    // Set color
		glBegin(GL_POLYGON);               // Draw the face
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
	glPopMatrix();
	// Obstacles 2
	glPushMatrix();
	glTranslatef(15, -0.5, 20);
	glRotatef(-180, 0, 1, 0);
	glScalef(2, 3, 25);
	for (int i = 0; i < 6; i++)
	{
		glColor3fv(colorsObstacles[i]);   // Set color
		glBegin(GL_POLYGON);              // Draw the face
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
	glPopMatrix();
}
void draw_background()
{
	static float  ang_self = 0.0;  // Define the angle of self-rotate
	static float  angle = 0.0;
	GLUquadricObj* cyliner = gluNewQuadric(), * sphere = gluNewQuadric();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear previous frame and the depth buffer
	glMatrixMode(GL_MODELVIEW);		// Define the current eye position and the eye-coordinate system
	glLoadIdentity();
	gluLookAt(8.0, 5.0, 15.0, 4.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Draw the objects can't move
	draw_floor();
	draw_axes();
	draw_obstacles();

	// Draw the legs
	glPushMatrix();						// initial coordinate system 
	glPushMatrix();						// initial coordinate system 
	glPushMatrix();						// initial coordinate system  

	glColor3f(0.6, 0.6, 0);
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
	glColor3f(0.6, 0.6, 0);
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
	gluCylinder(cyliner, 0.5, 0.5, 0.5, 26, 3);

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
	gluCylinder(cyliner, 0.5, 0.5, 0.5, 26, 3);

	glutSwapBuffers();		           // Swap the back buffer to the front
	return;
}
void draw_axes()
{
	/*----Draw a white sphere to represent the original-----*/
	glColor3f(0.9, 0.9, 0.9);

	gluSphere(sphere, 2.0,   /* radius=2.0 */
		12,            /* composing of 12 slices*/
		12);           /* composing of 8 stacks */

  /*----Draw three axes in colors, yellow, meginta, and cyan--*/
  /* Draw Z axis  */
	glColor3f(0.0, 0.95, 0.95);
	gluCylinder(cylind, 0.5, 0.5, /* radius of top and bottom circle */
		10.0,              /* height of the cylinder */
		12,               /* use 12-side polygon approximating circle*/
		3);               /* Divide it into 3 sections */

/* Draw Y axis */
	glPushMatrix();
	glRotatef(-90.0, 1.0, 0.0, 0.0);  /*Rotate about x by -90', z becomes y */
	glColor3f(0.95, 0.0, 0.95);
	gluCylinder(cylind, 0.5, 0.5, /* radius of top and bottom circle */
		10.0,             /* height of the cylinder */
		12,               /* use 12-side polygon approximating circle*/
		3);               /* Divide it into 3 sections */
	glPopMatrix();

	/* Draw X axis */
	glColor3f(0.95, 0.95, 0.0);
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);  /*Rotate about y  by 90', x becomes z */
	gluCylinder(cylind, 0.5, 0.5,   /* radius of top and bottom circle */
		10.0,             /* height of the cylinder */
		12,               /* use 12-side polygon approximating circle*/
		3);               /* Divide it into 3 sections */
	glPopMatrix();
	/*-- Restore the original modelview matrix --*/
	glPopMatrix();
}
void draw_scene()
{

	static float  ang_self = 0.0;  // Define the angle of self-rotate
	static float  angle = 0.0;
	GLUquadricObj* cyliner = gluNewQuadric(), * sphere = gluNewQuadric();

	// Draw the objects can't move
	draw_floor();
	draw_axes();
	draw_obstacles();

	// Draw the legs
	glPushMatrix();						// initial coordinate system 
	glPushMatrix();						// initial coordinate system 
	glPushMatrix();						// initial coordinate system  

	glColor3f(0.6, 0.6, 0);
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
	glColor3f(0.6, 0.6, 0);
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
	gluCylinder(cyliner, 0.5, 0.5, 0.5, 26, 3);

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
	gluCylinder(cyliner, 0.5, 0.5, 0.5, 26, 3);

}



// Make viewing matrix
void make_view(int x)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
	/* In this sample program, eye position and Xe, Ye, Ze are computed
	   by ourselves. Therefore, use them directly; no trabsform is
	   applied upon eye coordinate system	*/
		gluLookAt(eye[0], eye[1], eye[2],
			eye[0] - u[2][0], eye[1] - u[2][1], eye[2] - u[2][2],
			u[1][0], u[1][1], u[1][2]);
		break;
	}
}

// Procedure to make projection matrix
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

// Procedure to draw view volume, eye position, focus ,...  for perspective projection
void draw_view()
{
	int    i;

	glMatrixMode(GL_MODELVIEW);

	// Draw Eye position
	glPushMatrix();
	glTranslatef(eye[0], eye[1], eye[2]);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(1.0, 10, 10);
	glPopMatrix();

	// Draw eye coord. axes
	glColor3f(1.0, 1.0, 0.0);           // Draw Xe
	glBegin(GL_LINES);
	glVertex3f(eye[0], eye[1], eye[2]);
	glVertex3f(eye[0] + 20.0 * u[0][0], eye[1] + 20.0 * u[0][1], eye[2] + 20.0 * u[0][2]);
	glEnd();

	glColor3f(1.0, 0.0, 1.0);           // Draw Ye
	glBegin(GL_LINES);
	glVertex3f(eye[0], eye[1], eye[2]);
	glVertex3f(eye[0] + 20.0 * u[1][0], eye[1] + 20.0 * u[1][1], eye[2] + 20.0 * u[1][2]);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);           // Draw Ze
	glBegin(GL_LINES);
	glVertex3f(eye[0], eye[1], eye[2]);
	glVertex3f(eye[0] + 20.0 * u[2][0], eye[1] + 20.0 * u[2][1], eye[2] + 20.0 * u[2][2]);
	glEnd();
}

// Display callback procedure to draw the scene
void display()
{
	// Clear previous frame and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Drawing style  5:4-windows, 4:perspective, 3:z direction, 2:y direction, 1:x-dirtection
	switch (style)
	{
	case 5:
		make_view(4);
		make_projection(4);
		glViewport(width / 2, 0, width / 2, height / 2);
		draw_scene();

		make_view(1);
		make_projection(1);
		glViewport(0, height / 2, width / 2, height / 2);
		draw_scene();
		make_view(1);
		draw_view();

		make_view(2);
		glViewport(width / 2, height / 2, width / 2, height / 2);
		draw_scene();
		make_view(2);
		draw_view();

		make_view(3);
		glViewport(0, 0, width / 2, height / 2);
		draw_scene();
		make_view(3);
		draw_view();
		break;

	case 4:
		glViewport(0, 0, width, height);
		make_view(4);
		make_projection(4);
		draw_scene();
		break;

	case 3:
		glViewport(0, 0, width, height);
		make_view(3);
		make_projection(1);
		draw_scene();
		break;

	case 2:
		glViewport(0, 0, width, height);
		make_view(2);
		make_projection(1);
		draw_scene();
		break;

	case 1:
		glViewport(0, 0, width, height);
		make_view(1);
		make_projection(1);
		draw_scene();
		break;
	}
	glutSwapBuffers();		// Swap the back buffer to the front
	return;

}

// Reshape callback function which defines the size of the main window when a reshape event occurrs.
void reshape(int w, int h)
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

void move_control(unsigned char key, int ix, int iy)
{
	int    i;
	float  x[3], y[3], z[3], temp_position[3] = { position[0],position[1],position[2] };

	// Control the car.
	if (key == '~' || key == '`')
		exit(0);

	// move car ahead, SPACE key
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

	// Zoom in / out
	else if (key == 't')
		eyeDx += 2.0;
	else if (key == 'y')
		eyeDx += -2.0;
	else if (key == 'u')
		eyeDy += 2.0;
	else if (key == 'i')
		eyeDy += -2.0;
	else if (key == 'o')
		eyeDz += 2.0;
	else if (key == 'p')
		eyeDz += -2.0;

	// transform the EYE coordinate system
	// move down
	else if (key == 'x') 
		for (i = 0; i < 3; i++) 
			eye[i] -= 0.5 * u[1][i];
	// move up
	else if (key == 'z') 
		for (i = 0; i < 3; i++) 
			eye[i] += 0.5 * u[1][i];
	// move right
	else if (key == 'n') 
		for (i = 0; i < 3; i++) 
			eye[i] += 0.5 * u[0][i];
	// move left
	else if (key == 'b') 
		for (i = 0; i < 3; i++) 
			eye[i] -= 0.5 * u[0][i];
	// zoom in
	else if (key == 'c')   
		for (i = 0; i < 3; i++) 
			eye[i] -= 0.5 * u[2][i];
	// zoom out
	else if (key == 'v')   
		for (i = 0; i < 3; i++) 
			eye[i] += 0.5 * u[2][i];
	// pitching
	else if (key == 'g') 
	{             
		y[0] = u[1][0] * cv - u[2][0] * sv;
		y[1] = u[1][1] * cv - u[2][1] * sv;
		y[2] = u[1][2] * cv - u[2][2] * sv;

		z[0] = u[2][0] * cv + u[1][0] * sv;
		z[1] = u[2][1] * cv + u[1][1] * sv;
		z[2] = u[2][2] * cv + u[1][2] * sv;

		for (i = 0; i < 3; i++) 
		{
			u[1][i] = y[i];
			u[2][i] = z[i];
		}
	}
	else if (key == 'f') 
	{
		y[0] = u[1][0] * cv + u[2][0] * sv;
		y[1] = u[1][1] * cv + u[2][1] * sv;
		y[2] = u[1][2] * cv + u[2][2] * sv;

		z[0] = u[2][0] * cv - u[1][0] * sv;
		z[1] = u[2][1] * cv - u[1][1] * sv;
		z[2] = u[2][2] * cv - u[1][2] * sv;

		for (i = 0; i < 3; i++) 
		{
			u[1][i] = y[i];
			u[2][i] = z[i];
		}
	}
	// heading
	else if (key == 'h') 
	{         
		for (i = 0; i < 3; i++) 
		{
			x[i] = cv * u[0][i] - sv * u[2][i];
			z[i] = sv * u[0][i] + cv * u[2][i];
		}
		for (i = 0; i < 3; i++) 
		{
			u[0][i] = x[i];
			u[2][i] = z[i];
		}
	}
	
	else if (key == 'j') 
	{
		for (i = 0; i < 3; i++) 
		{
			x[i] = cv * u[0][i] + sv * u[2][i];
			z[i] = -sv * u[0][i] + cv * u[2][i];
		}
		for (i = 0; i < 3; i++) 
		{
			u[0][i] = x[i];
			u[2][i] = z[i];
		}
	}
	// rolling
	else if (key == 'k') 
	{        
		for (i = 0; i < 3; i++) 
		{
			x[i] = cv * u[0][i] - sv * u[1][i];
			y[i] = sv * u[0][i] + cv * u[1][i];
		}
		for (i = 0; i < 3; i++) 
		{
			u[0][i] = x[i];
			u[1][i] = y[i];
		}
	}
	else if (key == 'l') 
	{
		for (i = 0; i < 3; i++) 
		{
			x[i] = cv * u[0][i] + sv * u[1][i];
			y[i] = -sv * u[0][i] + cv * u[1][i];
		}
		for (i = 0; i < 3; i++) 
		{
			u[0][i] = x[i];
			u[1][i] = y[i];
		}
	}
	else if (key == 'q')          // swing hands
		swing_ang += speed;
	else if (key == 'e')          // swing hands
		swing_ang -= speed;
	// ¦^´_­ìª¬
	else if (key == 'r')
	{
		eyeDx = eyeDy = eyeDz = 30.0;
		eye[0] = 0.0;
		eye[1] = 0.0;
		eye[2] = 30.0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if(i == j)
					u[i][j] = 1;
				else
					u[i][j] = 0;
			}
		}
	}
	else if (key == '1') 
		style = 1;
	else if (key == '2')
		style = 2;
	else if (key == '3')
		style = 3;
	else if (key == '4')
		style = 4;
	else if (key == '5')
		style = 5;

	if ((position[0] >= 11.5 && position[0] <= 17) && (position[1] >= 0 && position[1] <= 3) && (position[2] >= 6.5 && position[2] <= 34))
		for (int i = 0; i < 3; i++)
			position[i] = temp_position[i];
	if ((position[0] >= -53 && position[0] <= -10.5) && (position[1] >= 0 && position[1] <= 3) && (position[2] >= -22.3 && position[2] <= -17))
		for (int i = 0; i < 3; i++)
			position[i] = temp_position[i];
	display();
}