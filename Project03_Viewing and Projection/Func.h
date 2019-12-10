#pragma once

// The following functions are in backGeound_OB.cpp
void  display();
void  reshape(int, int);
float norm2(float v[]);

// The following functions are in draw_func.cpp
void  myinit();
void  draw_floor();
void  draw_cube();
void  draw_obstacles();
void  draw_background();
void  draw_axes();
void  draw_scene();
void  draw_view();

void  make_projection(int);
void  make_view(int);
void  move_control(unsigned char key, int x, int y);