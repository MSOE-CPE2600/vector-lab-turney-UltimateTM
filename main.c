/***********
* Program Name: main.c
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -o vctr_calc main.c vector.c input.c
* Copyright (c) 2025
*
***********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "input.h"

int main(void) {
    char promptInput[100];
    char input[100];
    char *quit = "quit\n\0";
    Vector vList[10];   

    fgets(promptInput, 99, stdin);
    promptCheck(promptInput);

    while (strcmp(input, quit) != 0) {
        printf("%s ", promptInput);
        userInput(input);
    }

    return 0;
}