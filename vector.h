/***********
* Program Name: vector.h
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -o vctr_calc main.c vector.c input.c
* Copyright (c) 2025
*
***********/

typedef struct vector {
    char name[10];
    double x;
    double y;
    double z;
} Vector;