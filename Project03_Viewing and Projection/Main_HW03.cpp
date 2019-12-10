#include <GL/glut.h>
#include "Func.h"

void main(int argc, char** argv)
{
	int width = 800, height = 800;

	glutInit(&argc, argv);	// Initialize the GLUT environment

	// Depth buffer is used, be careful !!!
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(width, height);
	glutCreateWindow("windmill");

	myinit();					// Initialize other state varibales

	glutDisplayFunc(display);	// Associate callback func's whith events
	glutReshapeFunc(reshape);
	glutKeyboardFunc(move_control);

	glutMainLoop();
}