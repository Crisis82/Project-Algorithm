/*

    Questo algoritmo di selezione utilizza due min-heap, denominate H1 e H2. La prima heap H1 é
    costruita a partire dal vettore fornito in input in tempo lineare e non viene modificata. La
    seconda heap H2 contiene inizialmente un solo nodo, corrispondente alla radice di H1. All'i-esima
    iterazione, per i che va da 1 a k−1, l'algoritmo estrae la radice di H2, che corrisponde a un nodo
    xi in H1, e reinserisce in H2 i nodi successori (figli sinistro e destro) di xi nella heap H1. Dopo
    k−1 iterazioni, la radice di H2 corrisponderà al k-esimo elemento più piccolo del vettore fornito in
    input.
    L'algoritmo descritto ha complessità temporale O(n+klogk) sia nel caso pessimo che in quello medio.
    Per k sufficientemente piccolo, quindi, l'algoritmo "heap select" sarà preferibile, almeno nel caso
    pessimo, all'algoritmo "quick select". È possibile implementare una variante che utilizzi opportunamente
    min-heap o max-heap, a seconda del valore di k.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int insertion(int *array);
void createMinHeap(int *h1, int size);
void heapify(int *h1, int pos, int size);
void swapHeap(int *array, int i, int j);
int get(int *h1, int *h2, int k, int size);
int left(int pos);
int right(int pos);
void heapifySupport(int *h1, int *h2, int pos, int sizeSupport);
void control(int *h1, int *h2, int pos);

int main()
{
    int toOrdinate[2000];
    int *h1=toOrdinate;
    int size = insertion(h1);
    
    int k;
    scanf("%d", &k);

    createMinHeap(h1, size);
    int h2[size];
    
    int min = get(h1, h2, k, size);
    printf("%d", min);

    return 0;
}

int insertion(int *array)
{
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

void createMinHeap(int *h1, int size)
{
    for(int i=(size/2); i>=0; i--)
    {
        heapify(h1, i, size);
    }
}

void heapify(int *heap, int pos, int size)
{
    int left = 2*pos +1;
    int right = 2*pos +2;
    int posMin = pos;

    if((left<size) && (heap[left]<heap[posMin]))
    {
        posMin = left;
    }

    if((right<size) && (heap[right]<heap[posMin]))
    {
        posMin = right;
    }

    if(posMin!=pos)
    {
        swapHeap(heap, pos, posMin);
        heapify(heap, posMin, size);
    }
}

void swapHeap(int *array, int i, int j)
{
    int temp = *(array +i);
    *(array +i) = *(array +j);
    *(array +j) = temp;
}

int get(int *h1, int *h2, int k, int size)
{
    *(h2) = 0;
    int sizeSupport = 1;

    for(int i=0; i<(k-1); i++)
    {
        int posMin = h2[0];
        sizeSupport--;

        if(sizeSupport>0)
        {
            swapHeap(h2, 0, sizeSupport);
            heapifySupport(h1, h2, 0, sizeSupport);
        }

        if(left(posMin) < size)
        {
            *(h2 + sizeSupport) = left(posMin);
            control(h1, h2, sizeSupport);
            sizeSupport++;

            if(right(posMin) < size)
            {
                *(h2 + sizeSupport) = right(posMin);
                control(h1, h2, sizeSupport);
                sizeSupport++;
            }
        }
    }

    return h1[h2[0]];
}

int left(int pos)
{
    return 2*pos +1;
}

int right(int pos)
{
    return 2*pos +2;
}

void heapifySupport(int *h1, int *h2, int pos, int sizeSupport)
{
    int left = 2*pos +1;
    int right = 2*pos +2;
    int posMin = pos;

    if((left<sizeSupport) && (h1[h2[left]]<h1[h2[posMin]]))
    {
        posMin = left;
    }

    if((right<sizeSupport) && (h1[h2[right]]<h1[h2[posMin]]))
    {
        posMin = right;
    }

    if(posMin!=pos)
    {
        swapHeap(h2, pos, posMin);
        heapifySupport(h1, h2, posMin, sizeSupport);
    }
}

void control(int *h1, int *h2, int pos)
{
    while((pos>0) && (h1[h2[pos]] < h1[h2[((pos-1)/2)]]))
    {
        swapHeap(h2, pos, ((pos-1)/2));
        pos = ((pos-1)/2);
    }
}