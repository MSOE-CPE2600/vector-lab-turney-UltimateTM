/***********
* Program Name: vector.h
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -Wall -o vec_calculator main.c vector_operations.c input.c -lm
* Copyright (c) 2025
*
***********/
#include <stdio.h>
#include <stdlib.h>

// Define the Vector struct
#ifndef VECTOR_H // Header guard
#define VECTOR_H // Prevent multiple inclusions
typedef struct vector {
    char name[10];
    double x;
    double y;
    double z;
} Vector;
#endif