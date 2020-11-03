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

int Insertion(int *array);
int Median(int *array, int k, int from, int to, int lastNum, int fullsize);
int Meds(int *array, int from, int to, int lastNum, int fullsize);
int Partition(int *array, int from, int to);
void Swap(int *array, int i, int j);
int PartitionFixed(int *array, int from, int to, int posMedOfMed);

int main(){

    int toOrdinate[5000];
    int *array=toOrdinate;
    int numberInserted = Insertion(array);    

    int k=3;
    //scanf("%d", &k);

    int min = Median(array, (k-1), 0, 4, (numberInserted-1), numberInserted);
    printf("%d", min);

    return 0;
}

//inserisce i valori nell'array
int Insertion(int *array){
    char lista[] = " 91 32 4 3 -11 17 80 173 55 513 20 -19";
    //fgets(lista, 8000, stdin);
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
int Median(int *array, int k, int from, int to, int lastNum, int fullsize){
    int newsize=fullsize;
    int posMedOfMed=from;

    if(from!=lastNum){
        if(to>lastNum){
            to=lastNum;
        }
        newsize = Meds(array, from, to, lastNum, fullsize);
        posMedOfMed = Partition(array, fullsize, (newsize-1)) -fullsize +from;
        posMedOfMed = PartitionFixed(array, from, lastNum, posMedOfMed);
    }
    
    if(k==posMedOfMed){
        return array[posMedOfMed];
    }else if(k<posMedOfMed){
        Median(array, k, from, (from+4), (posMedOfMed-1), newsize);
    }else{
        Median(array, k, (posMedOfMed+1), (posMedOfMed+5), lastNum, newsize);
    }
}

int Meds(int *array, int from, int to, int lastNum, int fullsize){
    int newsize=fullsize;
    while(to<=lastNum){   
        int posMed = Partition(array, from, to);

        array[newsize]=array[posMed];
        newsize++;
        from=from+5;

        if((0<(lastNum-to)) && ((lastNum-to)<5)){//quantity of the last block
            to=lastNum;
        }else{
            to=to+5;
        }
    }
    return newsize;
}

//fa la partizione di numeri minori e maggiori di un perno e ritorna il perno
int Partition(int *array, int from, int to){
    int x = array[to];
    int median = from-1;

    for (int j=from; j<to; j++){
        if(array[j]<=x){
            median++;
            Swap(array, median, j);
        }
    }
    median++;
    Swap(array, median, to);
    return median;
}

//scambia due valori di posizioni i e j nell'array fornito
void Swap(int *array, int i, int j){
    int temp = *(array +i);
    *(array +i) = *(array +j);
    *(array +j) = temp;
}

int PartitionFixed(int *array, int from, int to, int posMedOfMed){
    Swap(array, posMedOfMed, to);
    int median = from-1;

    for(int j=from; j<to; j++){
        if(array[j]<=array[to]){
            median++;
            Swap(array, median, j);
        }
    }
    median++;
    Swap(array, median, to);
    return median;
}

/*

---------------------vecchio median-----------------

int Median(int *array, int k, int from, int to, int lastNum, int fullsize){

    int newsize=fullsize;
    while(to<=lastNum)
    {   
        int posMed = Partition(array, from, to);

        for (int i = 0; i <=lastNum; i++)
        {
            printf("%d ", array[i]);
        }
        putchar('\n');

        newsize++;
        array[newsize]=array[posMed];
        from=from+5;

        if((0<(lastNum-to)) && ((lastNum-to)<5)){//quantity of the last block
            to=lastNum;
        }else{
            to=to+5;
        }
    }

    int posMedOfMed = Partition(array, fullsize, newsize) -fullsize;
    
    printf("%d\n\n", posMedOfMed);
    
    if(k==posMedOfMed){
        return array[posMedOfMed];
    }else if(k<posMedOfMed){
        Median(array, k, 0, 5, (posMedOfMed-1), newsize);
    }else{
        Median(array, k, (posMedOfMed+1), (posMedOfMed+6), lastNum, newsize);
    }
}

*/