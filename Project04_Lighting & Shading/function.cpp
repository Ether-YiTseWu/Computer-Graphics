#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>

#include "parameter.h"

#define CRT_SECURE_NO_WARNINGS
GLUquadricObj* sphere = NULL, * cylind = NULL, * disk;
int style = 4;	// 4-windows mode

// Procedure to initialize the working environment.
void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);      // set the background color BLACK
					 /*Clear the Depth & Color Buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);  /*Enable depth buffer for shading computing */

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

	glEnable(GL_NORMALIZE);   /*Enable mornalization  */

	glEnable(GL_LIGHTING);    /*Enable lighting effects */
	glEnable(GL_LIGHT0);      /*Turn on light0 */
	glEnable(GL_LIGHT1);      /*Turn on light1 */
	/*-----Define light0 ---------*/
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);

	/*-----Define light1 ---------*/
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lit_specular);


	/*-----Define some global lighting status -----*/
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); /* local viewer */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); /*global ambient*/

	/*-----Enable face culling -----*/
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
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
	/* In this sample program, eye position and Xe, Ye, Ze are computed
	   by ourselves. Therefore, use them directly; no trabsform is
	   applied upon eye coordinate system	*/
		gluLookAt(30.0, 13.0, 20.0, 4.0, 4.0, 0.0, 0.0, 1.0, 0.0);  // Define Viewing Matrix
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

	for (i = 0; i < 6; i++) {     // draw the six faces one by one
		range = 1.0;
		glNormal3fv(normal[i]);
		glBegin(GL_POLYGON);  // Draw the face
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
}
void draw_obstacles()
{
	int    i;
	float  range;

	// Obstacles 1
	glPushMatrix();
	glTranslatef(38, 1, -5);
	glRotatef(-40, 0, 1, 0);
	glScalef(2, 3, 40);
	for (int i = 0; i < 6; i++)
	{
		range = 1.0;
		glNormal3fv(normal[i]);
		glBegin(GL_POLYGON);
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
	glPopMatrix();
	// Obstacles 2
	glPushMatrix();
	glTranslatef(10, 1, 25);
	glRotatef(-130, 0, 1, 0);
	glScalef(2, 3, 25);
	for (int i = 0; i < 6; i++)
	{
		range = 1.0;
		glNormal3fv(normal[i]);
		glBegin(GL_POLYGON);
		glVertex3fv(points[face[i][0]]);
		glVertex3fv(points[face[i][1]]);
		glVertex3fv(points[face[i][2]]);
		glVertex3fv(points[face[i][3]]);
		glEnd();
	}
	glPopMatrix();
}

void display()
{
	int   i, j;

	//gluLookAt(30.0, 13.0, 20.0, 4.0, 4.0, 0.0, 0.0, 1.0, 0.0);  // Define Viewing Matrix

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
	// Draw the floor
	glMaterialfv(GL_FRONT, GL_DIFFUSE, flr_diffuse);  // diffuse color
	glMaterialfv(GL_FRONT, GL_SPECULAR, flr_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, flr_ambient);
	glNormal3f(0.0, 1.0, 0.0);
	for (i = -35; i <= 35; i++) {
		for (j = -35; j <= 35; j++) {
			glBegin(GL_POLYGON);
			glVertex3f(i * 2.0 + 0.0, 0.0, j * 2.0 + 0.0);
			glVertex3f(i * 2.0 + 0.0, 0.0, j * 2.0 + 2.0);
			glVertex3f(i * 2.0 + 2.0, 0.0, j * 2.0 + 2.0);
			glVertex3f(i * 2.0 + 2.0, 0.0, j * 2.0 + 0.0);
			glEnd();
		}
	}

	// obstacles
	glPushMatrix();
	//glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, obstacle_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obstacle_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obstacle_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, obstacle_shininess);
	glNormal3f(0.0, 1.0, 0.0);
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

	// Swap the back buffer to the front
	glutSwapBuffers();
	glFlush(); // Display the results
}

// Display callback procedure to draw the scene
void display_()
{
	// Clear previous frame and the depth buffer
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		make_view(1);

		glViewport(width / 2, height / 2, width / 2, height / 2);
		make_view(2);
		display();
		make_view(2);

		glViewport(0, 0, width / 2, height / 2);
		make_view(3);
		display();
		make_view(3);
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
	if (key == '`' || key == '~')
		exit(0);
	if (key == 'r' || key == 'R')
		head = roll = Epitch = Wpitch = up = right = zoom = 0.0, lit_cutoff = 37.0, lit_exponent = 4.0, lit1_position[0] = 10;
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
		countPointColor++;
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
	if (countPointColor % 2 == 0)
		for (int i = 0; i < 3; i++)
			lit2_DIFFUSE[i] = 1;
	else
		lit2_DIFFUSE[0] = 0;
	
	if (key == '5')
	{
		lit2_DIFFUSE[0] = 1, lit2_DIFFUSE[1] = lit2_DIFFUSE[2] = 0;
		make_view(style);
		display_();
		Sleep(100);
		lit2_DIFFUSE[1] = 1, lit2_DIFFUSE[0] = lit2_DIFFUSE[2] = 0;
		make_view(style);
		display_();
		Sleep(100);
		lit2_DIFFUSE[2] = 1, lit2_DIFFUSE[0] = lit2_DIFFUSE[1] = 0;
		make_view(style);
		display_();
		Sleep(100);
		lit2_DIFFUSE[1] = 1, lit2_DIFFUSE[0] = lit2_DIFFUSE[2] = 0;
		make_view(style);
		display_();
		Sleep(100);
		lit2_DIFFUSE[0] = 1, lit2_DIFFUSE[1] = lit2_DIFFUSE[2] = 0;
		make_view(style);
		display_();
		Sleep(100);
		for (int i = 0; i < 3; i++)
			lit2_DIFFUSE[i] = 1;
	}

	display_();
}
// Main procedure which defines the graphics environment,