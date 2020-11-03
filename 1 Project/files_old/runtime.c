#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <limits.h>

struct minHeap{
    int val;
    int index;
    struct minHeap *next;
};

typedef struct minHeap MinHeap;
struct timespec first_start, second_start, third_start, first_end, second_end, third_end;

int randomInt(int from, int to);

void quickSelect(int *input, int k, int size);
void Insertion(int *array, int *input, int size);
void Quicksort(int *array, int p, int q, int posMin);
int Partition(int *array, int p, int q);
void Swap(int *array, int i, int j);

void heapSelect(int *input, int k, int size);
int Build(MinHeap **root, int *input, int heapsize, int size);
MinHeap *newNode(MinHeap *node, int value);
MinHeap *OrderMin(MinHeap *root, int heapsize);
MinHeap *OrderMax(MinHeap *root, int heapsize);
void printMinHeap(MinHeap *root);
void GetMin(MinHeap *h1, MinHeap *h2, int k, int length);
void GetMax(MinHeap *h1, MinHeap *h2, int k, int length);
int GetVal(MinHeap *h1, int child);
int Length(MinHeap *node);
MinHeap *newNodeIndex(MinHeap *node, int value, int index);
MinHeap *HeapifyMin(MinHeap *root, int pos, int length);
MinHeap *HeapifyMax(MinHeap *root, int pos, int length);
MinHeap **GetNode(MinHeap **root, int pos);
void SwapHeap(MinHeap **first, MinHeap **second);
void freeHeap(MinHeap *root);

void medianSelect(int *input, int k, int size);
int Median(int *array, int k, int from, int to, int lastNum, int fullsize);
int Meds(int *array, int from, int to, int lastNum, int fullsize);
int PartitionFixed(int *array, int from, int to, int posMedOfMed);



int main(){

    srand(time(NULL));
    int n = randomInt(100, 1000);
    int m = 0;
    srand(n);
    int size = randomInt(1000, 10000);
    srand(size);
    int k = randomInt(1, size);

    double p1[n];
    double T1 = 0;
    double D1 = 0;
    double p2[n];
    double T2 = 0;
    double D2 = 0;
    double p3[n];
    double T3 = 0;
    double D3 = 0;

    while(m<n)
    {
        srand(m);
        int input[size];
        for(int i=0; i<size; i++){
            input[i]=randomInt(-10000, 10000);
        }

        /*
        //print the array random values
        for(int i=0; i<size; i++){
            printf("%d ", input[i]);
        }
        */

        //start first timer and first program
        clock_gettime(CLOCK_MONOTONIC, &first_start);

        quickSelect(input, k, size);

        clock_gettime(CLOCK_MONOTONIC, &first_end);

        double first_time_spent = (first_end.tv_sec - first_start.tv_sec) * 1e9; 
        first_time_spent = (first_time_spent + (first_end.tv_nsec - first_start.tv_nsec)) * 1e-9; 

        p1[m] = first_time_spent;
        T1 = T1 + first_time_spent;
        //printf("T1:\t%f\t", first_time_spent);
        //end of first program
        //start of the second
        clock_gettime(CLOCK_MONOTONIC, &second_start);

        heapSelect(input, k, size);

        clock_gettime(CLOCK_MONOTONIC, &second_end);

        double second_time_spent = (second_end.tv_sec - second_start.tv_sec) * 1e9; 
        second_time_spent = (second_time_spent + (second_end.tv_nsec - second_start.tv_nsec)) * 1e-9;

        p2[m] = second_time_spent;
        T2 = T2 + second_time_spent;
        //printf("T2:\t%f\t", second_time_spent);
        //end of second program
        //start of the third
        clock_gettime(CLOCK_MONOTONIC, &third_start);

        medianSelect(input, k, size);

        clock_gettime(CLOCK_MONOTONIC, &third_end);

        double third_time_spent = (third_end.tv_sec - third_start.tv_sec) * 1e9; 
        third_time_spent = (third_time_spent + (third_end.tv_nsec - third_start.tv_nsec)) * 1e-9; 

        p3[m] = third_time_spent;
        T3 = T3 + third_time_spent;
        //printf("T3:\t%f\n", third_time_spent);
        //end of third program
        
        m++;
    }

    T1 = T1/n;
    T2 = T2/n;
    T3 = T3/n;

    for(m=0; m<n; m++){
        D1 = D1 + (T1 - p1[m])*(T1 - p1[m]);
        D2 = D2 + (T2 - p2[m])*(T2 - p2[m]);
        D3 = D3 + (T3 - p3[m])*(T3 - p3[m]);
    }

    D1 = sqrt(D1/n);
    D2 = sqrt(D2/n);
    D3 = sqrt(D3/n);
    
    printf("size:%d k:%d T1:%f D1:%f T2:%f D2:%f T3:%f D3:%f", size, k, T1, D1, T2, D2, T3, D3);

    return 0;
}

int randomInt(int from, int to)
{
    int num = (rand()%(to-from+1) + from);
    return num;
}

void quickSelect(int *input, int k, int size)
{
    Quicksort(input, 0, (size-1), (k-1));
    //printf("%d ", input[k-1]);
}



void Insertion(int *array, int *input, int size)
{
	for(int i=0; i<size; i++){
        array[i]=input[i];
    }
}

void Quicksort(int *array, int p, int q, int posMin)
{
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

int Partition(int *array, int p, int q)
{
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

void Swap(int *array, int i, int j)
{
    int temp = *(array+i);
    *(array+i) = *(array+j);
    *(array+j) = temp;
}

void heapSelect(int *input, int k, int size)
{
    //crea la heap h1 e salva i valori in essa
    MinHeap *h1=NULL;
    int heapsize = Build(&h1, input, 0, size);

    //trova il minimo usando la heap ausiliaria h2 e lo stampa
    //ottimizza ordinando h1 come min-heap o max-heap in base al valore di k e alla sua dimensione
    MinHeap *h2=NULL;
    
    if(k<=(ceil(heapsize/2))){
        h1=OrderMin(h1, heapsize);
        h2=newNode(NULL, h1->val);
        h2->index=1;
        GetMin(h1, h2, k, heapsize);
    }else{
        h1=OrderMax(h1, heapsize);
        h2=newNode(NULL, h1->val);
        h2->index=1;
        k=heapsize -k +1;
        GetMax(h1, h2, k, heapsize);
    }

    freeHeap(h1);
    freeHeap(h2);
}


//costruisce la heap
int Build(MinHeap **root, int *input, int heapsize, int size)
{
    if(size!=heapsize){
        (*root) = newNode((*root), input[heapsize]);
        heapsize++;
        Build(root, input, heapsize, size);
    }else{
        return heapsize;
    }
}

//crea un nuovo nodo
MinHeap *newNode(MinHeap *node, int value)
{
    MinHeap *newNode = NULL;
    newNode=(MinHeap *) malloc(sizeof(MinHeap));
    newNode->val=value;
    newNode->next=node;
    return newNode;
}

//ordina la heap restituendo una min-heap
MinHeap *OrderMin(MinHeap *root, int heapsize)
{
    if(heapsize==1){
        return root;
    }else{
        for(int i=(heapsize/2); i>0; i--){
            root = HeapifyMin(root, i, heapsize);
        }
    }
}

//ordina la heap restituendo una max-heap
MinHeap *OrderMax(MinHeap *root, int heapsize)
{
    if(heapsize==1){
        return root;
    }else{
        for(int i=(heapsize/2); i>0; i--){
            root = HeapifyMax(root, i, heapsize);
        }
    }
}

//stampa la heap
void printMinHeap(MinHeap *root)
{
    if(root==NULL){
        printf("\n");
    }else{
        printf("%d ", root->val);
        printMinHeap(root->next);
    }
}

//metodo per ottenere il k-esimo valore minimo della heap
void GetMin(MinHeap *h1, MinHeap *h2, int k, int heapsize)
{
    if(k>1){
        int index = 2*(h2->index); //salvo l'indice della radice della heap h2
        int left;
        int right;
        h2 = h2->next; //rimuovo la radice di h2

        if(index<=heapsize){ //se la radice aveva un figlio sinistro in h1 lo inserisce in h2
            left = GetVal(h1, index);
            h2 = newNodeIndex(h2, left, index);
        }

        if((index+1)<=heapsize){ //se la radice aveva un figlio destro in h1 lo inserisce in h2
            right = GetVal(h1, (index+1));
            h2 = newNodeIndex(h2, right, (index+1));
        }

        h2 = OrderMin(h2, Length(h2));

        k--;
        GetMin(h1, h2, k, heapsize);
    }else{
        //printf("%d ", h2->val);
    }
}

//metodo per ottenere il k-esimo valore minimo della heap
void GetMax(MinHeap *h1, MinHeap *h2, int k, int heapsize)
{
    if(k>1){
        int index = 2*(h2->index); //salvo l'indice della radice della heap h2
        int left;
        int right;
        h2 = h2->next; //rimuovo la radice di h2

        if(index<=heapsize){ //se la radice aveva un figlio sinistro in h1 lo inserisce in h2
            left = GetVal(h1, index);
            h2 = newNodeIndex(h2, left, index);
        }

        if((index+1)<=heapsize){ //se la radice aveva un figlio destro in h1 lo inserisce in h2
            right = GetVal(h1, (index+1));
            h2 = newNodeIndex(h2, right, (index+1));
        }

        h2 = OrderMax(h2, Length(h2));

        k--;
        GetMax(h1, h2, k, heapsize);
    }else{
        //printf("%d ", h2->val);
    }
}

//restituisce il valore del nodo della heap in posizione pos
int GetVal(MinHeap *h1, int pos)
{
    if(pos==1){
        return h1->val;
    }else{
        pos--;
        GetVal(h1->next, pos);
    }
}

//restituisce la dimensione della heap
int Length(MinHeap *node)
{
    if(node==NULL){
        return 0;
    }else{
        return 1 + Length(node->next);
    }
}

//crea un nuovo nodo aggiungendo anche il valore dell'indice
MinHeap *newNodeIndex(MinHeap *node, int value, int index)
{
    MinHeap *newNode = NULL;
    newNode=(MinHeap *) malloc(sizeof(MinHeap));
    newNode->val=value;
    newNode->index=index;
    newNode->next=node;
    return newNode;
}

//controlla che alla radice ci sia il minimo e restituisce una min-heap
MinHeap *HeapifyMin(MinHeap *root, int pos, int length)
{
    int left = pos*2;
    int right = pos*2 +1;

    int posMin;
    if(left<=length && GetVal(root, left)<GetVal(root, pos)){ //figlio sinistro esiste ed è minore del padre
        posMin = left;
    }else{
        posMin = pos;
    }

     if(right<=length && GetVal(root, right)<GetVal(root, posMin)){ //figlio destro esiste ed è minore di quello in posMin
        posMin = right;
    }

    if(posMin!=pos){//se la posizione minima non è quella del padre fa lo scambio e prosegue con la ricorsione
        MinHeap **first=GetNode(&root, pos);
        MinHeap **second=GetNode(&root, posMin);
        SwapHeap(first, second);
        HeapifyMin(root, posMin, length);
    }

    return root;
}

//controlla che alla radice ci sia il minimo e restituisce una min-heap
MinHeap *HeapifyMax(MinHeap *root, int pos, int length)
{
    int left = pos*2;
    int right = pos*2 +1;

    int posMax;
    if(left<=length && GetVal(root, left)>GetVal(root, pos)){ //figlio sinistro esiste ed è maggiore del padre
        posMax = left;
    }else{
        posMax = pos;
    }

     if(right<=length && GetVal(root, right)>GetVal(root, posMax)){ //figlio destro esiste ed è maggiore di quello in posMin
        posMax = right;
    }

    if(posMax!=pos){//se la posizione minima non è quella del padre fa lo scambio e prosegue con la ricorsione
        MinHeap **first=GetNode(&root, pos);
        MinHeap **second=GetNode(&root, posMax);
        SwapHeap(first, second);
        HeapifyMax(root, posMax, length);
    }

    return root;
}

//restituisce il puntatore al nodo della heap in posizione pos
MinHeap **GetNode(MinHeap **root, int pos)
{
    if(pos==1){
        return root;
    }else{
        pos--;
        GetNode(&(*root)->next, pos);
    }
}

//scambia i valori sia della chiave che dell'indice di due nodi
void SwapHeap(MinHeap **first, MinHeap **second)
{
    int val=(*first)->val;
    int index=(*first)->index;
    (*first)->val=(*second)->val;
    (*first)->index=(*second)->index;
    (*second)->val=val;
    (*second)->index=index;
}

void freeHeap(MinHeap *root)
{
    MinHeap *next = root;

    while(next)
    {
        MinHeap *n = next;
        next = n->next;
        free(n);
    }
}

void medianSelect(int *input, int k, int size)
{
    int min = Median(input, (k-1), 0, 4, (size-1), size);
    //printf("%d\n", min);
}

int Median(int *array, int k, int from, int to, int lastNum, int fullsize)
{
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

int Meds(int *array, int from, int to, int lastNum, int fullsize)
{
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

int PartitionFixed(int *array, int from, int to, int posMedOfMed)
{
    Swap(array, posMedOfMed, to);
    int median = from-1;

    for (int j=from; j<to; j++){
        if(array[j]<=array[to]){
            median++;
            Swap(array, median, j);
        }
    }
    median++;
    Swap(array, median, to);
    return median;
}