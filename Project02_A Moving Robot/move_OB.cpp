# include <stdio.h>
# include <math.h>
# include <GL/glut.h>
# include <math.h>

# include "func.h"
# include "vertices_OB.h"

float speed = 10.0, Step = 1.0;
bool  gesture_flag = 1, smallKnee_flag = 1, bigKnee_flag = 1, jump_flag = 1;

void draw_cube()
{
	// Procedure to draw a 1x1x1 cube. The cube is within (-0.5,-0.5,-0.5) ~ (0.5,0.5,0.5)
	for (int i = 0; i < 6; i++)
	{
		glColor3fv(colors[i]);            // Set color
		glBegin(GL_POLYGON);              // Draw the face
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
	glTranslatef(-32, -2.5, -20);
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
	glTranslatef(15, -2.5, 20);
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
	glTranslatef(position[0], position[1]-2, position[2] + 1);
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
	glTranslatef(position[0], position[1]-2, position[2] - 1);
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

// Keyboard callback func. When a 'q' key is pressed, the program is aborted.
void move_control(unsigned char key, int x, int y)
{
	float temp_swing = swing_ang, temp_knee_small = knee_ang_small, temp_knee_big = knee_ang_big;
	float temp_position[3] = { position[0],position[1],position[2] };

	if (key == '~' || key == '`')  // quit
		exit(0);

	if (key == 'q')          // swing hands
		swing_ang += speed;
	if (key == 'e')          // swing hands
		swing_ang -= speed;
	if (key == 'z')          // swing legs
		knee_ang_small += Step * 4;
	if (key == 'x')          // swing legs
		knee_ang_small -= Step * 4;
	if (key == 'c')          // swing legs
		knee_ang_big += Step * 4;
	if (key == 'v')          // swing legs
		knee_ang_big -= Step * 4;
	if (key == 's')
	{
		position[0] -= Step * cos(self_ang * PI / 180.0);      // 加三角函數是為了使之直線前進
		position[2] += Step * sin(self_ang * PI / 180.0);
	}
	if (key == 'w')
	{
		position[0] += Step * cos(self_ang * PI / 180.0);
		position[2] -= Step * sin(self_ang * PI / 180.0);
	}
	if (key == 'a')
		self_ang += speed;
	if (key == 'd')
		self_ang -= speed;
	if (key == 'r')
		swing_ang = knee_ang_small = knee_ang_big = position[1] = 0;
	if (key == 't')
		position[0] = -20, position[1] = 0, position[2] = 10;

	if (fabs(swing_ang) > 165)
		swing_ang = temp_swing;
	if (fabs(knee_ang_small) > 25)
		knee_ang_small = temp_knee_small;
	if (fabs(knee_ang_big) > 25)
		knee_ang_big = temp_knee_big;

	if (key == '1')
		speed = 5.0, Step = 0.5;   // slow speed mode
	if (key == '2')
		speed = 10.0, Step = 1.0;  // medium speed mode
	if (key == '3')
		speed = 15.0, Step = 1.5;  // high speed mode
	if (key == '4')                // gesture
	{
		self_ang += speed;         // rotate body
		if (swing_ang < 160 && gesture_flag)
			swing_ang += speed;    // swing hands
		else
		{
			gesture_flag = 0, swing_ang -= speed;
			if (swing_ang < -160)
				gesture_flag = 1;
		}

		if (knee_ang_small < 25 && smallKnee_flag)    // swing small legs
			knee_ang_small += Step * 4;
		else
		{
			smallKnee_flag = 0, knee_ang_small -= Step * 4;
			if (knee_ang_small < -25)
				smallKnee_flag = 1;
		}

		if (knee_ang_big > -25 && bigKnee_flag)       // swing big legs
			knee_ang_big -= Step * 4;
		else
		{
			bigKnee_flag = 0, knee_ang_big += Step * 4;
			if (knee_ang_big > 25)
				bigKnee_flag = 1;
		}
	}
	if (key == '5')                // gesture
	{
		self_ang -= speed;         // rotate body
		if (swing_ang < 160 && gesture_flag)
			swing_ang += speed;    // swing hands
		else
		{
			gesture_flag = 0, swing_ang -= speed;
			if (swing_ang < -160)
				gesture_flag = 1;
		}

		if (knee_ang_small < 25 && smallKnee_flag)   // swing small legs
			knee_ang_small += Step * 4;
		else
		{
			smallKnee_flag = 0, knee_ang_small -= Step * 4;
			if (knee_ang_small < -25)
				smallKnee_flag = 1;
		}

		if (knee_ang_big > -25 && bigKnee_flag)      // swing big legs
			knee_ang_big -= Step * 4;
		else
		{
			bigKnee_flag = 0, knee_ang_big += Step * 4;
			if (knee_ang_big > 25)
				bigKnee_flag = 1;
		}
	}

	if (key == ' ')									 // jump
	{
		// ensure the angle of knee is correct
		if (knee_ang_small != 0 && (knee_ang_small + knee_ang_big) == 0)
		{
			if (position[1] < 4.8 && jump_flag)
				position[1] += 0.4;
			else
			{
				jump_flag = 0, position[1] -= 0.4;
				if (position[1] < 0.4)
					jump_flag = 1;
			}
		}
	}
	if ((position[0] >= 8 && position[0] <= 18) && (position[1] >= 0 && position[1] <= 3) && (position[2] >= 6.5 && position[2] <= 34))
		for (int i = 0; i < 3; i++)
			position[i] = temp_position[i];
	if ((position[0] >= -53 && position[0] <= -10.5) && (position[1] >= 0 && position[1] <= 3) && (position[2] >= -22.3 && position[2] <= -17))
		for (int i = 0; i < 3; i++)
			position[i] = temp_position[i];

	draw_background();
}