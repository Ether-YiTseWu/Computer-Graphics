#pragma once

#define   TSIZE  64   

// Vertices of the box
extern float  points[][3] =                    
{ {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5 },
  {0.5, 0.5, -0.5}  , {-0.5, 0.5, -0.5 },
  {-0.5, -0.5, 0.5} , {0.5, -0.5, 0.5  },
  {0.5, 0.5, 0.5}   , {-0.5, 0.5, 0.5  } };

// Define faces, these num. are indices of vertices
int    face[][4] = { {0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
					{4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3} };
// Define a cube by using face indices 
int    cube[6] = { 0, 1, 2, 3, 4, 5 };

// Define normals of faces
float  normal[][4] = { {0.0, 0.0, -1.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0},
			  {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0} };

float  colorsObstacles[6][3] =
{ {0.2,0.2,0.2}, {0.2,0.2,0.2}, {0.8,0.8,0.8},
  {0.2,0.2,0.2}, {0.2,0.2,0.2}, {0.2,0.2,0.2} };

// Define material properties for cube
// Brass
float  robot_ambient[] = { 0.329412, 0.223529, 0.027451, 1.0 };
float  robot_diffuse[] = { 0.780392, 0.568627, 0.113725, 1.0 };
float  robot_specular[] = { 0.992157, 0.941176, 0.8078843, 1.0 };
float  robot_shininess = 27.8974;

// Silver
float  robot1_ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0 };
float  robot1_diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0 };
float  robot1_specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0 };
float  robot1_shininess = 51.2;

// Polished copper
float  robot2_ambient[] = { 0.2295f, 0.08825f, 0.0275f, 1.0 };
float  robot2_diffuse[] = { 0.5508f, 0.2118f, 0.066f, 1.0 };
float  robot2_specular[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0 };
float  robot2_shininess = 51.2;
GLfloat robotEmission[] = { 0.0, 0.05, 0.0, 1.0 };

float  obstacle_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
float  obstacle_diffuse[] = { 0.55, 0.55, 0.55, 1.0 };
float  obstacle_specular[] = { 0.55, 0.45, 0.4, 1.0 };
float  obstacle_shininess = 0.25;

float  flr_diffuse[] = { 0.60, 0.60, 0.60, 1.0 };
float  flr_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
float  flr_specular[] = { 0.0, 0.0, 0.0, 1.0 };

// Define light source properties
// SPOT LIGHT
float  lit_position[] = { 10.0, 14.0, 0.0, 1.0 };
float  lit_direction[] = { -1.0, -1.0, 1.0, 0.0 };
float  lit_diffuse[] = { 0.8, 0.4, 0.4, 1.0 };
float  lit_specular[] = { 0.7, 0.7, 0.7, 1.0 };
float  lit_cutoff = 37.0;
float  lit_exponent = 4.0;

// PARALLEL LIGHT
float  lit1_position[] = { 10.0, 14.0, 0.0, 0.0 };
float  lit1_diffuse[] = { 0.7, 0.7, 0.0, 1.0 };

// POINT LIGHT
float  lit2_position[] = { 10.0, 14.0, 0.0, 1.0 };
float  lit2_direction[] = { -1.0, -1.0, 1.0, 0.0 };
float  lit2_AMBIENT [] = { 0.0, 0.0, 0.0, 1.0 };
float  lit2_DIFFUSE [] = { 1.0, 1.0, 1.0, 1.0 };
float  lit2_SPECULAR[] = { 1.0, 1.0, 1.0, 1.0 };
float  global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

// Some global variables for transformation
float  lit_angle = 0.0, lit1_angle = 0.0;
float  head = 0.0, roll = 0.0, Epitch = 0.0, Wpitch = 0.0;
float  up = 0.0, right = 0.0, zoom = 0.0;

// robot parameter
float  PI = 3.141592653;
float  Step = 0.5;
float  position[3] = { 8.0, 4.0, 8.0 };
float  self_ang = -90.0, swing_ang = 0.0, knee_ang_small = 0.0, knee_ang_big = 0.0, glob_ang = 0.0;
int    countSun = 0, countPoint = 0, countSpot = 0, countFogMode = 0, countRobotMa = 0, countRobotEmi = 0;

// Translation and rotations of eye coordinate system
int     width = 800, height = 800;
float   eyeDx = 30.0, eyeDy = 30.0, eyeDz = 30.0;
float   eyeAngx = 0.0, eyeAngy = 0.0, eyeAngz = 0.0;
double  Eye[3] = { 0.0, 0.0, 30.0 };
float   u[3][3] = { {1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0} };
float   eye[3];
float   cv, sv; // cos(5.0) and sin(5.0)

// Texture Mapping Parameters
unsigned char  checkboard[TSIZE][TSIZE][4];   // checkboard textures
unsigned char  brick[TSIZE][TSIZE][4];        // brick wall textures
unsigned int   textName[3];                   // declare two texture maps
float    textAng = 0.0, ds = 0.0, dt = 0.0;

// the axes of billboard
float  a[3], b[3], mtx[16];

// Fog
float fog_color[] = { 0.3, 0.3, 0.6, 0.5 };

// Texture Mapping's parameters
int select_ = 0;
unsigned int TextureID[4];
unsigned char circle[64][64][4];
unsigned char waterwave[64][64][4];
unsigned char star[64][64][4];
unsigned char land[64][64][4];

// Parameters of cube
int cube_[6] = { 0 , 1 , 2 , 3 , 4 , 5 };
int face_[][4] = { { 0 , 3 , 2 , 1 } , { 0 , 1 , 5 , 4 } , { 1 , 2 , 6 , 5 } , { 4 , 5 , 6 , 7 } , { 2 , 3 , 7 , 6 } , { 0 , 4 , 7 , 3 } };
float vertex[][3] = { { -0.5 ,  -0.5 , -0.5 } , { 0.5 , -0.5 , -0.5 } , { 0.5 , 0.5 , -0.5 } , { -0.5 , 0.5 , -0.5 } , { -0.5 , -0.5 , 0.5 } , { 0.5 , -0.5 , 0.5 } , { 0.5 , 0.5 , 0.5 } , { -0.5 , 0.5 , 0.5 } };
double color[6][3] = { { 0.55 ,0.55 , 0.25 } , { 0.65 , 0.55 , 1.0 } , { 0.75 , 0.55 , 0.55 } , { 0.55 , 0.55 , 0.25 } , { 0.7 , 0.6 , 0.7 } , { 0.55 , 0.75 , 0.75 } };

// Parameters of light
float material_shininess = 32.0;
float light_position[] = { 0.0 , 15.0 , 5.0 , 1.0 };
float light_direction[] = { 0.0 , -1.0 , 0.0 , 0.0 };
float light_diffuse[] = { 1.0 , 1.0 , 0.5 , 1.0 };
float light_specular[] = { 0.5 , 0.5 , 0.5 , 1.0 };
float light_cutoff = 50.0;
double light_attenuation = 0.8;