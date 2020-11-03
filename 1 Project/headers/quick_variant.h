
clock_t quickSelect(int *input, int k, int size);
int quicksort(int *array, int from, int to, int k);
int partition(int *array, int from, int to);
void swap(int *array, int i, int j);

clock_t quickSelect(int *input, int k, int size)
{
    clock_t time_start = clock();
    int min = quicksort(input, 0, size, k);
    clock_t time_end = clock();
    return (time_end -time_start);
    //printf("%d\n", min);
}

int quicksort(int *array, int from, int to, int k)
{   
    int pos;

    while(from<to)
    {
        pos = partition(array, from, (to-1));

        if(pos == (k-1))
        {
            break;
        }
        else if(pos > (k-1))
        {
            to = pos;
        }
        else
        {
            from = pos +1; 
        }
    }

    return array[pos];
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