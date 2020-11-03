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

int insertion(int *array);
int quicksort(int *array, int from, int to, int posMin);
int partition(int *array, int from, int to);
void swap(int *array, int i, int j);

int main(){

    int toOrdinate[2000];
    int *array=toOrdinate;
    int size = insertion(array);
    
    int posMin;
    scanf("%d", &posMin);

    int min = quicksort(array, 0, (size-1), (posMin-1));
    printf("%d\n", min);
    return 0;
}

int insertion(int *array){
    char lista[6000];
    fgets(lista, 6000, stdin);
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


int quicksort(int *array, int from, int to, int posMin)
{
    int r = partition(array, from, to);
    
    if(posMin==r)
    {
        return array[posMin];
    }
    else if(posMin<r)
    {
        quicksort(array, from, r-1, posMin);
    }
    else
    {
        quicksort(array, r+1, to, posMin);
    }
}

//fa la partizione di numeri minori e maggiori di un perno e ritorna il perno
int partition(int *array, int from, int to)
{
    int x = array[to];
    int median = from-1;

    for (int j=from; j<to; j++)
    {
        if(array[j]<x)
        {
            median++;
            swap(array, median, j);
        }
    }

    median++;
    swap(array, median, to);

    return median;
}

//scambia due valori di posizioni i e j nell'array fornito
void swap(int *array, int i, int j)
{
    int temp = *(array +i);
    *(array +i) = *(array +j);
    *(array +j) = temp;
}