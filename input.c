/***********
* Program Name: input.c
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
#include <stdbool.h>
#include <ctype.h>
#include "input.h"
#include "vector.h"
#include "vec_operations.h"
#define MAX_VECTORS 10
#define INPUT_SIZE 100


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
            fgets(promptInput, INPUT_SIZE, stdin);
        }

    } while (validInput == false);
}

void strToUpper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void strToLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void inputParse(char *input, char *promptInput, Vector *list, int list_capacity, int used_size) {
    Operator op;
    int vector_list_size = list_capacity;
    char temp_input_coeff1[INPUT_SIZE];
    char temp_input_coeff2[INPUT_SIZE];
    char temp_name[INPUT_SIZE];
    double temp_x;
    double temp_y;
    double temp_z;
    int position = 0;

    op = determineOperator(input);

    if (op == OP_add) {
        if (sscanf(input, "%s = %s + %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position) == 3) {
            sscanf(input, "%s = %s + %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B + C to add vectors\n");
                return;
            }
            strToUpper(temp_name);
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size);
            Vector b = findvect(temp_input_coeff2, list, vector_list_size); // find vectors in list
            Vector c = findvect(temp_name, list, vector_list_size);

            if (a.name[0] == '\0' || b.name[0] == '\0') {
                printf("VECTOR NOT FOUND\n"); // If either vector is not found
                return;
            }

            // if vector already exists, modify it
            if (c.name[0] != '\0') {
                addVectors(a, b, &c);
                modifyVector(c, list, vector_list_size);
                printVector(c);
            } else {
                // else create new vector
                Vector result;
                addVectors(a, b, &result); // Perform addition
                strcpy(result.name, temp_name); // Assign the name to the result vector
                addvect(result, list, vector_list_size); // Add the new vector to the list
                printVector(result);
                
            }

        } else if (sscanf(input, "%s + %s%n", temp_input_coeff1, temp_input_coeff2, &position) == 2) {
            sscanf(input, "%s + %s%n", temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B + C or B + C to add vectors\n");
                return;
            }
            strToUpper(temp_input_coeff1);
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size);
            Vector b = findvect(temp_input_coeff2, list, vector_list_size); // find vectors in list
            Vector result;
            if (a.name[0] == '\0' || b.name[0] == '\0') {
                printf("VECTOR NOT FOUND\n"); // If either vector is not found
                return;
            } else {
                addVectors(a, b, &result); // Perform addition
                strcpy(result.name, "ans"); // Assign the name to the result vector
                printVector(result); // Print the result
            }
        } else {
            printf("Invalid Input: Please use the format A = B + C or B + C to add vectors\n");
            return; // Invalid input format
        }
        
    } else if (op == OP_sub) {
        if (sscanf(input, "%s = %s - %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position) == 3) {
            sscanf(input, "%s = %s - %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B - C or B - C to subtract vectors\n");
                return;
            }
            strToUpper(temp_name);
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size);
            Vector b = findvect(temp_input_coeff2, list, vector_list_size); // find vectors in list
            Vector c = findvect(temp_name, list, vector_list_size);
            Vector result;

            if (a.name[0] == '\0' || b.name[0] == '\0') {
                printf("VECTOR NOT FOUND\n"); // If either vector is not found
                return;
            }

            if (c.name[0] != '\0') { // if vector to be assigned already exists
                subtractVectors(a, b, &c);
                modifyVector(c, list, vector_list_size);
                printVector(c);
            } else { // else create new vector
                subtractVectors(a, b, &result); // Perform subtraction
                strcpy(result.name, temp_name); // Assign the name to the result vector
                addvect(result, list, vector_list_size); // Add the new vector to the list
                printVector(result); // Print the result
            }

        } else if (sscanf(input, "%s - %s%n", temp_input_coeff1, temp_input_coeff2, &position) == 2) { // if no assignment
            sscanf(input, "%s - %s%n", temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B - C or B - C to subtract vectors\n");
                return;
            }
            strToUpper(temp_input_coeff1);
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size); // find vectors in list
            Vector b = findvect(temp_input_coeff2, list, vector_list_size);
            Vector result;
            if (a.name[0] == '\0' || b.name[0] == '\0') { // if either vector is not found
                printf("VECTOR NOT FOUND\n");
                return;
            } else { // else perform subtraction and print result
                subtractVectors(a, b, &result);
                strcpy(result.name, "ans");
                printVector(result); 
            }
        } else {
            printf("Invalid Input: Please use the format A = B - C or B - C to subtract vectors\n");
            return; // Invalid input format
        }

    } else if (op == OP_dot) {
        if (sscanf(input, "%s = %s * %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position) == 3) {
            sscanf(input, "%s = %s * %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B * C or B * C to compute the dot product of vectors\n");
                return;
            }
            strToUpper(temp_name);
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size);
            Vector b = findvect(temp_input_coeff2, list, vector_list_size); // find vectors in list
            Vector c = findvect(temp_name, list, vector_list_size);
            Vector result;

            // if list is full, do not add another vector
            if (used_size == MAX_VECTORS && c.name[0] == '\0') {
                printf("%s ", promptInput);
                printf("Cannot add more vectors. List is full.\n");
                return;
            }

            if (c.name[0] != '\0') {
                dotProduct(a, b, &c); // perform dot product and store in existing vector
                modifyVector(c, list, vector_list_size); // modify existing vector in list
                printDot(c);
            } else {
                dotProduct(a, b, &result); // Perform dot product
                strcpy(result.name, temp_name); // Assign the name to the result vector
                addvect(result, list, vector_list_size); // Add the new vector to the list
                printDot(result);
            }

        } else if (sscanf(input, "%s * %s%n", temp_input_coeff1, temp_input_coeff2, &position) == 2) { // if no assignment
            sscanf(input, "%s * %s%n", temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B * C or B * C to compute the dot product of vectors\n");
                return;
            }
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size);
            Vector b = findvect(temp_input_coeff2, list, vector_list_size); // find vectors in list
            Vector result;
            if (a.name[0] == '\0' || b.name[0] == '\0') { // if either vector is not found
                printf("VECTOR NOT FOUND\n");
                return;
            } else {
                dotProduct(a, b, &result); // Perform dot product
                strcpy(result.name, "ans"); // Assign the name to the result vector
                printDot(result);
            }
        } else {
            printf("Invalid Input: Please use the format A = B * C or B * C to compute the dot product of vectors\n");
            return;
        }

    } else if (op == OP_cross) {
        if (sscanf(input, "%s = %s x %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position) == 3) {
            sscanf(input, "%s = %s x %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B x C or B x C to compute the cross product of vectors\n");
                return;
            }
            strToUpper(temp_name);
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size);
            Vector b = findvect(temp_input_coeff2, list, vector_list_size); // find vectors in list
            Vector c = findvect(temp_name, list, vector_list_size); 

            if (a.name[0] == '\0' || b.name[0] == '\0') {
                printf("VECTOR NOT FOUND\n"); // If either vector is not found
                return;
            }

            if (c.name[0] != '\0') { // if vector to be assigned already exists
                crossProduct(a, b, &c); // perform cross product and store in existing vector
                modifyVector(c, list, vector_list_size); // modify existing vector in list
                printVector(c);
            } else { // else create new vector
                Vector result;
                // else perform cross product and add new vector to list
                crossProduct(a, b, &result); // Perform cross product
                strcpy(result.name, temp_name);
                addvect(result, list, vector_list_size);
                printVector(result);
            }

        } else if (sscanf(input, "%s x %s%n", temp_input_coeff1, temp_input_coeff2, &position) == 2) { // if no assignment
            sscanf(input, "%s x %s%n", temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B x C or B x C to compute the cross product of vectors\n");
                return;
            }
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a = findvect(temp_input_coeff1, list, vector_list_size); // find vectors in list
            Vector b = findvect(temp_input_coeff2, list, vector_list_size);
            Vector result;
            if (a.name[0] == '\0' || b.name[0] == '\0') { // if either vector is not found
                printf("VECTOR NOT FOUND\n");
                return;
            } else { // else perform cross product and print result
                crossProduct(a, b, &result);
                strcpy(result.name, "ans");
                printVector(result);
            }
        } else { // invalid input format
            printf("Invalid Input: Please use the format A = B x C or B x C to add vectors\n");
            return;
        }
    } else if (op == OP_scalar) { // scalar multiplication
        if (sscanf(input, "%s = %s o %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position) == 3) {
            sscanf(input, "%s = %s o %s%n", temp_name, temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = B o Number to multiply vector by scalar\n");
                return;
            }
            strToUpper(temp_name);
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector result = findvect(temp_name, list, vector_list_size); // check if vector to be assigned already exists
            Vector a;
            double value;

            if (atof(temp_input_coeff1) != 0) { // check which input is the scalar
                value = atof(temp_input_coeff1); // convert string to double
                a = findvect(temp_input_coeff2, list, vector_list_size);
            } else if (atof(temp_input_coeff2) != 0) { // check which input is the scalar
                value = atof(temp_input_coeff2);
                a = findvect(temp_input_coeff1, list, vector_list_size);
            }

            if (a.name[0] == '\0' || value == 0) {
                printf("VECTOR NOT FOUND or scalar is zero\n"); // if vector not found or scalar is zero
                return;
            }

            // if vector already exists, modify it
            if (result.name[0] != '\0') {
                scalarMultiply(a, value, &result);
                modifyVector(result, list, vector_list_size); // modify existing vector in list
                printVector(result);
            } else { // else create new vector
                Vector result; 
                scalarMultiply(a, value, &result);
                strcpy(result.name, temp_name);
                addvect(result, list, vector_list_size);
                printVector(result);
            }

        } else if (sscanf(input, "%s o %s%n", temp_input_coeff1, temp_input_coeff2, &position) == 2) { // if no assignment
            sscanf(input, "%s o %s%n", temp_input_coeff1, temp_input_coeff2, &position);
            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A o B to multiply vector by scalar\n");
                return;
            }
            strToUpper(temp_input_coeff1); // Convert to uppercase
            strToUpper(temp_input_coeff2);
            Vector a;
            double value;
            if (atof(temp_input_coeff1) != 0) { // check which input is the scalar
                value = atof(temp_input_coeff1);
                a = findvect(temp_input_coeff2, list, vector_list_size);
            } else if (atof(temp_input_coeff2) != 0) {
                value = atof(temp_input_coeff2); // check which input is the scalar
                a = findvect(temp_input_coeff1, list, vector_list_size);
            }
    
            Vector result;
            if (a.name[0] == '\0' || value == 0) { // if vector not found or scalar is zero
                printf("VECTOR NOT FOUND or scalar is zero\n");
                return;
            } else { // else perform scalar multiplication and print result
                scalarMultiply(a, value, &result);
                strcpy(result.name, "ans");
                printVector(result);
            }
        } else { // invalid input format
            printf("Invalid Input: Please use the format A = B o C or B o C to add vectors\n");
            return;
        }
    } else if (op == OP_assign) { // vector assignment
        if (sscanf(input, "%s = %lf, %lf, %lf,", temp_name, &temp_x, &temp_y, &temp_z) == 4 ||
            sscanf(input, "%s = %lf, %lf, %lf", temp_name, &temp_x, &temp_y, &temp_z) == 4 ||
            sscanf(input, "%s = %lf, %lf %lf", temp_name, &temp_x, &temp_y, &temp_z) == 4 ||
            sscanf(input, "%s = %lf %lf, %lf", temp_name, &temp_x, &temp_y, &temp_z) == 4 ||
            sscanf(input, "%s = %lf %lf %lf", temp_name, &temp_x, &temp_y, &temp_z) == 4) { // Parse input

            

            // detect which kind of separators appear in the input
            if (sscanf(input, "%s = %lf, %lf, %lf,%n", temp_name, &temp_x, &temp_y, &temp_z, &position) == 4 ) {
                sscanf(input, "%s = %lf, %lf, %lf,%n", temp_name, &temp_x, &temp_y, &temp_z, &position); // assigning value to position
            } else if (sscanf(input, "%s = %lf, %lf, %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position) == 4 ) {
                sscanf(input, "%s = %lf, %lf, %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position); // assigning value to position
            } else if (sscanf(input, "%s = %lf, %lf %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position) == 4 ) {
                sscanf(input, "%s = %lf, %lf %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position); // assigning value to position
            } else if (sscanf(input, "%s = %lf %lf, %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position) == 4 ) {
                sscanf(input, "%s = %lf %lf, %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position); // assigning value to position
            } else if (sscanf(input, "%s = %lf %lf %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position) == 4 ) {
                sscanf(input, "%s = %lf %lf %lf%n", temp_name, &temp_x, &temp_y, &temp_z, &position); // assigning value to position
            }

            if (input[position] != '\0') {
                printf("Invalid Input: Please use the format A = x, y, z or A = x y z to assign a vector\n");
                return;
            }

            strToUpper(temp_name); // Convert to uppercase
            Vector temp = findvect(temp_name, list, vector_list_size);

            for (int i = 0; i < vector_list_size; i++) {
                if (list[i].name[0] == '\0' && temp.name[0] == '\0') { // if empty slot found and vector does not already exist
                    strcpy(list[i].name, temp_name);
                    list[i].x = temp_x;
                    list[i].y = temp_y;
                    list[i].z = temp_z;
                    break;
                } else if (strcmp(list[i].name, temp_name) == 0) { // if vector already exists, modify it
                    list[i].x = temp_x;
                    list[i].y = temp_y;
                    list[i].z = temp_z;
                    break;
                }
            }
        } else { // invalid input format
            printf("Invalid Input: Please use the format A = x, y, z or A = x y z to assign a vector\n");
        }
    } else if (op == OP_none) { // if no operator found, assume user wants to print vector
        strToUpper(input);
        Vector temp = findvect(input, list, vector_list_size);
        if (temp.name[0] != '\0') {
            printVector(temp);
        } else {
            printf("VECTOR NOT FOUND\n");
        }
    } else { // invalid operator
        printf("Invalid Input: Please use one of the following operators: + - * x o =\n");
    }

}

Operator determineOperator(char *input) { // Determine the operator in the input string
    Operator op = OP_none;
    for (int i = 0; input[i] != '\0'; ++i) {
        switch (input[i]) {
            case '+':
                op = OP_add;
            break;
            case '-':
                op = OP_sub;
            break;
            case '*':
                op = OP_dot;
            break;
            case '=':
                op = OP_assign;
            break;
            case 'x':
                op = OP_cross;
            break;
            case 'o':
                op = OP_scalar;
            break;
            default:
            break;
        }
    }
    return op;
}


int verifyFile(char *input) { 
    FILE* fp;
    char data[INPUT_SIZE]; // data stream
    int fileSize; // amount of vectors in file
    fp = fopen(input, "r"); // reading file only

    if (fp == NULL) { // return 1 whenever there is an error
        printf("File does not exist\n"); 
        return 1;
    } else if (checkCSV(input) == 0) {
        printf("Invalid filetype. Can only write "".csv"" files\n"); // only allows csv files to be opened
        return 1;
    }

    while (fgets(data, INPUT_SIZE, fp) != NULL) {
        fileSize++; // counts the amount of rows of text (does not verify if correct)
    }
    fclose(fp);
    return fileSize; // returns the size (amount of vectors) present in the file
}

void openCSV(char *input, Vector *vlist) {
    FILE* fp;
    char data[INPUT_SIZE];
    fp = fopen(input, "r"); // reading file oly
    int position = 0;

    if (fp == NULL) {
        printf("An error has ocurred\n"); // if an error somehow occurs
        return;
    }

    while (fgets(data, INPUT_SIZE, fp) != NULL) {
        char name[INPUT_SIZE];
        double x;
        double y;
        double z;

        // accepts only valid data inputs, then writes it into the vlist array
        if (sscanf(data, "%[^,],%lf,%lf,%lf", name, &x, &y, &z) == 4) { // %s did not account for comma, need to use special scanning function
            Vector temp;
            strcpy(temp.name, name);
            temp.x = x;
            temp.y = y;
            temp.z = z;
            vlist[position] = temp;
            position++;
        }
    }
    fclose(fp);

}

void writeCSV(char *input, Vector *vlist, int vList_used) {
    char filename[INPUT_SIZE];
    char *csv = ".csv"; // text to append at the end of input
    int position;
    
    if (sscanf(input, "%s%n", filename, &position) == 1) {

      
        sscanf(input, "%s%n", filename, &position);

        if (filename[position] != '\0') {
            printf("Invalid Filename, proper file name is as follows ""example.csv"" or ""example"" \n");
            // verification for proper input
            return;
        }

        if (checkCSV(input) != 0) { 
            strcpy(filename, input); // if the filename does contain .csv at the end, copy input into filename
            filename[strcspn(filename, "\n")] = '\0';
        } else {
            strcat(filename, csv); // if filename does not contain, append .csv at the end
            filename[strcspn(filename, "\n")] = '\0';
        }

        FILE *fp;
        fp = fopen(filename, "w+"); // write and overwrite if present
        if (fp == NULL) {
            printf("Error creating or opening the file!\n");
            return; // Indicate an error
        }

        for (int i = 0; i < vList_used; i++) {
            Vector temp = vlist[i]; // writing into the list
            fprintf(fp, "%s,%.1f,%.1f,%.1f\n", temp.name, temp.x, temp.y, temp.z);
        }
        fclose(fp);
    } else {
        printf("Incorrect naming format, please use correct format (i.e. list.csv or list)\n");
    }

}

int checkCSV(char *input) {
    strToLower(input);
    int length = strlen(input);

    return length >= 4 && strcmp(input + length - 4, ".csv") == 0;
}
