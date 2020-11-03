
#include <time.h>

clock_t heapSelect(int *input, int k, int size);
void createMinHeap(int *h1, int size);
void heapify(int *h1, int pos, int size);
void swapHeap(int *array, int i, int j);
int get(int *h1, int *h2, int k, int size);
int left(int pos);
int right(int pos);
void heapifySupport(int *h1, int *h2, int pos, int sizeSupport);
void control(int *h1, int *h2, int pos);

clock_t heapSelect(int *h1, int k, int size)
{

    createMinHeap(h1, size);
    int h2[size];

    clock_t time_start;
    clock_t time_end;

    time_start = clock();
    int min = get(h1, h2, k, size);
    time_end = clock();
    //printf("%d", min);

    return (time_end - time_start);
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