/*
 Skills: iterative sorting algorithms, empirical complexity analysis
Evaluation of sorting algorithms
Consider the following sorting algorithms to sort vectors of integers in ascending order:
• Selection Sort
• Insertion Sort
• Shell Sort
Write a C program that acquires numerical sequences from a file (sort.txt) and calls all the
above-mentioned sorting algorithms on each sequence, printing the following output on the screen:
• the number of swaps
• the number of iterations of the outer loop
• per each iteration of the outer loop, the number of iterations of the inner loop
• the total number of iterations.
The file sort.txt has the following format:
• the first line reports the number S of numerical sequences that will follow
• in the following S lines, one per line:
<length> <sequence>
where <length> is a positive integer (at most 100) representing the length of the sequence
reported in the current line, and <sequence> is a sequence of <length> integer values
separated by a space.
Example of file sort.txt:
4
5 1 2 3 4 5
5 1 2 3 4 0
5 5 4 3 2 1
5 1 5 2 4 3
 * */

#include <stdio.h>
#include <stdlib.h>

#define filepos "../sort.txt"
#define maxLenght 100

typedef struct {
    int lenght;
    int array[maxLenght];
} entry_t;

FILE *fp_read;

void readFile(entry_t data[], int numEntries);
void selectionSort();
void insertionSort();
void shellSort();

int main() {
    fp_read = fopen(filepos, "r");
    if(fp_read==NULL){
        printf("Errore nell'apertura del file. \n");
        exit(1);
    }
    int numberOfEntries;
    fscanf(fp_read, "%d ", &numberOfEntries);
    printf("Number of entries is %d \n", numberOfEntries);
    entry_t data[numberOfEntries];
    readFile(data, numberOfEntries);
    fclose(fp_read);
}

void readFile(entry_t data[], int numberOfEntries) {

    for(int i = 0; i<numberOfEntries; i++){
        fscanf(fp_read, "%d", &data[i].lenght);
            for (int j = 0; j < data[i].lenght; ++j) {
                fscanf(fp_read, "%d", &data[i].array[j]);
                printf("%d ", data[i].array[j]);
            }
            printf("\n");
    }
}