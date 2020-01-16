#include "function.h"

#include <GL/glut.h>

void main(int argc, char** argv)
{
	/*-----Initialize the GLUT environment-------*/
	glutInit(&argc, argv);

	/*-----Depth buffer is used, be careful !!!----*/
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 800);
	glutCreateWindow("cube");

	myinit();      /*---Initialize other state varibales----*/

	/*----Associate callback func's whith events------*/
	glutDisplayFunc(display);
	glutReshapeFunc(my_reshape);
	glutKeyboardFunc(key_func);

	glutMainLoop();
}
