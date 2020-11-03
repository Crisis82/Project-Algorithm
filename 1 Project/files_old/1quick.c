/*

    Si tratta di una variante dell'algoritmo di ordinamento "quick sort", in cui ogni chiamata
    ricorsiva su un intervallo [i,j] del vettore fornito in input termina in tempo costante ogniqualvolta
    il parametro k non sia contenuto nell'intervallo [i,j]. L'algoritmo deve avere complessità
    temporale asintotica Θ(n^2) nel caso pessimo e O(n) nel caso medio, dove n è il numero di elementi
    del vettore.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Insertion(int *array);
void Quicksort(int *array, int p, int q, int posMin);
int Partition(int *array, int p, int q);
void Swap(int *array, int i, int j);

int main(){

    int toOrdinate[2000];
    int *array=toOrdinate;
    int size = Insertion(array);
    
    int posMin=4;
    //scanf("%d", &posMin);

    Quicksort(array, 0, (size-1), (posMin-1));
    printf("%d\n", toOrdinate[posMin-1]);
    return 0;
}

int Insertion(int *array){
    char lista[]="12 3 1 2 17 29 35 6 43 22";
    //fgets(lista, 6000, stdin);
	char *value=strtok(lista, " \n");

	int size=0;

	while(value!=NULL){
		*array=atoi(value);
		array++;
		size++;
		value=strtok(NULL, " \n");
	}

    return size;
}

void Quicksort(int *array, int p, int q, int posMin){
    if(p<q){
        int r = Partition(array, p, q);
        
        if(posMin!=r){
            if(posMin<r){
                Quicksort(array, p, r-1, posMin);
            }else{
                Quicksort(array, r+1, q, posMin);
            }
        }
    }
}

int Partition(int *array, int p, int q){
    int x = array[q];
    int i = p-1;

    for (int j=p; j<q; j++){
        if(array[j]<=x){
            i=i+1;
            Swap(array, i, j);
        }
    }
    i=i+1;
    Swap(array, i, q);
    return i;    
}

void Swap(int *array, int i, int j){
    int temp = *(array+i);
    *(array+i) = *(array+j);
    *(array+j) = temp;
}