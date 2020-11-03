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
#include <math.h>
#include <limits.h>

struct minHeap{
    int val;
    int index;
    struct minHeap *next;
};

typedef struct minHeap MinHeap;

int Build(MinHeap **root, char *value, int heapsize);
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

int main(){

    //prende i valori dall'input
    char lista[5000];
    fgets(lista, 5000, stdin);
    char *value=strtok(lista, " \n");

    //crea la heap h1 e salva i valori in essa
    MinHeap *h1=NULL;
    int heapsize = Build(&h1, value, 0);

    //prende il numero k dall'input
    int k;
    scanf("%d", &k);

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

    return 0;
}

//costruisce la heap
int Build(MinHeap **root, char *value, int heapsize){
    if(value!=NULL){
        (*root) = newNode((*root), atoi(value));
        heapsize++;
        value=strtok(NULL, " \n");
        Build(root, value, heapsize);
    }else{
        return heapsize;
    }
}

//crea un nuovo nodo
MinHeap *newNode(MinHeap *node, int value){
    MinHeap *newNode = NULL;
    newNode=(MinHeap *) malloc(sizeof(MinHeap));
    newNode->val=value;
    newNode->next=node;
    return newNode;
}

//ordina la heap restituendo una min-heap
MinHeap *OrderMin(MinHeap *root, int heapsize){
    if(heapsize==1){
        return root;
    }else{
        for(int i=(heapsize/2); i>0; i--){
            root = HeapifyMin(root, i, heapsize);
        }
    }
}

//ordina la heap restituendo una max-heap
MinHeap *OrderMax(MinHeap *root, int heapsize){
    if(heapsize==1){
        return root;
    }else{
        for(int i=(heapsize/2); i>0; i--){
            root = HeapifyMax(root, i, heapsize);
        }
    }
}

//stampa la heap
void printMinHeap(MinHeap *root){
    if(root==NULL){
        printf("\n");
    }else{
        printf("%d ", root->val);
        printMinHeap(root->next);
    }
}

//metodo per ottenere il k-esimo valore minimo della heap
void GetMin(MinHeap *h1, MinHeap *h2, int k, int heapsize){
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
        printf("%d", h2->val);
    }
}

//metodo per ottenere il k-esimo valore minimo della heap
void GetMax(MinHeap *h1, MinHeap *h2, int k, int heapsize){
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
        printf("%d", h2->val);
    }
}

//restituisce il valore del nodo della heap in posizione pos
int GetVal(MinHeap *h1, int pos){
    if(pos==1){
        return h1->val;
    }else{
        pos--;
        GetVal(h1->next, pos);
    }
}

//restituisce la dimensione della heap
int Length(MinHeap *node){
    if(node==NULL){
        return 0;
    }else{
        return 1 + Length(node->next);
    }
}

//crea un nuovo nodo aggiungendo anche il valore dell'indice
MinHeap *newNodeIndex(MinHeap *node, int value, int index){
    MinHeap *newNode = NULL;
    newNode=(MinHeap *) malloc(sizeof(MinHeap));
    newNode->val=value;
    newNode->index=index;
    newNode->next=node;
    return newNode;
}

//controlla che alla radice ci sia il minimo e restituisce una min-heap
MinHeap *HeapifyMin(MinHeap *root, int pos, int length){
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
MinHeap *HeapifyMax(MinHeap *root, int pos, int length){
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
MinHeap **GetNode(MinHeap **root, int pos){
    if(pos==1){
        return root;
    }else{
        pos--;
        GetNode(&(*root)->next, pos);
    }
}

//scambia i valori sia della chiave che dell'indice di due nodi
void SwapHeap(MinHeap **first, MinHeap **second){
    int val=(*first)->val;
    int index=(*first)->index;
    (*first)->val=(*second)->val;
    (*first)->index=(*second)->index;
    (*second)->val=val;
    (*second)->index=index;
}