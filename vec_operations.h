/***********
* Program Name: vector_operations.h
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -Wall -o vec_calculator main.c vector_operations.c input.c -lm
* Copyright (c) 2025
*
***********/

void addVectors(Vector a, Vector b, Vector *result);

void subtractVectors(Vector a, Vector b, Vector *result);

void dotProduct(Vector a, Vector b, Vector *result);

void crossProduct(Vector a, Vector b, Vector *result);

void scalarMultiply(Vector a, double scalar, Vector *result);

void printDot(Vector a);

void printVector(Vector a);

void addvect(Vector new_vect, Vector *vList, int vList_size);

void modifyVector(Vector a, Vector* vList, int vList_size);

Vector findvect(char* name, Vector* vList, int vList_size);