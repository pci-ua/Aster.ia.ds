#ifndef __INIT
#define __INIT

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include<vector>

#include "fonctions/ppm.h"


int Rand( int a, int b);
int notre_init(int argc, char** argv, void (*Modelisation)());
GLvoid Redimensionne(GLsizei width, GLsizei height);



#endif