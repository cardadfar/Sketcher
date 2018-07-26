#include "Skeleton.h"
#include <assert.h>
#include <windows.h>
#include <glew.h>
#include <glut.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

//---------------------- MODIFY PIXELS ------------------

//gets pixel at (x,y)
static PF_Pixel *getPixelXY(PF_ParamDef checkout, 
                            int x, 
                            int y);

//sets pixel at (x,y) to white
static void setPixelXY(PF_EffectWorld *def, 
                       int x , 
                       int y);

//---------------------- PIXEL CALCULATIONS ------------------

//returns distance between (x1, y1) & (x2, y2)
static float dist(float x1, 
                  float y1, 
                  float x2, 
                  float y2);

//returns true if midpoint of line connecting (x1, y1) & (x2, y2) is within range of color inp, false otherwise
static bool gap(float x1, 
                float y1, 
                float x2, 
                float y2, 
                float wth, 
                float hgt, 
                PF_Pixel inp, 
                PF_ParamDef checkout);

//returns true if angle between (x1, y1) & (x2, y2) & (x3, y3) is within range of range, false otherwise
static bool dir(float x1, 
                float y1, 
                float x2, 
                float y2, 
                float x3, 
                float y3, 
                float range);

//---------------------- GLEW SETUP ------------------

//sets up a glew context of size [l_width, l_height]
static GLFWwindow *glewSetup(float l_width, 
                             float l_height);

//draws canvas of size [l_width, l_height] using Drawing Mode mode & locations in points, saving the data to l_data
static void generateCanvas(float *points, 
                           float l_width, 
                           float l_height, 
                           PF_EffectWorld l_world, 
                           PF_Pixel8 *l_data,
                           PF_Pixel color, 
                           GLFWwindow *offscreen_context,
                           int count,
                           int step,
                           int mode);
