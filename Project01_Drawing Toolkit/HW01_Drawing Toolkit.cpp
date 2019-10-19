#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define    SIZEX   1300
#define    SIZEY   800

#define    MY_QUIT -1
#define    MY_CLEAR -2
#define    MY_SAVE -3
#define    MY_LOAD -4
#define	   MY_GRID  -6
#define    MY_BACKGROUND_BlACK -7
#define    MY_BACKGROUND_WHITE -8

#define    WHITE   1
#define    RED     2
#define    GREEN   3
#define    BLUE    4
#define    YELLOW  5
#define    PURPLE 6
#define    CYAN 7

#define    POINT   1
#define    LINE    2
#define    POLYGON 3
#define    POLYGON_LINE 4
#define    CURVE   5
#define    ERASER  6

#define    MAX_CHAR  128

int        height = 800, width = 1300;
bool	   grid_flag = 0;
int        screen_color_flag = 0, times = 0, save_flag = 0, load_flag = 0;
unsigned char  image[SIZEX * SIZEY][4];		// Image data in main memory

int        pos_x = -1, pos_y = -1;
float      myColor[3] = { 0.0,0.0,0.0 };
int        obj_type = -1, file_type = -100;
int        first = 0;		// flag of initial points for lines and curve,..
int        vertex[128][2];	// coords of vertices
int        side = 0;		// num of sides of polygon
float      pnt_size = 1.0, line_Width = 1.0;

// procedure to clear window
void init_window(void)
{
	// Do nothing else but clear window to black

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)width, 0.0, (double)height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	if(screen_color_flag == 64)
		glClearColor(0.0, 0.0, 0.0, 0.0);
	else if (screen_color_flag == 128)
		glClearColor(0.8, 0.8, 0.8, 0.0);
	glFinish();
}

/*------------------------------------------------------------
 * Callback function for display, redisplay, expose events
 * Just clear the window again
 */
void display_func(void)
{
	// define window background color
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

// reshape callback function for window.
void my_reshape(int new_w, int new_h)
{
	height = new_h;
	width = new_w;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)width, 0.0, (double)height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();   //---Trigger Display event for redisplay window
}


// Callback function for keyboard event.
// key = the key pressed,
// (x,y)= position in the window, where the key is pressed.

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'Q' || key == 'q') 
		exit(0);
	if (key == 'G' || key == 'g')
		grid_flag = 1;

	if (key == '1')
		myColor[0] = myColor[1] = myColor[2] = 1.0, glColor3f(myColor[0], myColor[1], myColor[2]);		 //white
	if (key == '2')
		myColor[0] = 1.0, myColor[1] = myColor[2] = 0.0, glColor3f(myColor[0], myColor[1], myColor[2]);  //Red
	if (key == '3')
		myColor[1] = 1.0, myColor[0] = myColor[2] = 0.0, glColor3f(myColor[0], myColor[1], myColor[2]);  //Green
	if (key == '4')
		myColor[2] = 1.0, myColor[0] = myColor[1] = 0.0, glColor3f(myColor[0], myColor[1], myColor[2]);  //Blue
	if (key == '5')
		myColor[0] = myColor[1] = 1.0, myColor[2] = 0.0, glColor3f(myColor[0], myColor[1], myColor[2]);  //Yellow
	if (key == '6')
		myColor[0] = myColor[2] = 1.0, myColor[1] = 0.0, glColor3f(myColor[0], myColor[1], myColor[2]);  //Purple
	if (key == '7')
		myColor[1] = myColor[2] = 1.0, myColor[0] = 0.0, glColor3f(myColor[0], myColor[1], myColor[2]);  //Cyan

	if (key == 'W' || key == 'w')
		obj_type = POINT;
	if (key == 'E' || key == 'e')
		obj_type = LINE;
	if (key == 'R' || key == 'r')
		obj_type = CURVE;
	if (key == 'T' || key == 't')
		obj_type = POLYGON;
	if (key == 'Y' || key == 'y')
		obj_type = POLYGON_LINE;
	if (key == 'U' || key == 'u')
		obj_type = ERASER;

	if (grid_flag)
	{
		glColor4f(0.4, 0.4, 0.4, 1);
		glLineWidth(1);
		glBegin(GL_LINES);	     // Draw the line
		for (int i = 50; i <= 2000; i += 50)
		{
			glVertex3f(i, 0, 0);
			glVertex3f(i, 2000, 0);
		}
		for (int j = 50; j <= 2000; j += 50)
		{
			glVertex3f(0, j, 0);
			glVertex3f(2000, j, 0);
		}
		glEnd();
		glColor3f(myColor[0], myColor[1], myColor[2]);    //為保持開網格後，線的顏色仍與先前設定的相同
		grid_flag = 0;
	}

	// File Type
	if (key == 'S' || key == 's')
	{
		if (screen_color_flag == 128)
			save_flag = 255;
		else
			save_flag = 32;
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
	if (key == 'L' || key == 'l')
	{
		load_flag = 1;
		glRasterPos2i(0, 0);
		glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}

	if (key == 'V' || key == 'v')
		screen_color_flag = 64, init_window(), init_window(), load_flag = 0;
	if (key == 'B' || key == 'b')
		screen_color_flag = 128, init_window(), init_window(), load_flag = 0;
	if (key == 'C' || key == 'c')						  //清空畫面用，一定要放在if (grid_flag)後面，否則有問題
		glClear(GL_COLOR_BUFFER_BIT), load_flag = 0;      //load_flag = 0 是防止LOAD完並改變背景顏色後，橡皮擦
	                                                      //會有顏色出錯的狀況發生
}

// Procedure to draw a polygon
void draw_polygon()
{
	int  i;

	glBegin(GL_POLYGON);
	for (i = 0; i < side; i++)
		glVertex2f(vertex[i][0], height - vertex[i][1]);
	glEnd();

	glFinish();
	side = 0;    // set side=0 for next polygon
}

// Callback function handling mouse-press events
void mouse_func(int button, int state, int x, int y)     //X、Y為滑鼠現在點的位置
{
	if (state == GLUT_UP && obj_type == CURVE)			// 改善畫CURVE的時候，有線一直連著的問題
		first = 0;

	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;

	switch (obj_type) 
	{
	case POINT:
		glPointSize(pnt_size);      // Define point size
		glBegin(GL_POINTS);			// Draw a point
		glVertex2f(x, height - y);
		glEnd();
		break;
	case LINE:
		if (first == 0) 
		{
			first = 1;
			pos_x = x; pos_y = y;
			glPointSize(1.0);	 
			glBegin(GL_POINTS);		 // Draw the 1st point
			glVertex3f(x, height - y, 0);
			glEnd();
		}
		else 
		{
			first = 0;
			glLineWidth(line_Width); // Define line width
			glBegin(GL_LINES);	     // Draw the line
			glVertex2f(pos_x, height - pos_y);
			glVertex2f(x, height - y);
			glEnd();
		}
		break;
	case POLYGON:				     // Define vertices of poly
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (side == 0)               // side = 0為USER點進POL後發生的事情
		{
			vertex[side][0] = x; vertex[side][1] = y;   // 把第一個點座標記錄下來，之後的點擊才會有東西出來
			side++;
		}
		else 
		{
			if (fabs(vertex[side - 1][0] - x) + fabs(vertex[side - 1][1] - y) < 2) // 如果紀錄的兩點距離過近(點兩下)
			{
				glLineWidth(line_Width); // Define line width
				draw_polygon();			 // 把先前紀錄的點作為POLYGON的各點，於是先前畫的直線只是給USER方便看的而已
										 // 用這個FUNCTION後，先前的直線會消失
			}
			else 
			{
				glLineWidth(line_Width); // Define line width
				glBegin(GL_LINES);
				glVertex2f(vertex[side - 1][0], height - vertex[side - 1][1]);  //上一個紀錄的點
				glVertex2f(x, height - y);	                                    //滑鼠剛點的位置
				glEnd();
				vertex[side][0] = x;   // 紀錄滑鼠剛點的位置
				vertex[side][1] = y;   // 紀錄滑鼠剛點的位置。如此，可以達成線會綿綿不絕連著的感覺
				side++;
			}
		}
		break;
	case POLYGON_LINE:				     // Define vertices of poly
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (side == 0)               // side = 0為USER點進POL後發生的事情
		{
			vertex[side][0] = x; vertex[side][1] = y;   // 把第一個點座標記錄下來，之後的點擊才會有東西出來
			side++;
		}
		else
		{
			if (fabs(vertex[side - 1][0] - x) + fabs(vertex[side - 1][1] - y) < 2) // 如果紀錄的兩點距離過近(點兩下)
			{
				glLineWidth(line_Width); // Define line width
				draw_polygon();			 // 把先前紀錄的點作為POLYGON的各點，於是先前畫的直線只是給USER方便看的而已
										 // 用這個FUNCTION後，先前的直線會消失
			}
			else
			{
				glLineWidth(line_Width); // Define line width
				glBegin(GL_LINES);
				glVertex2f(vertex[side - 1][0], height - vertex[side - 1][1]);  //上一個紀錄的點
				glVertex2f(x, height - y);	                                    //滑鼠剛點的位置
				glEnd();
				vertex[side][0] = x;   // 紀錄滑鼠剛點的位置
				vertex[side][1] = y;   // 紀錄滑鼠剛點的位置。如此，可以達成線會綿綿不絕連著的感覺
				side++;
			}
		}
		break;
	case ERASER:
		if (screen_color_flag == 128)
			glColor3f(0.8, 0.8, 0.8);
		else if (screen_color_flag == 64)
			glColor3f(0.0, 0.0, 0.0);
		else
			glColor3f(0.0, 0.0, 0.0);

		if (save_flag == 255 && load_flag == 1)
			glColor3f(0.8, 0.8, 0.8);
		else if (save_flag == 32 && load_flag == 1)
			glColor3f(0.0, 0.0, 0.0);

		glPointSize(10);      // Define point size
		glBegin(GL_POINTS);			// Draw a point
		glVertex2f(x, height - y);
		glEnd();

	default:
		break;
	}
	glFinish();
}

// motion callback function. The mouse is pressed and moved.
void motion_func(int  x, int y)
{
	if (obj_type != CURVE) 
		return;

	// Curve
	if (first == 0)
	{
		first = 1;
		pos_x = x; pos_y = y;
	}
	else
	{
		glLineWidth(line_Width);
		glBegin(GL_LINES);
		glVertex3f(pos_x, height - pos_y, 0.0);
		glVertex3f(x, height - y, 0.0);
		glEnd();
		pos_x = x; pos_y = y;
	}
	glFinish();
}

// Procedure to initialize data alighment and other stuff
void init_func()
{
	glReadBuffer(GL_FRONT);
	glDrawBuffer(GL_FRONT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

// Callback function for color menu
void  color_func(int value)
{
	switch (value) {
	case WHITE:
		myColor[0] = myColor[1] = myColor[2] = 1.0;
		break;

	case RED:
		myColor[0] = 1.0;
		myColor[1] = myColor[2] = 0.0;
		break;

	case GREEN:
		myColor[1] = 1.0;
		myColor[0] = myColor[2] = 0.0;
		break;

	case BLUE:
		myColor[2] = 1.0;
		myColor[0] = myColor[1] = 0.0;
		break;

	case YELLOW:
		myColor[0] = myColor[1] = 1.0;
		myColor[2] = 0.0;
		break;

	case PURPLE:
		myColor[0] = myColor[2] = 1.0;
		myColor[1] = 0.0;
		break;

	case CYAN:
		myColor[1] = myColor[2] = 1.0;
		myColor[0] = 0.0;
		break;

	default:
		break;
	}
	glColor3f(myColor[0], myColor[1], myColor[2]);
}

// Callback function for top menu.
void file_func(int file_type)
{
	int i, j;

	if (file_type == MY_QUIT)
		exit(0);

	else if (file_type == MY_CLEAR)
		glClear(GL_COLOR_BUFFER_BIT), load_flag = 0;

	else if (file_type == MY_GRID)
	{
		grid_flag = 1;
		glColor4f(0.4, 0.4, 0.4, 1);
		glLineWidth(1);
		glBegin(GL_LINES);	     // Draw the line
		for (int i = 50; i <= 2000; i += 50)
		{
			glVertex3f(i, 0, 0);
			glVertex3f(i, 2000, 0);
		}
		for (int j = 50; j <= 2000; j += 50)
		{
			glVertex3f(0, j, 0);
			glVertex3f(2000, j, 0);
		}
		glEnd();
		glColor3f(myColor[0], myColor[1], myColor[2]);    //為保持開網格後，線的顏色仍與先前設定的相同
	}
	else if (file_type == MY_BACKGROUND_BlACK )
		screen_color_flag = 64, init_window(), init_window(), load_flag = 0;

	else if (file_type == MY_BACKGROUND_WHITE )
		screen_color_flag = 128, init_window(), init_window(), load_flag = 0;

	else if (file_type == MY_SAVE)
	{
		if (screen_color_flag == 128)
			save_flag = 255;
		else
			save_flag = 32;
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	}
	else if (file_type == MY_LOAD)
	{
		load_flag = 1;
		glRasterPos2i(0, 0);
		glDrawPixels(width, height,GL_RGBA, GL_UNSIGNED_BYTE,image);
	}
	glFlush();
}

void quit_func(int mode)
{
	if (mode == MY_QUIT)
		exit(0);
}

void size_func(int value)
{
	pnt_size = value;
}

void lineWidth_func(int value)
{
	line_Width = value;
}

/*---------------------------------------------------------------
 * Callback function for top menu. Do nothing.
 */
void top_menu_func(int value)
{
}


/*-------------------------------------------------------------
 * Callback Func for type_m, define drawing object
 */
void draw_type(int value)
{
	obj_type = value;
	if (value == LINE || value == CURVE)
		first = 0;
	else if (value == POLYGON)
		side = 0;
}


/*---------------------------------------------------------------
 * Main procedure sets up the window environment.
 */
void main(int argc, char** argv)
{
	int  size_m, lineWidth_m, top_m, color_m, file_m, type_m, quit_m = 1;

	glutInit(&argc, argv);							//---Make connection with server---

	glutInitWindowPosition(300, 150);				//---Specify window position ---
	glutInitWindowSize(width, height);				//--Define window's height and width--

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);	//---set display mode---
	init_func();

	/* Create parent window */
	glutCreateWindow("Drawing Toolkit");

	glutDisplayFunc(display_func);	// Associate display event callback func
	glutReshapeFunc(my_reshape);	// Associate reshape event callback func
	glutKeyboardFunc(keyboard);		// Callback func for keyboard event 
	glutMouseFunc(mouse_func);		// Mouse Button Callback func
	glutMotionFunc(motion_func);	// Mouse motion event callback func

	color_m = glutCreateMenu(color_func);	// Create color-menu
	glutAddMenuEntry("White", WHITE);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Yellow", YELLOW);
	glutAddMenuEntry("Purple", PURPLE);
	glutAddMenuEntry("Cyan", CYAN);

	type_m = glutCreateMenu(draw_type);     // Create draw-type menu
	glutAddMenuEntry("Point", POINT);		// Switch case0 : POINT, case1 : LINE ........
	glutAddMenuEntry("Line", LINE);
	glutAddMenuEntry("Curve", CURVE);
	glutAddMenuEntry("Polygon(Fill)", POLYGON);
	glutAddMenuEntry("Polygon(Line)", POLYGON_LINE);
	glutAddMenuEntry("Eraser", ERASER);

	size_m = glutCreateMenu(size_func);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);
	glutAddMenuEntry("6", 6);
	glutAddMenuEntry("7", 7);
	glutAddMenuEntry("8", 8);
	glutAddMenuEntry("9", 9);
	glutAddMenuEntry("10", 10);

	lineWidth_m = glutCreateMenu(lineWidth_func);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);
	glutAddMenuEntry("6", 6);
	glutAddMenuEntry("7", 7);
	glutAddMenuEntry("8", 8);
	glutAddMenuEntry("9", 9);
	glutAddMenuEntry("10", 10);

	quit_m = glutCreateMenu(quit_func);

	file_m = glutCreateMenu(file_func);   // Create file-menu menu
	glutAddMenuEntry("Grid", MY_GRID);
	glutAddMenuEntry("Back(Black)", MY_BACKGROUND_BlACK);
	glutAddMenuEntry("Back(White)", MY_BACKGROUND_WHITE);
	glutAddMenuEntry("Save", MY_SAVE);
	glutAddMenuEntry("Load", MY_LOAD);
	glutAddMenuEntry("Clear", MY_CLEAR);
	glutAddMenuEntry("Quit", MY_QUIT); 

	top_m = glutCreateMenu(top_menu_func);	// Create top menu
	glutAddSubMenu("Colors", color_m);		// add color-menu as a sub-menu
	glutAddSubMenu("Draw Type", type_m);
	glutAddSubMenu("Point Size", size_m);
	glutAddSubMenu("Line Width", lineWidth_m);
	glutAddSubMenu("Screen Option", file_m);	// add file-menu as a sub-menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);			// associate top-menu with right button

	//---Test whether overlay support is available --

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(300, 200);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 23);

	if (glutLayerGet(GLUT_OVERLAY_POSSIBLE)) 
		fprintf(stderr, "Overlay is available\n");
	else
		fprintf(stderr, "Overlay is NOT available, May encounter problems for menu\n");

	//---Enter the event loop ----
	glutMainLoop();
}