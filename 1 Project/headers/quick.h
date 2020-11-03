
clock_t quickSelect(int *input, int k, int size);
void quicksort(int *array, int from, int to, int posMin);
int partition(int *array, int from, int to);
void swap(int *array, int i, int j);

clock_t quickSelect(int *input, int k, int size)
{
    clock_t time_start = clock();
    quicksort(input, 0, (size-1), (k-1));
    clock_t time_end = clock();
    return (time_end -time_start);
    //printf("%d\n", toOrdinate[k-1]);
}

void quicksort(int *array, int from, int to, int posMin)
{
    if(from<to)
    {
        int r = partition(array, from, to);
        
        if(posMin!=r)
        {
            if(posMin<r)
            {
                quicksort(array, from, r-1, posMin);
            }
            else
            {
                quicksort(array, r+1, to, posMin);
            }
        }
    }
}

//fa la partizione di numeri minori e maggiori di un perno e ritorna il perno
int partition(int *array, int from, int to)
{
    int x = array[to];
    int median = from-1;

    for (int j=from; j<to; j++)
    {
        if(array[j]<=x)
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