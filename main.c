/***********
* Program Name: main.c
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -o vec_calculator main.c vector_operations.c input.c
* Copyright (c) 2025
*
***********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "input.h"
#define MAX_VECTORS 10
#define INPUT_SIZE 100

void clearList(Vector *list);
void list(Vector *list);
int countUsedVectors(Vector *list);


int main(void) {
    char promptInput[INPUT_SIZE];
    char input[INPUT_SIZE];
    int quit_flag = 0; // flag to indicate if user wants to quit
    char *quit = "quit";
    char *listCmd = "list";
    char *clearCmd = "clear";
    Vector vList[MAX_VECTORS] = {0};
    int vList_size = sizeof(vList)/sizeof(vList[0]);
    int vList_used = countUsedVectors(vList);

    printf("Welcome to the Vector Calculator!\n");
    printf("Type 'list' to see all stored vectors, 'clear' to clear the vector list, and 'quit' to exit the program.\n");
    printf("To perform operations, use the format A = B + C or B + C to add vectors, A = B - C or B - C to subtract vectors,\n");
    printf("A = B * C or B * C for dot product, A = B x C or B x C for cross product, A = B o n or B o n to multiply vector B by scalar n,\n");
    printf("To start the program, enter the command prompt 'matlab>' or any command followed by a '>'\n");

    fgets(promptInput, INPUT_SIZE, stdin);
    promptCheck(promptInput);

    while (strcmp(input, quit) != 0) {
        while (vList_used == MAX_VECTORS) { // if vector list is full
            printf("%s ", promptInput);
            printf("Vector list full. Please clear the list using \"clear\" before adding more vectors.\n");
            printf("%s ", promptInput);
            fgets(input, INPUT_SIZE, stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline character

            Operator operator = determineOperator(input); // determine operator in input

            // Check if the operator is valid and not an assignment operator
            // Also check if the input is not a command (list, clear, quit)
            if (operator != OP_assign && strcmp(input, listCmd) != 0 && strcmp(input, clearCmd) != 0 && strcmp(input, quit) != 0) {
                inputParse(input, promptInput, vList, vList_size, vList_used);
            } else if (operator != OP_assign){
                if (strcmp(input, clearCmd) == 0) {
                    clearList(vList);
                } else if (strcmp(input, listCmd) == 0) {
                    list(vList);
                } else if (strcmp(input, quit) == 0) {
                    clearList(vList);
                    quit_flag = 1; // set quit flag to exit program, had to type quit twice if list was full
                }
            } 
            
            vList_used = countUsedVectors(vList);
        }

        if (quit_flag == 1) { // if quit flag is set from array full, exit program
            strcpy(input, quit);
        } else {
            printf("%s ", promptInput);
            fgets(input, INPUT_SIZE, stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            // check for commands
            if (strcmp(input, listCmd) == 0) {
                list(vList);
                continue;
            } else if (strcmp(input, clearCmd) == 0) {
                clearList(vList);
                continue;
            } else if (strcmp(input, quit) == 0) {
                continue;
            }
            // parse input and perform operations
            inputParse(input, promptInput, vList, vList_size, vList_used);
            vList_used = countUsedVectors(vList); // update used size
        }
        
    }

    return 0;
}

void clearList(Vector *list) { // Clear the vector list
    for (int i = 0; i < MAX_VECTORS; i++) {
        list[i].name[0] = '\0';
        list[i].x = 0;
        list[i].y = 0;
        list[i].z = 0;
    }
}

void list(Vector *list) { // List all stored vectors
    for (int i = 0; i < MAX_VECTORS; i++) {
        if (list[i].name[0] != '\0') {
            printf("%s = %.2f, %.2f, %.2f\n", list[i].name, list[i].x, list[i].y, list[i].z);
        }
    }
}

int countUsedVectors(Vector *list) { // Count the number of used vectors in the list
    int count = 0;
    for (int i = 0; i < MAX_VECTORS; i++) {
        if (list[i].name[0] != '\0') {
            count++;
        }
    }
    return count;
}