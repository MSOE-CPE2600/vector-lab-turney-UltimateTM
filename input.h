/***********
* Program Name: input.h
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -Wall -o vec_calculator main.c vector_operations.c input.c -lm
* Copyright (c) 2025
***********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef enum {
    OP_none,
    OP_add = '+',
    OP_sub = '-',
    OP_dot = '*',
    OP_cross = 'x',
    OP_scalar = 'o',
    OP_assign = '='
} Operator;

void promptCheck(char *promptInput); // Check for valid prompt input

void inputParse(char *input, char *promptInput, Vector *list, int list_size, int used_size); // Parse user input and perform operations

Operator determineOperator(char *input); // Determine the operator in the input string

void clear(); // Clear the vector list

void strToUpper(char *str); // Convert string to uppercase

void strToLower(char *str); // convert to lowercase

int verifyFile(char *input);

void openCSV(char *input, Vector *list); // Open CSV file and read vectors from it

void writeCSV(char *input, Vector *list, int vList_used); // Write vectors to CSV file

void checkCSV(char *input);

