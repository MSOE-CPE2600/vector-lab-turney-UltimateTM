/***********
* Program Name: main.c
* Author: Gabriel Limberg
* Date: 30 Sept 2025
* Version: 1.0
* To Compile: gcc -Wall -o vec_calculator main.c vector_operations.c input.c -lm
* Copyright (c) 2025
*
***********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "input.h"
#define INITIAL_VECTOR_CAPACITY 10
#define INPUT_SIZE 100

void clearList(Vector *list, int size);
void list(Vector *list, int size);
int countUsedVectors(Vector *list, int size);
void fillVectorList(Vector *list, int size, int usedVectors);


int main(void) {
    char promptInput[INPUT_SIZE];
    char input[INPUT_SIZE];
    int quit_flag = 0; // flag to indicate if user wants to quit
    char *quit = "quit";
    char *listCmd = "list";
    char *clearCmd = "clear";
    char *fill = "fill"; // command to fill vector list with sample data for testing
    char *open = "open"; // command to open CSV file and read vectors from it
    char *write = "write"; // command to write vectors to CSV file

    Vector *vList; // dynamically allocate memory for vector list
    vList = malloc(INITIAL_VECTOR_CAPACITY * sizeof *vList); // allocate memory for vector list
    int vList_size = INITIAL_VECTOR_CAPACITY; // current size of vector list
    int vList_used = 0; // current number of used vectors

    printf("Welcome to the Vector Calculator!\n");
    printf("Type 'list' to see all stored vectors, 'clear' to clear the vector list, and 'quit' to exit the program.\n");
    printf("To perform operations, use the format A = B + C or B + C to add vectors, A = B - C or B - C to subtract vectors,\n");
    printf("A = B * C or B * C for dot product, A = B x C or B x C for cross product, A = B o n or B o n to multiply vector B by scalar n\n");
    printf("To start the program, enter the command prompt 'matlab>' or any command followed by a '>'\n");

    fgets(promptInput, INPUT_SIZE, stdin);
    promptCheck(promptInput);

    while (strcmp(input, quit) != 0) {
        if (vList_used == vList_size) { // if vector list is full, reallocate memory to expand list
            Vector *temp = realloc(vList, (vList_size + INITIAL_VECTOR_CAPACITY) * sizeof *vList); // reallocate memory to expand vector list
            if (temp == NULL) {
                printf("Memory reallocation failed. Exiting program.\n");
                strcpy(input, quit); // exit program if reallocation fails
            } else {
                vList = temp;
                vList_size += INITIAL_VECTOR_CAPACITY; // update vector list size
            }
        }

        if (strcmp(input, quit) != 0) { // if user has not chosen to quit
            printf("%s ", promptInput);
            fgets(input, INPUT_SIZE, stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            // check for commands
            if (strcmp(input, listCmd) == 0) {
                list(vList, vList_used);
                continue;
            } else if (strcmp(input, clearCmd) == 0) {
                clearList(vList, vList_used);
                vList_used = 0; // reset used size
                vList_size = INITIAL_VECTOR_CAPACITY; // reset vector list size
                vList = calloc(INITIAL_VECTOR_CAPACITY, sizeof *vList); // reset vector list
                continue;
            } else if (strcmp(input, fill) == 0) {
                fillVectorList(vList, vList_size, vList_used);
                vList_used = countUsedVectors(vList, vList_size); // update used size
                continue;
            } else if (strcmp(input, open) == 0) {
                printf("Enter name of the file\n");
                fgets(input, INPUT_SIZE, stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove newline character

            } else if (strcmp(input, write) == 0) {
                if (vList_used == 0) {
                    printf("Vector list is empty, please populate list before writing\n");
                    continue;
                }
                printf("Enter name of the file\n");
                fgets(input, INPUT_SIZE, stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove newline character
                writeCSV(input, vList, vList_used);


            } else if (strcmp(input, quit) == 0) {
                continue; // exit program
            }
            // parse input and perform operations
            inputParse(input, promptInput, vList, vList_size, vList_used);
            vList_used = countUsedVectors(vList, vList_size); // update used size
            printf("Used Vectors: %d\n", vList_used); // debug print to show used vectors
        }
        
    }
    free(vList); // free allocated memory

    return 0;
}

void clearList(Vector *list, int size) { // Clear the vector list
    for (int i = 0; i < size; i++) {
        list[i].name[0] = '\0';
        list[i].x = 0;
        list[i].y = 0;
        list[i].z = 0;
    }
}

void list(Vector *list, int size) { // List all stored vectors
    for (int i = 0; i < size; i++) {
        if (list[i].name[0] != '\0') {
            printf("%s = %.2f, %.2f, %.2f\n", list[i].name, list[i].x, list[i].y, list[i].z);
        }
    }
}

int countUsedVectors(Vector *list, int size) { // Count the number of used vectors in the list
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i].name[0] != '\0') {
            count++;
        }
    }
    return count;
}

void fillVectorList(Vector *list, int Vlist_size, int usedVectors) { // Fill the vector list with sample data for testing
    for (int i = usedVectors; i < Vlist_size; i++) {
        sprintf(list[i].name, "v%u", (unsigned)(i + 1));
        list[i].x = i * 1.0;
        list[i].y = i * 2.0;
        list[i].z = i * 3.0;
    }
}   