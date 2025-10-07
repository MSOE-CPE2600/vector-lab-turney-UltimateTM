/***********
* Program Name: input.c
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -o vctr_calc main.c vector.c input.c
* Copyright (c) 2025
*
***********/
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void promptCheck(char *promptInput) {
    bool validInput = true;
    do {
        int length = strlen(promptInput);

        if (length > 0 && promptInput[length - 2] == '>') {
            validInput = true;
            if (length >= 2) {
                promptInput[length - 1] = '\0'; 
            }
        } else {
            validInput = false; 
            printf("Invalid Input: Please use \">\" to indicate command usage\n");
            fgets(promptInput, 99, stdin);
        }

    } while (validInput == false);
}

void testcheck() {
    printf("test");
}

void userInput(char *userInput) {
    fgets(userInput, 99, stdin);
}