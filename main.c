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
void selectionSort(entry_t *data, int numberOfEntries);
void insertionSort(entry_t *data, int numberOfEntries);
void shellSort(entry_t *data, int numberOfEntries);

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
    for(int i = 0; i<numberOfEntries; i++){
        for (int j = 0; j < data[i].lenght; ++j) {
            printf("%d ", data[i].array[j]);
        }
        printf("\n");
    }

    //selectionSort(data, numberOfEntries);
    //insertionSort(data, numberOfEntries);
    shellSort(data, numberOfEntries);

}

void readFile(entry_t data[], int numberOfEntries) {

    for(int i = 0; i<numberOfEntries; i++){
        fscanf(fp_read, "%d", &data[i].lenght);
            for (int j = 0; j < data[i].lenght; ++j) {
                fscanf(fp_read, "%d", &data[i].array[j]);
            }
    }
}


void selectionSort(entry_t *data, int numEntries) {
    /*RIPASSINO
     * Il selection sort è un algoritmo in-place: solo array e la variabile temp sono usati.
     * Ad ogni iterazione, prende il valore minore della sequenza non ordinata e lo sposta nella sequenza ordinata.
     * All'inizio la sequenza non ordinata ha lunghezza N-1; l'altra 0.
     * Poi, una decrementa unitamente all'altra che incrementa (sempre di uno)
     * */
    printf("Selection sort:\n");
    for (int i = 0; i < numEntries; i++) {//Cioé applico l'algoritmo per ogni array nel file
        int posMin, temp, swaps = 0, comparisons = 0;

        //Qui scanno l'intero array da 0 a N-1
        for (int n = 0; n < data[i].lenght; n++) {
            posMin = n; //Il primo elemento viene settato come minimo, per procedura

            for (int j = (n + 1); j < data[i].lenght; ++j) {
                //Cioé scanno il right subarray (non ordinato)

                if (data[i].array[j] < data[i].array[posMin]) {
                    comparisons++;
                    //Ho trovato un nuovo minimo nel right subarray
                    posMin = j;
                    //quindi scambio gli indici
                }
            }
            //finito di scannare il right subarray nella sua interezza

            if (posMin != n) { //li scambio se gli indici non combaciano
                //Cioé, ho trovato un nuovo minimo che non era in posizione posMin
                swaps++;
                temp = data[i].array[n];
                data[i].array[n] = data[i].array[posMin];
                data[i].array[posMin] = temp;
            }
        }
        printf("Number of comparisons (%d) and swaps (%d)\n", comparisons, swaps);
        //finito di scannare tutti gli array
    }


    //Fine ciclo
    for (int j = 0; j < numEntries; j++) {
        for (int i = 0; i < data[j].lenght; i++) {
            printf("%d ", data[j].array[i]);
        }
        printf("\n");
    }
    printf("\n");
}

void insertionSort(entry_t *data, int numberOfEntries){
    /*
     * In place and stable.
     * Idealmente l'array ha due sottosequenze: l e r, da 1 e N-1 elementi rispettivamente.
     * (L'array da un elemento è ordinato per definizione mentre si scorre, si inserisce
     * l'elemento dall'array non ordinato in quello ordinato, mantenendo invariata questa proprietà
     * Il subarray di sinistra è scannato fino a quando non si trova un elemento per cui Aj > ai, mentre
     * il destro viene spostato di una posizione verso destra */

    //Qui ciclo tra tutti i vettori del file
    for(int entry = 0; entry<numberOfEntries; entry++){
        //Inizializzo le variabili del caso
        int pos, insertions = 0, comparisons = 0, valueToCompare;

        for(int l = 1; l < data[entry].lenght; l++){
            //Cioé, scorro sul vettore. All'inizio ho come array ordinato data[entry].array[i = 0] quindi parto da i = 1.
            valueToCompare = data[entry].array[l];
            pos = l - 1; //Sarebbe l'indice che scorre nel left-sub array

            while(pos>=0&& valueToCompare < data[entry].array[pos]){
                data[entry].array[pos+1] = data[entry].array[pos];
                pos--;
            }
            data[entry].array[pos+1] = valueToCompare;
        }
    }
    for (int j = 0; j < numberOfEntries; j++) {
        for (int i = 0; i < data[j].lenght; i++) {
            printf("%d ", data[j].array[i]);
        }
        printf("\n");
    }
    printf("\n");
}

void shellSort(entry_t *data, int numberOfEntries){
    /*
     * Questo è shell sort, cominciamo
     * é un insertion sort che però confronta elementi anche lontani, distanti h. h decresce fino a diventare 1 (quindi
     * scambi tra celle adiacenti). H si può scegliere in base a diverse sequenze: verrà usato Knuth.
     * */
    for(int entry = 0; entry < numberOfEntries; entry++) {
        int i, j, x, h = 1, l=0, r = data[entry].lenght -1;

        while (h <= data[entry].lenght) {
            h = 3*h - 1; //Sequenza di knuth
        }

        while(h>=1){ //condizione per la quale eseguo i confronti.
            for(i = l+h; i <= r; i++){
                j = i; x = data[entry].array[i];

                while (j >= l + h && x < data[entry].array[j-h]){
                    data[entry].array[j] = data[entry].array[j-h];
                    j -= h;
                }

                data[entry].array[j] = x;

            }
            h = h/3;
        }
    }
    for (int j = 0; j < numberOfEntries; j++) {
        for (int i = 0; i < data[j].lenght; i++) {
            printf("%d ", data[j].array[i]);
        }
        printf("\n");
    }
    printf("\n");
}