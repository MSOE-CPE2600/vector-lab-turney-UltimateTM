# Vector Calculator with Dynamic Memory Allocation 
## Description
The purposes of this program is to conduct vector operations, allowing for functions such
as adding, subtracting, dot product, cross product, and scalar multiplications of vectors. Conducting operations saves the resulting saved vectors in a list which dynamically expands when passing an initial capacity of 10 vectors. Additionally, you may view this list, delete the list, export as a CSV, and even import an outside list if it is formatted correctly.

## How to Build the Program
To build the program, use the following command:

gcc -Wall -o vec_calculator main.c vector_operations.c input.c -lm

This allows all warning, renames the exe to "vec_calculator" and includes all important .c files and loads the math library for conducting vector operation math

## How to Run the Program
To run the program, open command line and input the following command

./vec_calculator

This will run and start the program

Follow the prompts given at the start of the program to run the program

To perform operations, use the format A = B + C or B + C to add vectors, A = B - C or B - C to subtract vectors, A = B * C or B * C for dot product, A = B x C or B x C for cross product, A = B o n or B o n to multiply vector B by scalar n

## Commands Supported by Program
**list**: Prints out a list of all currently stored vectors in the vector list 

**fill**: Fills the list with 10 vectors. Testing for dynamic memory

**clear**: Clears the list of vectors

**open**: Opens a .csv file. User enters name. File must be present in project directory for it to work.

**write**: Writes into a .csv file the list of vectors.

**quit**: quits the program

## How this Program uses Dynamic Memory
This program uses dynamic memory throught the use of the **malloc()** function on the vList array, which stores Vectors. This list will dynamically expand depending on if the local variable we track, vList_used, is equal to vList_size. The function **realloc()** will run by first adding the initial capacity (10 vectors) to vList_size, increasing the array by size 10. If the **realloc()** is successfull, vList_size will be increased by 10. The **realloc()** occurs whenever vList_used is equal to vList_size. At the end of the program, **free()** will be ran to free up the space in memory taken up by the array. 