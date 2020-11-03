/*

    L'algoritmo è basato sulla suddivisione del vettore fornito in input in blocchi di dimensione limitata
    e sul calcolo della mediana delle mediane. Più precisamente, l'algoritmo esegue le seguenti operazioni:
    - divisione dell'array in blocchi di 5 elementi, escluso eventualmente l'ultimo blocco che potrà
    contenere meno di 5 elementi,
    - ordinamento e calcolo della mediana di ciascun blocco,
    - calcolo della mediana M delle mediate dei blocchi, attraverso chiamata ricorsiva allo stesso algoritmo
    - partizionamento dell'intero array attorno alla mediana M, attraverso una variante della procedura
    "partition" dell'algoritmo "quick sort"
    - chiamata ricorsiva nella parte di array che sta a sinistra o a destra della mediana M, in funzione
    del valore k fornito in input.
    Il modo più semplice per implementare quest'algoritmo consiste nell'allocare, ad ogni chiamata
    ricorsiva, un nuovo vettore per memorizzare le mediane dei blocchi. Esiste tuttavia un approccio più
    efficiente e "in place" che riutilizza lo spazio allocato per il vettore originariamente fornito in
    input. La valutazione del progetto terrà conto della variante implementata (quella "in place",
    essendo più complicata ma anche più efficiente, sarà valutata con un punteggio più alto).
    Indipendentemente dalla variante implementata, nel caso pessimo l'algoritmo dovrà avere complessità,
    sia temporale che spaziale, pari a Θ(n).

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1

int insertion(int *array);
int median(int *array, int k, int first, int last);
int medOfMed(int *array, int from, int to);
int partitionFixed(int *array, int from, int to, int median);
void insertionsort(int *array, int from, int to);
void swapMed(int *array, int i, int j);
int min(int first, int second);

int main(){

    int toOrdinate[5000];
    int *array=toOrdinate;
    int size = insertion(array);    

    int k;
    scanf("%d", &k);

    int min = median(array, k, 0, size);
    printf("%d", min);

    return 0;
}

//inserisce i valori nell'array
int insertion(int *array){
    char lista[8000];
    fgets(lista, 8000, stdin);
	char *value=strtok(lista, " \n");

    int numberInserted=0;
	while(value!=NULL){
        array[numberInserted]=atoi(value);
        numberInserted++;
		value=strtok(NULL, " \n");
	}

    return numberInserted;
}

//ritorna il k-esimo minimo usando median-of-median
int median(int *array, int k, int from, int to)
{
    int median;
    int posMed;

    while(true)
    {
        median = medOfMed(array, from, to);
        posMed = partitionFixed(array, from, (to -1), median);
        int position = posMed -from +1;

        if(k < position)
        {
            to = posMed;
        }
        else if(k > position)
        {
            from = posMed +1;
            k = k -position;
        }
        else
        {
            break;
        }
    }
    
    return array[posMed];
}

int medOfMed(int *array, int from, int to)
{
    int blockSize = 5;

    if(from>=(to-1))
    {
        return array[from];
    }
    else
    {
        int difference = to -from;
        int quantity = (difference/blockSize) + min(1, difference%blockSize);
        int position = 0;
        int block[quantity];

        for(int i=from; i<to; i=i+blockSize)
        {
            int last = min((i +blockSize -1), (to -1));
            insertionsort(array, i, last);
            block[position++] = array[(i + last)/2];
        }
        
        return medOfMed(block, 0, quantity);
    }
}

int partitionFixed(int *array, int from, int to, int median)
{
    int i = from;
    int j = to;
    int val = -1;

    while(i <= j)
    {
        if(array[i] <= median)
        {
            if(array[i] == median)
            {
                val = i;
            }

            i++;
        }
        else
        {
            swapMed(array, j, i);
            j--;
        }
    }

    if(val >= 0)
    {
        swapMed(array, j, val);
    }

    return j;
}

void insertionsort(int *array, int from, int to)
{
    for(int j=(from+1); j<(to+1); j++)
    {
        int key = array[j];
        int i = j -1;

        while((i>=from) && (array[i]>key))
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

void swapMed(int *array, int i, int j)
{
    int temp = *(array +i);
    *(array +i) = *(array +j);
    *(array +j) = temp;
}

int min(int first, int second)
{
    if(first<second)
    {
        return first;
    }
    else
    {
        return second;
    }
}