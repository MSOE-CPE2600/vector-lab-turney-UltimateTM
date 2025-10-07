/***********
* Program Name: vector.h
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -o vctr_calc main.c vector.c input.c
* Copyright (c) 2025
*
***********/
#include "vector.h"

void addVectors(Vector a, Vector b, Vector *result);

void subtractVectors(Vector a, Vector b, Vector *result);

void dotProduct(Vector a, Vector b, double *result);

void crossProduct(Vector a, Vector b, Vector *result);

void scalarMultiply(Vector a, double scalar, Vector *result);

void magnitude(Vector a, double *result);

void printVector(Vector a);