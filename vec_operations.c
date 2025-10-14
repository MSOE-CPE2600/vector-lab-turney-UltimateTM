/***********
* Program Name: vector_operations.c
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -o vec_calculator main.c vector_operations.c input.c
* Copyright (c) 2025
*
***********/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vector.h"
#include "vec_operations.h"

void addVectors(Vector a, Vector b, Vector *result) { // Add two vectors
    result->x = a.x + b.x;
    result->y = a.y + b.y;
    result->z = a.z + b.z;
}

void subtractVectors(Vector a, Vector b, Vector *result) { // Subtract two vectors
    result->x = a.x - b.x;
    result->y = a.y - b.y;
    result->z = a.z - b.z;
}

void dotProduct(Vector a, Vector b, Vector *result) { // Dot product of two vectors
    result->x = a.x * b.x + a.y * b.y + a.z * b.z;
    result->y = 0;
    result->z = 0;
}

void crossProduct(Vector a, Vector b, Vector *result) { // Cross product of two vectors
    result->x = a.y * b.z - a.z * b.y;
    result->y = a.z * b.x - a.x * b.z;
    result->z = a.x * b.y - a.y * b.x;
}

void scalarMultiply(Vector a, double scalar, Vector *result) { // Multiply vector by scalar
    result->x = a.x * scalar;
    result->y = a.y * scalar;
    result->z = a.z * scalar;
}

void printDot(Vector a) { // Print scalar result
    printf("%s = %.2f\n", a.name, a.x);
}

void printVector(Vector a) { // Print vector in format "name = x y z"
    printf("%s = %.2f %.2f %.2f\n", a.name, a.x, a.y, a.z);
}

void addvect(Vector new_vect, Vector *vList, int vList_size) { // Add new vector to vector list
    for (int i = 0; i < vList_size; i++) {
        if (vList[i].name[0] == '\0') {
            vList[i] = new_vect;
            return;
        }
    }
}

void modifyVector(Vector a, Vector* vList, int vList_size) { // Modify existing vector in vector list
    for (int i = 0; i < vList_size; i++) {
        if (strcmp(a.name, vList[i].name) == 0) {
            vList[i].x = a.x;
            vList[i].y = a.y;
            vList[i].z = a.z;
            return;
        }
    }
}

Vector findvect(char* name, Vector* vList, int vList_size) { // Find vector in vector list by name
    for (int i = 0; i < vList_size; i++) {
        if (strcmp(name, vList[i].name) == 0) {
            return vList[i];
        }
    }
    return (Vector){0};
}
