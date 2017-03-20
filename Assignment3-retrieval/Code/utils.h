#ifndef _UTILS_H
#define _UTILS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

using namespace std;

// Some utility functions
void hsv_to_rgb( double h, double s, double v, unsigned char* r, unsigned char* g, unsigned char* b );
unsigned char* read_pgm( char* filename, int* width, int* height );
void write_ppm( FILE* f, int width, int height, unsigned char* data );
void write_pgm( FILE* f, int width, int height, unsigned char* data );
void mat_pgm(FILE* f,int** mat,int width, int height);
int** pgm_mat( char* filename, int& width, int& height );
int** imatrix(int row, int col);


#endif