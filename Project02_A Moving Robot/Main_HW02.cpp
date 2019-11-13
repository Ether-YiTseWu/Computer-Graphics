# include <stdio.h>
# include <math.h>
# include <GL/glut.h>

# include "func.h"

int width = 1300, height = 800;	// Define window size

// Reshape callback function which defines the size of the main window when a reshape event occurrs.
void reshape(int w, int h)
{
	width = w;
	height = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w > h)
		glOrtho(-40.0, 40.0, -40.0 * (float)h / (float)w, 40.0 * (float)h / (float)w,
			-100.0, 100.0);
	else
		glOrtho(-40.0 * (float)w / (float)h, 40.0 * (float)w / (float)h, -40.0, 40.0,
			-100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main procedure which defines the graphics environment, the operation style, and the callback func's.
void main(int argc, char** argv)
{
	glutInit(&argc, argv);		    // Initialize the GLUT environment
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Depth buffer is used, be careful !!!
	glutInitWindowSize(width, height);
	glutCreateWindow("windmill");
	myinit();					    // Initialize other state varibales

	glutDisplayFunc(draw_background);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(move_control);
	glutMainLoop();
}
