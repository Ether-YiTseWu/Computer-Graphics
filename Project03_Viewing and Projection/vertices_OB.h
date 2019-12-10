#pragma once

// Declare robot position, orientation
float  self_ang = -90.0, swing_ang = 0.0, knee_ang_small = 0.0, knee_ang_big = 0.0, glob_ang = 0.0;
float  position[3] = { -20.0, 2.0, 10.0 };
float  PI = 3.141592653;

int width = 800, height = 800;

extern float  points[][3] =                    // Vertices of the box
{ {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5 },
  {0.5, 0.5, -0.5}  , {-0.5, 0.5, -0.5 },
  {-0.5, -0.5, 0.5} , {0.5, -0.5, 0.5  },
  {0.5, 0.5, 0.5}   , {-0.5, 0.5, 0.5  } };

extern int    face[][4] =                      // face of box, each face composing of 4 vertices
{ {0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5},
  {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3} };

extern float  colors[6][3] =
{ {0.5,0.5,0.5}, {0.7,0.7,0.7}, {0.7,0.5,0.5},
  {0.5,0.5,0.5}, {0.5,0.7,0.5}, {0.5,0.5,0.7} };

extern float  colorsObstacles[6][3] =
{ {0.2,0.2,0.2}, {0.2,0.2,0.2}, {0.8,0.8,0.8},
  {0.2,0.2,0.2}, {0.2,0.2,0.2}, {0.2,0.2,0.2} };

extern int    cube[6] = { 0, 1, 2, 3, 4, 5 };  // indices of the box faces

// Translation and rotations of eye coordinate system
float   eyeDx = 30.0, eyeDy = 30.0, eyeDz = 30.0;
float   eyeAngx = 0.0, eyeAngy = 0.0, eyeAngz = 0.0;
double  Eye[3] = { 0.0, 0.0, 30.0 };

float   u[3][3] = { {1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0} };
float   eye[3];
float   cv, sv; // cos(5.0) and sin(5.0)